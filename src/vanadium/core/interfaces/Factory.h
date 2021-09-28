#pragma once

#include <string>

namespace vanadium {

class Factory {
 public:
  virtual ~Factory() = default;

  /**
   * Should return name of the base factory(Not end implementation).
   * @return Name of base factory.
   */
  [[nodiscard]] virtual const std::string &getName() const noexcept = 0;
  /**
   * Should be overridden by end implementation.
   * @return Name of end implementation.
   */
  [[nodiscard]] virtual const std::string &getImplName() const noexcept = 0;
};

}  // namespace vanadium
