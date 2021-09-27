#pragma once

#include "vanadium/core/interfaces/Factory.h"
#include "vanadium/core/interfaces/constructed/Logger.h"
#include "vanadium/core/types/Reference.h"

namespace vanadium {

class LoggerFactory : public Factory {
 private:
  static std::string _name;

 public:
  ~LoggerFactory() override = default;

  [[nodiscard]] virtual Ref<Logger> construct(const std::string &name) = 0;

  [[nodiscard]] const std::string &getName() const noexcept final;
  static const std::string &getFactoryName() noexcept;
};

}  // namespace vanadium
