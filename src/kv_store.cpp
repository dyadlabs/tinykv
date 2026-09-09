#include "tinykv/kv_store.h"

namespace tinykv {
bool KVStore::put(const std::string &key, const std::string &value) {
  if (key.empty()) {
    return false;
  }
  data_[key] = value;
  return true;
}

std::optional<std::string> KVStore::get(const std::string &key) const {
  auto it = data_.find(key);
  if (it != data_.end()) {
    return it->second;
  }
  return std::nullopt;
}

bool KVStore::remove(const std::string &key) { return data_.erase(key) == 1; }

bool KVStore::exists(const std::string &key) const {
  auto it = data_.find(key);
  return it != data_.end();
}

} // namespace tinykv
