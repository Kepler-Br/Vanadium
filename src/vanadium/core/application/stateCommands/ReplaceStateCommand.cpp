#include "ReplaceStateCommand.h"

#include "vanadium/core/interfaces/StateStack.h"

namespace vanadium::state_stack_commands {

Replace::Replace(EngineEndStateStack *stateStack, Ref<State> state)
    : _stateStack(stateStack), _state(std::move(state)) {}

void Replace::execute() {
  this->_stateStack->pop();
  this->_stateStack->push(this->_state);
}

}  // namespace vanadium::state_stack_commands
