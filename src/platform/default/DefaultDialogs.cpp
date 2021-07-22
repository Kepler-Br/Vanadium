#include "platform/default/DefaultDialogs.h"

#include "platform/default/DefaultIncludes.h"

namespace vanadium {

bool DefaultDialogs::show(const std::string &title, const std::string &content,
                          DialogType type) {
  int result;
  switch (type) {
    case DialogType::Error:
      result = SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, title.c_str(),
                                        content.c_str(), nullptr);
      break;
    case DialogType::Warning:
      result = SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING, title.c_str(),
                                        content.c_str(), nullptr);
      break;
    case DialogType::Information:
      result = SDL_ShowSimpleMessageBox(
          SDL_MESSAGEBOX_INFORMATION, title.c_str(), content.c_str(), nullptr);
      break;
  }
  return result == 0;
}

}  // namespace Vanadium
