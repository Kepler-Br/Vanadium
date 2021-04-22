#include "core/StateStack.h"

#include "core/Log.h"
#include "stateCommands/PopAllStatesCommand.h"
#include "stateCommands/PopStateCommand.h"
#include "stateCommands/PushStateCommand.h"
#include "core/Application.h"

namespace Vanadium {

StateStack::StateStack(UserEndApplication *application)
    : application(application) {
  this->commands.reserve(5);
  this->states.reserve(5);
}

StateStack::~StateStack() { this->popAll(); }

State *StateStack::top() const noexcept { return this->states.back(); }

State *StateStack::get(VNsize index) const noexcept {
  if (index >= this->states.size()) {
    VAN_ENGINE_ERROR("Unable to retrieve state with index {}. Total states: {}",
                     index, this->states.size());
    return nullptr;
  }
  return this->states.back();
}

VNsize StateStack::size() const noexcept { return this->states.size(); }

void StateStack::requestPush(State *state, const std::string &name) noexcept {
  if (state == nullptr) {
    VAN_ENGINE_ERROR("U ok? Why are you passing state as nullptr?");
    return;
  }
  this->commands.push_back(new StateStackCommands::Push(this, state, name));
}

void StateStack::requestPop() noexcept {
  this->commands.push_back(new StateStackCommands::Pop(this));
}

void StateStack::requestPopAll() noexcept {
  this->commands.push_back(new StateStackCommands::PopAll(this));
}

void StateStack::push(State *state, const std::string &name) {
  if (!this->states.empty()) this->states.back()->_onStateLostPriority();
  state->_onAttach(this->application, name);
  this->states.push_back(state);
}

void StateStack::pop() {
  State *state = this->states.back();
  state->_onDetach();
  delete state;
  this->states.pop_back();
  if (!this->states.empty()) this->states.back()->_onStateGainedPriority();
}

void StateStack::popAll() {
  for (auto *state : this->states) {
    state->_onDetach();
    delete state;
  }
  this->states.clear();
}

void StateStack::executeCommands() {
  for (auto *command : this->commands) {
    command->execute();
    delete command;
  }
  this->commands.clear();
}

}  // namespace Vanadium