#ifndef VANADIUM_SVG_PATH_H
#define VANADIUM_SVG_PATH_H

#include <string>
#include <utility>
#include <vector>

#include "Commands.h"

namespace vanadium {

namespace svg {

class Path {
 private:
  std::vector<commands::Command *> commands;

 public:
  Path(const std::initializer_list<commands::Command *> &list)
      : commands(list) {}

  Path(std::vector<commands::Command *> commands)
      : commands(std::move(commands)) {}

  ~Path() {
    for (commands::Command *command : this->commands) {
      delete command;
    }
    this->commands.clear();
  }

  [[nodiscard]] const std::vector<commands::Command *> &getCommands()
      const noexcept {
    return this->commands;
  }
};

}  // namespace svg

}  // namespace vanadium

#endif  // VANADIUM_SVG_PATH_H
