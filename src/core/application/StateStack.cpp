#include "StateStack.h"

#include "core/Log.h"
#include "core/application/Application.h"
#include "stateCommands/PopAllStatesCommand.h"
#include "stateCommands/PopStateCommand.h"
#include "stateCommands/PushStateCommand.h"

namespace vanadium {

StateStack::StateStack(UserEndApplication *application)
    : _application(application) {
  this->_commands.reserve(5);
  this->_states.reserve(5);
}

StateStack::~StateStack() { this->popAll(); }

State *StateStack::top() const noexcept { return this->_states.back(); }

State *StateStack::get(size_t index) const noexcept {
  if (index >= this->_states.size()) {
    VAN_ENGINE_ERROR("Unable to retrieve state with index {}. Total states: {}",
                     index, this->_states.size());
    return nullptr;
  }
  return this->_states.back();
}

size_t StateStack::size() const noexcept { return this->_states.size(); }

void StateStack::requestPush(State *state, const std::string &name) noexcept {
  if (state == nullptr) {
    VAN_ENGINE_ERROR("U ok? Why are you passing state as nullptr?");
    return;
  }
  this->_commands.push_back(new state_stack_commands::Push(this, state, name));
}

void StateStack::requestPop() noexcept {
  this->_commands.push_back(new state_stack_commands::Pop(this));
}

void StateStack::requestPopAll() noexcept {
  this->_commands.push_back(new state_stack_commands::PopAll(this));
}

void StateStack::push(State *state, const std::string &name) {
  if (!this->_states.empty()) {
    this->_states.back()->_onStateLostPriority();
  }
  state->_onAttach(this->_application, name);
  this->_states.push_back(state);
}

void StateStack::pop() {
  State *state = this->_states.back();
  state->_onDetach();
  delete state;
  this->_states.pop_back();
  if (!this->_states.empty()) {
    this->_states.back()->_onStateGainedPriority();
  }
}

void StateStack::popAll() {
  for (auto *state : this->_states) {
    state->_onDetach();
    delete state;
  }
  this->_states.clear();
}

void StateStack::executeCommands() {
  for (auto *command : this->_commands) {
    command->execute();
    delete command;
  }
  this->_commands.clear();
}

}  // namespace vanadium