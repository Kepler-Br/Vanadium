#include "core/Exceptions.h"

namespace vanadium {

InitializationInterrupted::InitializationInterrupted(const std::string& msg,
                                                     bool showDialog)
    : std::runtime_error(msg), doShowDialog(showDialog) {}

bool InitializationInterrupted::showDialog() const noexcept {
  return doShowDialog;
}

ExecutionInterrupted::ExecutionInterrupted(const std::string& msg,
                                           bool showDialog)
    : std::runtime_error(msg), doShowDialog(showDialog) {}

bool ExecutionInterrupted::showDialog() const noexcept { return doShowDialog; }
}  // namespace Vanadium