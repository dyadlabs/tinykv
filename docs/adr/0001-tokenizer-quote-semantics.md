# ADR-0001：Tokenizer 中引号的语义与空参数的处理

- **Status**: Accepted
- **Date**: 2026-10-07
- **Code**: `src/command_parser.cpp`, `include/tinykv/command_parser.h`

## Question

如何 Tokenize, 同时 Quote 具体的作用是什么？

需要回答的子问题：

1. 引号在字符中间应该起什么作用？
2. `""` 应该对应什么 token?
3. 位于 token 之外的 space, 怎么处理？

## Context

最初的实现用同一个判断 `if (!current.empty())`.
但糅合了对于 Token 和空白的两种不同的判断，因此怎么修复都会有测试出问题。


## Decision

采用以下规则（实现于 `CommandParser::tokenize`）：

1. 引入独立状态位 `token_started`，用于区分对于 token 和 space 的判断。
2. 保留 `in_quotes` 并使用 `"` 进行切换，保证对于引号的处理。
3. 字符中间的 `"` 将立马 push back 当前 token 并开启下一个 in quotes 的 token.

行为示例（均有对应测试）：

| 输入 | tokens | 说明 |
|---|---|---|
| `put a apple` | `put` `a` `apple` | 基本情形 |
| `put "a b" "c d"` | `put` `"a b"` `"c d"` | 引号内空白不切分 |
| `put "" v` | `put` `""` `v` | 空参数在中间 |
| `put a ""` | `put` `a` `""` | 空参数在行尾 |
| `get ""` | `get` `""` | 唯一参数为空 |
| `   put a apple` | `put` `a` `apple` | 前导/重复/尾随空白均忽略 |
| `put a b"c d"e` | `put` `a` `b` `c d` `e` | 引号在中间时起分隔作用 |
| `"put a apple"` | `"put a apple"` | 整行加引号 = 一个 token |

## Reason

目前没有支持转义等复杂功能，因此强化了引号对于 Token 的切分作用。
但引号只是一部分，因此 `token_started` 的引入是必要的。

## Trade-off

不支持转义符号，因此 Token 中不能出现引号。
计划在后续更新中支持。
