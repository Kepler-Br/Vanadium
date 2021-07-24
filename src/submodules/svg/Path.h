#ifndef VANADIUM_SVG_PATH_H
#define VANADIUM_SVG_PATH_H

#include <string>
#include <utility>
#include <vector>

#include "Commands.h"

namespace vanadium::svg {

class Path {
 private:
  std::vector<commands::Command *> _commands;

 public:
  Path(const std::initializer_list<commands::Command *> &list)
      : _commands(list) {}

  Path(std::vector<commands::Command *> commands)
      : _commands(std::move(commands)) {}

  ~Path() {
    for (commands::Command *command : this->_commands) {
      delete command;
    }
    this->_commands.clear();
  }

  [[nodiscard]] const std::vector<commands::Command *> &getCommands()
      const noexcept {
    return this->_commands;
  }
};

}  // namespace vanadium::svg

#endif  // VANADIUM_SVG_PATH_H
