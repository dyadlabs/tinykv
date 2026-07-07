#include "tinykv/kv_store.h"

namespace tinykv {
bool KVStore::put(const std::string &key, const std::string &value) {
  if (key.empty()) {
    return false;
  }
  data_[key] = value;
  return true;
}

std::optional<std::string> KVStore::get(std::string_view key) const {
  auto it = data_.find(std::string(key));
  if (it != data_.end()) {
    return it->second;
  }
  return std::nullopt;
}

bool KVStore::remove(std::string_view key) {
  return data_.erase(std::string(key)) == 1;
}

bool KVStore::exists(std::string_view key) const {
  auto it = data_.find(std::string(key));
  return it != data_.end();
}

} // namespace tinykv
