#pragma once

#include "core/interfaces/constructed/factories/WindowFactory.h"
#include "core/types/Reference.h"
#include "core/types/window/WindowProperties.h"
#include "core/interfaces/constructed/factories/LoggerFactory.h"

namespace vanadium {

class SdlWindowFactoryImpl : public WindowFactory {
 private:
  Ref<LoggerFactory> _loggerFactory;

 public:
  explicit SdlWindowFactoryImpl(Ref<LoggerFactory> loggerFactory);
  ~SdlWindowFactoryImpl() override = default;

  [[nodiscard]] Ref<Window> construct(
      const WindowProperties &properties) override;
};

}  // namespace vanadium
