#include "tinykv/command_executor.h"

// TODO: better error handling
namespace tinykv {
CommandExecutor::CommandExecutor() {
  handlers["put"] = handlePut;
  handlers["get"] = handleGet;
  handlers["remove"] = handleRemove;
  handlers["contain"] = handleExists;
}
void CommandExecutor::execute(KVStore &kv, const Command &command) {
  auto it = handlers.find(command.name);
  if (it == handlers.end()) {
    throw std::runtime_error("Unknown command");
  }

  it->second(kv, command);
}

void CommandExecutor::handlePut(KVStore &kv, const Command &command) {
  validateArgs(command, 2);
  kv.put(command.arguments[0], command.arguments[1]);
}
void CommandExecutor::handleGet(KVStore &kv, const Command &command) {
  validateArgs(command, 1);
  std::optional<std::string> value = kv.get(command.arguments[0]);
  if (value == std::nullopt) {
    printf("The key does not exist.\n");
  } else {
    printf("Value: %s", value.value().c_str());
  }
}

void CommandExecutor::handleRemove(KVStore &kv, const Command &command) {
  validateArgs(command, 1);
  if (!kv.remove(command.arguments[0])) {
    printf("The key does not exist.\n");
  }
}
void CommandExecutor::handleExists(KVStore &kv, const Command &command) {
  validateArgs(command, 1);
  if (kv.exists(command.arguments[0])) {
    printf("The key exists.\n");
  } else {
    printf("The key does not exist.\n");
  }
}

void CommandExecutor::validateArgs(const Command &command, int num) {
  if (command.arguments.size() != num) {
    throw std::runtime_error("Incorrect argument number");
  }
}
} // namespace tinykv
