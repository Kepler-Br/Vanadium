#include "PushStateCommand.h"

#include "vanadium/core/interfaces/constructed/StateStack.h"

namespace vanadium::state_stack_commands {

Push::Push(EngineEndStateStack *stateStack, Ref<State> state)
    : _stateStack(stateStack), _state(std::move(state)) {}

void Push::execute() { this->_stateStack->push(this->_state); }

}  // namespace vanadium::state_stack_commands
