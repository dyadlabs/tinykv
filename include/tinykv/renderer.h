#pragma once

#include "result.h"
#include <ostream>

namespace tinykv {
class Renderer {
public:
  static void render(const ExecutionResult &result, std::ostream &os);
};
} // namespace tinykv
