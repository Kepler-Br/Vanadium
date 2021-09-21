#include "PopAllStatesCommand.h"

#include "core/interfaces/StateStack.h"

namespace vanadium::state_stack_commands {

PopAll::PopAll(WeakRef<EngineEndStateStack> stateStack)
    : _stateStack(std::move(stateStack)) {}

void PopAll::execute() { this->_stateStack.lock()->popAll(); }

}  // namespace vanadium::state_stack_commands
