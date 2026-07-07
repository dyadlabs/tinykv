#include "tinykv/kv_store.h"
#include <iostream>

int main() {
  tinykv::KVStore kv_store;
  kv_store.put("name", "alice");
  std::optional<std::string> result = kv_store.get("name");
  std::cout << "name: " << result.value() << std::endl;
  return 0;
}
