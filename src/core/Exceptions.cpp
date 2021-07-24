#include "core/Exceptions.h"

namespace vanadium {

InitializationInterrupted::InitializationInterrupted(const std::string& msg)
    : std::runtime_error(msg), _doShowDialog(false) {}

bool InitializationInterrupted::showDialog() const noexcept {
  return _doShowDialog;
}

InitializationInterrupted& InitializationInterrupted::withDialog() noexcept {
  this->_doShowDialog = true;

  return *this;
}

ExecutionInterrupted::ExecutionInterrupted(const std::string& msg)
    : std::runtime_error(msg), _doShowDialog(false) {}

bool ExecutionInterrupted::showDialog() const noexcept { return _doShowDialog; }

ExecutionInterrupted& ExecutionInterrupted::withDialog() noexcept {
  this->_doShowDialog = true;

  return *this;
}

}  // namespace vanadium