#ifndef VANADIUM_CORE_SUBSYTEM_H
#define VANADIUM_CORE_SUBSYTEM_H

#include <string>
#include <utility>

namespace vanadium {

class Subsystem {
 protected:
  std::string _name;

 public:
  explicit Subsystem(std::string name) : _name(std::move(name)){};
  virtual ~Subsystem() = default;

  virtual void init() = 0;
  virtual void shutdown() = 0;
  [[nodiscard]] virtual const std::string &getName() const noexcept {
    return this->_name;
  }
};

}  // namespace vanadium

#endif  // VANADIUM_CORE_SUBSYTEM_H
