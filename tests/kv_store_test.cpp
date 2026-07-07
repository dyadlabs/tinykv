#include "tinykv/kv_store.h"
#include <cassert>

void integrated_test() {
  tinykv::KVStore kv_store;
  assert(kv_store.put("name", "mike"));
  assert(kv_store.get("name") == "mike");
  assert(kv_store.put("name", "bob"));
  assert(kv_store.get("name") == "bob");
  assert(kv_store.get("missing") == std::nullopt);
  assert(kv_store.exists("name"));
  assert(kv_store.remove("name"));
  assert(!kv_store.exists("name"));
  assert(!kv_store.remove("name"));
  assert(!kv_store.put("", "value"));
}

int main() {
  integrated_test();
  return 0;
}
