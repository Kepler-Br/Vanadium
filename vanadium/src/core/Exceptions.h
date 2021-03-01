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

// Should not be called otherwise than in Application preInit or postInit methods.
class InitializationInterrupted : public std::runtime_error
{
private:
    bool doShowDialog;

public:
    InitializationInterrupted(const std::string &msg, bool showDialog = true):
            std::runtime_error(msg),
            doShowDialog(showDialog)
    {}

    bool showDialog() const noexcept
    {
        return doShowDialog;
    }
};

// Should be called by state when some problem occurred.
class ExecutionInterrupted : public std::runtime_error
{
private:
    bool doShowDialog;

public:
    ExecutionInterrupted(const std::string &msg, bool showDialog = true):
            std::runtime_error(msg),
            doShowDialog(showDialog)
    {}

    bool showDialog() const noexcept
    {
        return doShowDialog;
    }
};

//class ForcePopState : public std::runtime_error
//{
//    using std::runtime_error::runtime_error;
//};

}

#endif //VANADIUM_EXCEPTIONS_H
