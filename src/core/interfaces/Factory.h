#pragma once

#include <string>

namespace vanadium {

class Factory {
 public:
  virtual ~Factory() = default;

  [[nodiscard]] virtual const std::string &getName() const noexcept = 0;
};

}  // namespace vanadium
