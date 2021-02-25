#ifndef VANADIUM_EXCEPTIONS_H
#define VANADIUM_EXCEPTIONS_H

namespace Vanadium
{

class ShaderAssetParsingError : public std::runtime_error
{
    using std::runtime_error::runtime_error;
};

class ShaderCompilationError : public std::runtime_error
{
    using std::runtime_error::runtime_error;
};

}

#endif //VANADIUM_EXCEPTIONS_H
