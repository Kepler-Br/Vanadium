#ifndef VANADIUM_EXCEPTIONS_H
#define VANADIUM_EXCEPTIONS_H

#include <stdexcept>

namespace vanadium {

class ShaderAssetParsingError : public std::runtime_error {
  using std::runtime_error::runtime_error;
};

class ShaderCompilationError : public std::runtime_error {
  using std::runtime_error::runtime_error;
};

class ExceptionWithDialog : public std::runtime_error {
  using std::runtime_error::runtime_error;

 protected:
  bool _showDialog = false;

 public:
  explicit ExceptionWithDialog(const std::string &msg) noexcept;

  ExceptionWithDialog &withDialog() noexcept;

  [[nodiscard]] bool showDialog() const noexcept;
};

// Should not be called otherwise than in Application preInit or postInit
// methods.
class InitializationInterrupted : public ExceptionWithDialog {
  using ExceptionWithDialog::ExceptionWithDialog;
};

// Should be called by state when some problem occurred.
class ExecutionInterrupted : public ExceptionWithDialog {
  using ExceptionWithDialog::ExceptionWithDialog;
};

class SubsystemInitializationException : public ExceptionWithDialog {
  using ExceptionWithDialog::ExceptionWithDialog;
};

}  // namespace vanadium

#endif  // VANADIUM_EXCEPTIONS_H
