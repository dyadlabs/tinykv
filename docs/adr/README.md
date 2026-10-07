# Architecture Decision Records

本目录记录 TinyKV 的**设计决策**。

格式遵循 [adr.github.io](https://adr.github.io)（Michael Nygard, *Documenting Architecture Decisions*, 2011）。

## Format

| 字段 | 含义 |
|---|---|
| **Question** | 面对的是什么问题？有哪几种可选方案？ |
| **Decision** | 选了哪个，以及具体规则是什么？ |
| **Reason** | 为什么它更好？ |
| **Trade-off** | 这个选择**代价**是什么？ |

## 两条核心规则

### 1. Append-Only

如果已有决定需要更新，在旧的 `Status` 里写 `Superseded by ADR-XXXX`。**

### 2. When to Append

只有以后需要回顾的决策进入 ADR 文档。

## 状态机

```
Proposed  →  Accepted  →  Deprecated  →  Superseded by ADR-NNNN
   │
   └──→ Rejected（记下来为什么否掉，避免以后重蹈覆辙）
```

- `Proposed`：已提出，尚未决定。
- `Accepted`：已决定，且当前实现与之一致。
- `Rejected`：考虑过但否掉了。

## 命名

```
NNNN-kebab-case-英文短标题.md
```

编号顺序递增，永不复用。

## 语言

本目录使用中文撰写：ADR 用思考最快的语言写收益最大。
代码标识符、注释、`README.md` 与 commit message 保持英文，面向所有人和工具。
