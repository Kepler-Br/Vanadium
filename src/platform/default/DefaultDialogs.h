#ifndef VANADIUM_DEFAULTDIALOGS_H
#define VANADIUM_DEFAULTDIALOGS_H

#include <string>

#include "../../core/Types.h"

namespace vanadium {

class DefaultDialogs {
 public:
  static bool show(const std::string &title, const std::string &content,
                   DialogType type = DialogType::Error);
};

}  // namespace vanadium

#endif  // VANADIUM_DEFAULTDIALOGS_H
