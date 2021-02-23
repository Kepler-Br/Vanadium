#ifndef VANADIUM_SHADERCOMPILATIONERROR_H
#define VANADIUM_SHADERCOMPILATIONERROR_H

namespace Vanadium
{

class ShaderCompilationError : public std::runtime_error
{
    using std::runtime_error::runtime_error;
};

}

#endif //VANADIUM_SHADERCOMPILATIONERROR_H
