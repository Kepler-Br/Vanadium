#include "StateStackImpl.h"

#include "core/Log.h"
#include "core/application/ApplicationImpl.h"
#include "stateCommands/PopAllStatesCommand.h"
#include "stateCommands/PopStateCommand.h"
#include "stateCommands/PushStateCommand.h"

namespace vanadium {

StateStackImpl::StateStackImpl(WeakRef<EngineEndApplication> application)
    : _application(std::move(application)) {
  this->_commands.reserve(5);
  this->_states.reserve(5);
}

// Aka popAll();
StateStackImpl::~StateStackImpl() {
  for (const auto& state : this->_states) {
    state->_onDetach();
  }

  this->_states.clear();
}

#pragma region EngineEndStateStack

void StateStackImpl::push(Ref<State> state) {
  if (!this->_states.empty()) {
    this->_states.back()->_onStateLostPriority();
  }

  state->_onAttach(this->_application);

  this->_states.push_back(state);
}

void StateStackImpl::pop() {
  Ref<State> state = this->_states.back();

  state->_onDetach();
  this->_states.pop_back();

  if (!this->_states.empty()) {
    this->_states.back()->_onStateGainedPriority();
  }
}

void StateStackImpl::popAll() {
  for (const auto& state : this->_states) {
    state->_onDetach();
  }

  this->_states.clear();
}

void StateStackImpl::executeCommands() {
  for (const auto& command : this->_commands) {
    command->execute();
  }

  this->_commands.clear();
}

#pragma endregion

#pragma region StateStack

Ref<State> StateStackImpl::top() const noexcept { return this->_states.back(); }

Ref<State> StateStackImpl::get(size_t index) const noexcept {
  if (index >= this->_states.size()) {
    VAN_ENGINE_ERROR("Unable to retrieve state with index {}. Total states: {}",
                     index, this->_states.size());

    return nullptr;
  }
  return this->_states.back();
}

size_t StateStackImpl::size() const noexcept { return this->_states.size(); }

bool StateStackImpl::empty() const noexcept { return this->_states.empty(); }

void StateStackImpl::requestPush(Ref<State> state) noexcept {
  if (state == nullptr) {
    VAN_ENGINE_ERROR("U ok? Why are you passing state as nullptr?");
    return;
  }

  using namespace state_stack_commands;

  this->_commands.push_back(MakeRef<Push>(this, state));
}

void StateStackImpl::requestPop() noexcept {
  using namespace state_stack_commands;

  this->_commands.push_back(MakeRef<Pop>(this));
}

void StateStackImpl::requestPopAll() noexcept {
  using namespace state_stack_commands;

  this->_commands.push_back(MakeRef<PopAll>(this));
}

std::vector<Ref<State>>::iterator StateStackImpl::begin() {
  return this->_states.begin();
}

std::vector<Ref<State>>::iterator StateStackImpl::end() {
  return this->_states.end();
}

std::vector<Ref<State>>::reverse_iterator StateStackImpl::rbegin() {
  return this->_states.rbegin();
}

std::vector<Ref<State>>::reverse_iterator StateStackImpl::rend() {
  return this->_states.rend();
}

std::vector<Ref<State>>::const_iterator StateStackImpl::begin() const {
  return this->_states.begin();
}

std::vector<Ref<State>>::const_iterator StateStackImpl::end() const {
  return this->_states.end();
}

std::vector<Ref<State>>::const_reverse_iterator StateStackImpl::rbegin() const {
  return this->_states.rbegin();
}

std::vector<Ref<State>>::const_reverse_iterator StateStackImpl::rend() const {
  return this->_states.rend();
}

#pragma endregion

}  // namespace vanadium