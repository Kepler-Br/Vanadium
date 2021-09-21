#include "ReplaceStateCommand.h"

#include "core/interfaces/StateStack.h"

namespace vanadium::state_stack_commands {

Replace::Replace(WeakRef<EngineEndStateStack> stateStack, Ref<State> state)
    : _stateStack(std::move(stateStack)), _state(std::move(state)) {}

void Replace::execute() {
  Ref<EngineEndStateStack> stateStack = this->_stateStack.lock();

  stateStack->pop();
  stateStack->push(this->_state);
}

}  // namespace vanadium::state_stack_commands
