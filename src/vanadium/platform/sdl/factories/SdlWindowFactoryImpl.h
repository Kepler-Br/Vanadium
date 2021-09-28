#pragma once

#include "vanadium/core/interfaces/constructed/factories/LoggerFactory.h"
#include "vanadium/core/interfaces/constructed/factories/WindowFactory.h"
#include "vanadium/core/types/Reference.h"
#include "vanadium/core/types/window/WindowProperties.h"

namespace vanadium {

class SdlWindowFactoryImpl : public WindowFactory {
 private:
  static const std::string _implName;

  Ref<LoggerFactory> _loggerFactory;

 public:
  explicit SdlWindowFactoryImpl(Ref<LoggerFactory> loggerFactory);
  ~SdlWindowFactoryImpl() override = default;

  [[nodiscard]] Ref<Window> construct(
      const WindowProperties &properties) override;

  [[nodiscard]] const std::string &getImplName() const noexcept override;
};

}  // namespace vanadium
