#ifndef VANADIUM_TOOLS_H
#define VANADIUM_TOOLS_H

#include <string>
#include <random>

namespace Vanadium
{

namespace Tools
{

std::string randomString(const int len)
{
    static const char alphanum[] =
            "0123456789"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz";

    std::string tmp_s;
    tmp_s.reserve(len);
    for (int i = 0; i < len; ++i)
        tmp_s += alphanum[random() % (sizeof(alphanum) - 1)];
    return tmp_s;
}

}

}

#endif //VANADIUM_TOOLS_H
