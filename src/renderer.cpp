#include "tinykv/renderer.h"
#include "tinykv/result.h"
#include <type_traits>
#include <variant>

namespace tinykv {
void Renderer::render(const ExecutionResult &result, std::ostream &os) {
  std::visit(
      [&](const auto &r) {
        using T = std::decay_t<decltype(r)>;

        if constexpr (std::is_same_v<T, PutResult>) {
          if (r.original_value) {
            os << "The value of \"" << r.key << "\" is updated from \""
               << r.original_value.value() << "\" to \"" << r.value << "\".\n";
          } else {
            os << "Put the pair {\"" << r.key << "\": \"" << r.value
               << "\"}.\n";
          }
        } else if constexpr (std::is_same_v<T, GetResult>) {
          if (!r.value) {
            os << "The key does not exist.\n";
          } else {
            os << "Got the pair {\"" << r.key << "\": \"" << r.value.value()
               << "\"}.\n";
          }
        } else if constexpr (std::is_same_v<T, RemoveResult>) {
          if (!r.success) {
            os << "The key does not exist.\n";
          } else {
            os << "Removed the pair mapped by \"" << r.key << "\".\n";
          }
        } else {
          if (!r.exists) {
            os << "The key does not exists.\n";
          } else {
            os << "Found the key \"" << r.key << "\".\n";
          }
        }
      },
      result);
}
} // namespace tinykv
