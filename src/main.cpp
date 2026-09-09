#include "tinykv/command_executor.h"
#include "tinykv/command_parser.h"
#include "tinykv/kv_store.h"

#include <iostream>
#include <stdexcept>
#include <string>

int main() {
  tinykv::KVStore kv_store;
  tinykv::CommandExecutor executor;
  std::string line;
  std::cout << "> ";
  while (std::getline(std::cin, line)) {
    tinykv::Command command = tinykv::CommandParser::parse(line);
    if (command.name == "quit") {
      break;
    } else if (command.empty()) {
      continue;
    }
    try {
      executor.execute(kv_store, command);
    } catch (const std::runtime_error &e) {
      std::cerr << "Error: " << e.what() << "\n";
      std::cout << "> ";
      continue;
    }
    std::cout << "> ";
  }
  return 0;
}
