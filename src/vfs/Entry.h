#ifndef VANADIUM_ENTRY_H
#define VANADIUM_ENTRY_H

#include <string>

namespace vanadium {

namespace Vfs {

// Think about new name.
class Entry {
 private:
  std::string workingDirectory;

 public:
  explicit Entry(std::string workingDirectory = "");
  ~Entry();
};

}  // namespace Vfs

}  // namespace Vanadium

#endif  // VANADIUM_ENTRY_H
