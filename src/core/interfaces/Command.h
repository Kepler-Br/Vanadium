#ifndef VANADIUM_COMMAND_H
#define VANADIUM_COMMAND_H

namespace vanadium {

class Command {
 public:
  virtual ~Command() = default;

  virtual void execute() = 0;
  virtual void undo() {}
};

}  // namespace vanadium

#endif  // VANADIUM_COMMAND_H
