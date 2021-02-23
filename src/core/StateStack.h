#ifndef VANADIUM_STATESTACK_H
#define VANADIUM_STATESTACK_H

#include <vector>

#include "State.h"
#include "Command.h"

namespace Vanadium
{

class UserStateStack
{
public:
    virtual State *top() const noexcept = 0;
    virtual State *get(uint32_t index) const noexcept = 0;
    virtual uint32_t size() const noexcept = 0;
    virtual void requestPush(State *state) noexcept = 0;
    virtual void requestPop() noexcept = 0;
    virtual void requestPopAll() noexcept = 0;

};

#warning "Implement this."

class StateStack : public UserStateStack
{
private:
    std::vector<State *> states;
    std::vector<Command> stateCommands;

public:
    StateStack() = default;

    State *top() const noexcept override
    {
        return nullptr;
    }
    State *get(uint32_t index) const noexcept override
    {
        return nullptr;
    }
    uint32_t size() const noexcept override
    {
        return 0;
    }
    void requestPush(State *state) noexcept override
    {
    }
    void requestPop() noexcept override
    {
    }
    void requestPopAll() noexcept override
    {
    }

    void push(State *state)
    {

    }
    void pop(State *state)
    {

    }
    void popAll(State *state)
    {

    }

};

}


#endif //VANADIUM_STATESTACK_H
