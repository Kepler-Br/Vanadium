#pragma once

#include <stdexcept>
#include <unordered_map>

#include "vanadium/core/Exceptions.h"
#include "vanadium/core/interfaces/Factory.h"
#include "vanadium/core/types/Reference.h"

namespace vanadium {

class FactoryContainer {
 public:
  virtual ~FactoryContainer() = default;

  /**
   * Get factory by registered name.
   * @param name factory name.
   * @return Reference to factory.
   * If not found then <code>nullptr</code> is returned.
   */
  virtual Ref<Factory> getFactory(const std::string &name) = 0;

  /**
   * Register preinstantiated factory.
   * @param factory reference to preinstantiated factory.
   * @return reference to registered factory.
   * @throws FactoryAlreadyRegistered if factory was already registered.
   */
  virtual Ref<Factory> registerFactory(Ref<Factory> factory) = 0;

  virtual bool hasFactory(const std::string &name) = 0;

#pragma region static

  /**
   * Get factory by type.
   * Factory type should implement <code>Factory</code> interface
   * and implement <code>static std::string getFactoryName()</code> method.
   * @tparam TFactory factory type to be found.
   * @return reference to registered factory.
   * If not found then <code>nullptr</code> is returned.
   */
  template <class TFactory>
  static Ref<TFactory> getFactory(const Ref<FactoryContainer>& factoryContainer) {
    const std::string &name = TFactory::getFactoryName();

    Ref<Factory> found = factoryContainer->getFactory(name);

    return std::static_pointer_cast<TFactory>(found);
  }

  /**
   * Register factory by type.
   * Factory type should implement <code>Factory</code> interface
   * and implement <code>static std::string getFactoryName()</code> method.
   * @tparam TFactory factory type to be registered.
   * @return reference to registered factory.
   * @throws FactoryAlreadyRegistered if factory was already registered.
   */
  template <class TFactory>
  static Ref<TFactory> registerFactory(const Ref<FactoryContainer>& factoryContainer) {
    const std::string &name = TFactory::getFactoryName();

    if (factoryContainer->hasFactory(name)) {
      throw FactoryAlreadyRegistered("Factory with name " + name +
                                     " was already registered.");
    }

    Ref<TFactory> factory = MakeRef<TFactory>();

    factory = factoryContainer->registerFactory(factory);

    return std::static_pointer_cast<TFactory>(factory);
  }

  /**
   * Register factory by type.
   * Factory type should implement <code>Factory</code> interface
   * and implement <code>static std::string getFactoryName()</code> method.
   * @tparam TFactory factory type to be found.
   * @return reference to registered factory.
   */
  template <class TFactory>
  static bool hasFactory(const Ref<FactoryContainer>& factoryContainer) {
    const std::string &name = TFactory::getFactoryName();

    return factoryContainer->hasFactory(name);
  }
#pragma endregion
};

}  // namespace vanadium
