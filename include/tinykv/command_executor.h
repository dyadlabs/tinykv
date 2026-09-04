#pragma once

#include "command.h"
#include "kv_store.h"

#include <cstdio>
#include <functional>
#include <optional>
#include <stdexcept>
#include <unordered_map>

namespace tinykv {
class CommandExecutor {
public:
  CommandExecutor();
  void execute(KVStore &kv, const Command &command);

private:
  std::unordered_map<std::string,
                     std::function<void(KVStore &, const Command &)>>
      handlers;

  void static handlePut(KVStore &kv, const Command &command);
  void static handleGet(KVStore &kv, const Command &command);
  void static handleRemove(KVStore &kv, const Command &command);
  void static handleExists(KVStore &kv, const Command &command);
  void static validateArgs(const Command &command, int num);
};
} // namespace tinykv
