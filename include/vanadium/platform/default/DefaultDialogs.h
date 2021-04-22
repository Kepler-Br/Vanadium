#ifndef VANADIUM_DEFAULTDIALOGS_H
#define VANADIUM_DEFAULTDIALOGS_H

#include <string>

namespace Vanadium {

class DefaultDialogs {
 public:
  enum class Type {
    Error = 0,
    Warning,
    Information,
  };

 public:
  static bool show(const std::string &title, const std::string &content,
                   Type type = Type::Error);
};

}  // namespace Vanadium

#endif  // VANADIUM_DEFAULTDIALOGS_H
