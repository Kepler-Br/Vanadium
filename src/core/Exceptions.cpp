#include "core/Exceptions.h"

namespace vanadium {

InitializationInterrupted::InitializationInterrupted(const std::string& msg)
    : std::runtime_error(msg), doShowDialog(false) {}

bool InitializationInterrupted::showDialog() const noexcept {
  return doShowDialog;
}

InitializationInterrupted& InitializationInterrupted::withDialog() noexcept {
  this->doShowDialog = true;

  return *this;
}

ExecutionInterrupted::ExecutionInterrupted(const std::string& msg)
    : std::runtime_error(msg), doShowDialog(false) {}

bool ExecutionInterrupted::showDialog() const noexcept { return doShowDialog; }

ExecutionInterrupted& ExecutionInterrupted::withDialog() noexcept {
  this->doShowDialog = true;

  return *this;
}

}  // namespace vanadium