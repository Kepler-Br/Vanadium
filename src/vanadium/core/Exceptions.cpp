#include "vanadium/core/Exceptions.h"

namespace vanadium {

ExceptionWithDialog::ExceptionWithDialog(const std::string& msg) noexcept
    : std::runtime_error(msg) {}

bool ExceptionWithDialog::showDialog() const noexcept { return _showDialog; }

ExceptionWithDialog& ExceptionWithDialog::withDialog() noexcept {
  this->_showDialog = true;

  return *this;
}

}  // namespace vanadium
