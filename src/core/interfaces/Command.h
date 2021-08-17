#pragma once

namespace vanadium {

class Command {
 public:
  virtual ~Command() = default;

  virtual void execute() = 0;
  virtual void undo() {}
};

}  // namespace vanadium
