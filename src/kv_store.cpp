#include "tinykv/kv_store.h"
#include "tinykv/error.h"

namespace tinykv {
namespace {
void requiredNonEmptyKey(const std::string &key) {
  if (key.empty()) {
    throw InvalidKey("The key must not be empty.");
  }
}
} // namespace

void KVStore::put(const std::string &key, const std::string &value) {
  requiredNonEmptyKey(key);
  data_[key] = value;
}

std::optional<std::string> KVStore::get(const std::string &key) const {
  requiredNonEmptyKey(key);
  auto it = data_.find(key);
  if (it != data_.end()) {
    return it->second;
  }
  return std::nullopt;
}

bool KVStore::remove(const std::string &key) {
  requiredNonEmptyKey(key);
  return data_.erase(key) == 1;
}

bool KVStore::exists(const std::string &key) const {
  requiredNonEmptyKey(key);
  auto it = data_.find(key);
  return it != data_.end();
}

} // namespace tinykv
