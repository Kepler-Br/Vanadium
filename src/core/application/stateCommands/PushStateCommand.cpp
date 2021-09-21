#include "PushStateCommand.h"

#include "core/interfaces/StateStack.h"

namespace vanadium::state_stack_commands {

Push::Push(WeakRef<EngineEndStateStack> stateStack, Ref<State> state)
    : _stateStack(std::move(stateStack)), _state(std::move(state)) {}

void Push::execute() { this->_stateStack.lock()->push(this->_state); }

}  // namespace vanadium::state_stack_commands
