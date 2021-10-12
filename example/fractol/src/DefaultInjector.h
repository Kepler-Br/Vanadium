#pragma once

#include <vanadium/core/Assert.h>
#include <vanadium/core/application/ApplicationImpl.h>
#include <vanadium/core/application/FactoryContainerImpl.h>
#include <vanadium/core/application/MainLoopImpl.h>
#include <vanadium/core/application/StateStackImpl.h>
#include <vanadium/core/interfaces/Application.h>
#include <vanadium/core/interfaces/FactoryContainer.h>
#include <vanadium/core/interfaces/MainLoop.h>
#include <vanadium/core/interfaces/constructed/EventProvider.h>
#include <vanadium/core/interfaces/constructed/StateStack.h>
#include <vanadium/core/types/Reference.h>
#include <vanadium/core/types/application/ApplicationProperties.h>
#include <vanadium/platform/default/factories/DefaultEventDispatcherFactoryImpl.h>
#include <vanadium/platform/default/factories/DefaultLoggerFactoryImpl.h>
#include <vanadium/platform/sdl/SdlEventProviderImpl.h>
#include <vanadium/platform/sdl/factories/SdlEventProviderFactoryImpl.h>
#include <vanadium/platform/sdl/factories/SdlStopwatchFactoryImpl.h>
#include <vanadium/platform/sdl/factories/SdlWindowFactoryImpl.h>

#include <boost/di.hpp>
#include <boost/di/extension/injections/shared_factory.hpp>
#include <iostream>

void registerFactories(
    const vanadium::Ref<vanadium::FactoryContainer>& factoryContainer,
    const vanadium::ApplicationProperties appProps) {
  using namespace vanadium;

  factoryContainer->registerFactory<DefaultLoggerFactoryImpl>(
      appProps.getLogLevel(), "[%Y-%m-%d %T] [%^%l%$] %n: %v",
      appProps.getLogPath());
  factoryContainer->registerFactory<SdlStopwatchFactoryImpl>();
  factoryContainer->registerFactory<SdlWindowFactoryImpl>(
      factoryContainer->getFactory<LoggerFactory>());
  factoryContainer->registerFactory<SdlEventProviderFactoryImpl>(
      factoryContainer->getFactory<LoggerFactory>());
  factoryContainer->registerFactory<DefaultEventDispatcherFactoryImpl>();
}

auto getInjector(const vanadium::ApplicationProperties &appProps) {
  namespace di = boost::di;
  using namespace vanadium;

  const auto *props = &appProps;
  auto fclambda = [&](const auto&) -> Ref<FactoryContainer> {
    Ref<FactoryContainer> factoryContainer =
        MakeRef<FactoryContainerImpl>();

    const auto ppp = *props;

    registerFactories(factoryContainer, ppp);

    return factoryContainer;
  };

  auto injector = di::make_injector(
      di::bind<FactoryContainer>().to(
          boost::di::extension::shared_factory<FactoryContainer>(
              fclambda)),
      di::bind<LoggerFactory>().to([](const auto& inj) -> Ref<LoggerFactory> {
        auto factoryContainer = inj.template create<Ref<FactoryContainer>>();

        Ref<LoggerFactory> loggerFactory =
            factoryContainer->template getFactory<LoggerFactory>();

        VAN_ENGINE_ASSERT((loggerFactory != nullptr),
                          "Cannot cast factory to LoggerFactory");

        return loggerFactory;
      }),
      di::bind<EngineEndMainLoop>.to<MainLoopImpl>(),
      di::bind<EngineEndStateStack>.to<StateStackImpl>(),
      di::bind<EngineEndEventProvider>.to<SdlEventProviderImpl>(),
      di::bind<EngineEndApplication>.to<ApplicationImpl>());

  return injector;
}
