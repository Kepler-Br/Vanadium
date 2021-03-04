#ifndef VANADIUM_PARSER_H
#define VANADIUM_PARSER_H

#include <string>
#include <vector>

#include "../../core/Types.h"

namespace Vanadium
{

namespace Svg
{


class Parser
{
private:
    std::string source;

    void parse();
public:
    Parser(std::string source);
};

class Rasterizer
{
public:
    static std::vector<VNfloat> opengl(VNint quality)
    {
        return std::vector<VNfloat>();
    }
};

}

}

#endif //VANADIUM_PARSER_H
