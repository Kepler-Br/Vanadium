#include "PopStateCommand.h"

#include "core/interfaces/StateStack.h"

namespace vanadium::state_stack_commands {

Pop::Pop(WeakRef<EngineEndStateStack> stateStack)
    : _stateStack(std::move(stateStack)) {}

void Pop::execute() { this->_stateStack.lock()->pop(); }

}  // namespace vanadium::state_stack_commands
