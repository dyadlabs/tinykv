#pragma once

#include "command.h"
#include "kv_store.h"
#include "result.h"

#include <functional>
#include <iostream>
#include <optional>
#include <unordered_map>

namespace tinykv {
class CommandExecutor {
public:
  CommandExecutor();
  ExecutionResult execute(KVStore &kv, const Command &command);

private:
  std::unordered_map<std::string,
                     std::function<ExecutionResult(KVStore &, const Command &)>>
      handlers;

  PutResult static handlePut(KVStore &kv, const Command &command);
  GetResult static handleGet(KVStore &kv, const Command &command);
  RemoveResult static handleRemove(KVStore &kv, const Command &command);
  ExistsResult static handleExists(KVStore &kv, const Command &command);
  void static validateArgs(const Command &command, size_t num);
};
} // namespace tinykv
