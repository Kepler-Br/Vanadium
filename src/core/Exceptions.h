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

// Should not be called otherwise than in Application preInit or postInit
// methods.
class InitializationInterrupted : public std::runtime_error {
 private:
  bool doShowDialog;

 public:
  explicit InitializationInterrupted(const std::string &msg,
                                     bool showDialog = true);

  [[nodiscard]] bool showDialog() const noexcept;
};

// Should be called by state when some problem occurred.
class ExecutionInterrupted : public std::runtime_error {
 private:
  bool doShowDialog;

 public:
  explicit ExecutionInterrupted(const std::string &msg, bool showDialog = true);

  [[nodiscard]] bool showDialog() const noexcept;
};

}  // namespace Vanadium

#endif  // VANADIUM_EXCEPTIONS_H
