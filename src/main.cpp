#include "tinykv/command_parser.h"
#include "tinykv/kv_store.h"

#include <iostream>
#include <string>

int main() {
  tinykv::KVStore kv_store;
  tinykv::CommandParser parser;
  std::string line;
  while (std::getline(std::cin, line)) {
    tinykv::Command command = parser.parse(line);
    if (command.name.empty() || command.name == "quit") {
      break;
    }
    std::cout << "Command: " << command.name << std::endl;
    std::cout << "Arguments: " << command.arguments.size() << std::endl;
  }
  return 0;
}
