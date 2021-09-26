#pragma once

#include <string>

#include "vanadium/core/types/DialogType.h"

namespace vanadium {

class SdlDialogs {
 public:
  static bool show(const std::string &title, const std::string &content,
                   DialogType type = DialogType::Error);
};

}  // namespace vanadium
