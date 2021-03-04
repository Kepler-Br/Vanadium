#ifndef VANADIUM_SVG_TYPES_H
#define VANADIUM_SVG_TYPES_H

namespace Vanadium
{

namespace Svg
{

namespace Commands
{

enum class Type
{
    Unknown,
    Move,
    Line,
    HorizontalLine,
    VerticalLine,
    ClosePath,
    Cubic,
    Quadratic,
    CubicConnected,
};

enum class CoordinateType
{
    Unknown,
    Absolute,
    Relative,
};

}

}

}

#endif //VANADIUM_SVG_TYPES_H
