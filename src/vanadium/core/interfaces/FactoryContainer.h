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
  Ref<TFactory> getFactory() {
    const std::string &name = TFactory::getFactoryName();

    Ref<Factory> found = this->getFactory(name);

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
  template <class TFactory, class... Args>
  Ref<TFactory> registerFactory(Args &&...args) {
    const std::string &name = TFactory::getFactoryName();

    if (this->hasFactory(name)) {
      throw FactoryAlreadyRegistered("Factory with name " + name +
                                     " was already registered.");
    }

    Ref<TFactory> factory = MakeRef<TFactory>(std::forward<Args>(args)...);

    this->registerFactory(factory);

    return factory;
  }

  /**
   * Register factory by type.
   * Factory type should implement <code>Factory</code> interface
   * and implement <code>static std::string getFactoryName()</code> method.
   * @tparam TFactory factory type to be found.
   * @return reference to registered factory.
   */
  template <class TFactory>
  bool hasFactory() {
    const std::string &name = TFactory::getFactoryName();

    return this->hasFactory(name);
  }
#pragma endregion
};

}  // namespace vanadium
