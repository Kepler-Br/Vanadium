#pragma once

#include "vanadium/core/interfaces/constructed/EventProvider.h"
#include "vanadium/core/interfaces/constructed/factories/EventProviderFactory.h"
#include "vanadium/core/interfaces/constructed/factories/LoggerFactory.h"

namespace vanadium {

class SdlEventProviderFactoryImpl : public EventProviderFactory {
 private:
  const std::string _implName = "SdlEventProviderFactoryImpl";

  Ref<LoggerFactory> _loggerFactory;

 public:
  explicit SdlEventProviderFactoryImpl(Ref<LoggerFactory> loggerFactory);

  Ref<EventProvider> construct() override;

  [[nodiscard]] const std::string &getImplName() const noexcept override;
};

}
