#include "tinykv/command_executor.h"
#include "tinykv/command_parser.h"
#include "tinykv/error.h"
#include "tinykv/kv_store.h"
#include "tinykv/renderer.h"
#include "tinykv/result.h"

#include <iostream>
#include <ostream>
#include <stdexcept>
#include <string>

int main() {
  tinykv::KVStore kv_store;
  tinykv::CommandExecutor executor;
  std::string line;

  std::cout << "> ";
  while (std::getline(std::cin, line)) {
    try {
      tinykv::Command command = tinykv::CommandParser::parse(line);

      if (command.name == "quit") {
        break;
      } else if (command.empty()) {
        std::cout << "> " << std::flush;
        continue;
      }

      tinykv::ExecutionResult result = executor.execute(kv_store, command);
      tinykv::Renderer::render(result, std::cout);
    } catch (const tinykv::TinyKVError &e) {
      std::cerr << "Error: " << e.what() << "\n";
      std::cout << "> " << std::flush;
      continue;
    }
    std::cout << "> " << std::flush;
  }

  return 0;
}
