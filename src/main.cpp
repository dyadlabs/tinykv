#include "tinykv/command_executor.h"
#include "tinykv/command_parser.h"
#include "tinykv/kv_store.h"

#include <iostream>
#include <string>

int main() {
  tinykv::KVStore kv_store;
  tinykv::CommandParser parser;
  tinykv::CommandExecutor executor;
  std::string line;
  while (std::getline(std::cin, line)) {
    tinykv::Command command = parser.parse(line);
    if (command.name.empty() || command.name == "quit") {
      break;
    }
    executor.execute(kv_store, command);
  }
  return 0;
}
