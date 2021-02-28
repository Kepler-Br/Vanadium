#ifndef VANADIUM_ENTRY_H
#define VANADIUM_ENTRY_H

#include <string>

namespace Vanadium
{

namespace Vfs
{

// Think about new name.
class Entry
{
private:
    std::string workingDirectory;

public:
    Entry(std::string workingDirectory = "");
    ~Entry();
};

}

}

#endif //VANADIUM_ENTRY_H
