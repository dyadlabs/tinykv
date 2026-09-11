#include "tinykv/command_executor.h"
#include "tinykv/error.h"
#include "tinykv/result.h"

namespace tinykv {

CommandExecutor::CommandExecutor() {
  handlers["put"] = handlePut;
  handlers["get"] = handleGet;
  handlers["remove"] = handleRemove;
  handlers["exists"] = handleExists;
}

ExecutionResult CommandExecutor::execute(KVStore &kv, const Command &command) {
  auto it = handlers.find(command.name);
  if (it == handlers.end()) {
    throw UnknownCommand("The command does not exist.");
  }

  return it->second(kv, command);
}

PutResult CommandExecutor::handlePut(KVStore &kv, const Command &command) {
  validateArgs(command, 2);
  std::optional<std::string> original_value;
  const std::string &key = command.arguments[0];
  const std::string &value = command.arguments[1];
  original_value = kv.get(key);
  kv.put(key, value);
  return {key, value, original_value};
}

GetResult CommandExecutor::handleGet(KVStore &kv, const Command &command) {
  validateArgs(command, 1);
  const std::string &key = command.arguments[0];
  std::optional<std::string> value = kv.get(key);
  return {key, value};
}

RemoveResult CommandExecutor::handleRemove(KVStore &kv,
                                           const Command &command) {
  validateArgs(command, 1);
  const std::string &key = command.arguments[0];
  bool success = kv.remove(key);
  return {success, key};
}

ExistsResult CommandExecutor::handleExists(KVStore &kv,
                                           const Command &command) {
  validateArgs(command, 1);
  const std::string &key = command.arguments[0];
  bool success = kv.exists(key);
  return {success, key};
}

void CommandExecutor::validateArgs(const Command &command, size_t num) {
  if (command.arguments.size() != num) {
    throw InvalidArguments("Incorrect number of arguments for this command.");
  }
}
} // namespace tinykv
