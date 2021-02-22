#ifndef VANADIUM_STATE_H
#define VANADIUM_STATE_H

#include <functional>

class UserEndApplication;

namespace Van
{

class State
{
public:
    virtual void onAttach(UserEndApplication *application) = 0;
    virtual void onDetach() = 0;
    virtual void loadResources(const std::function<void ()> &callback)
    {
        this->loadResources();
        callback();
    }
    virtual void loadResources() = 0;
    virtual void onTickStart() = 0;
    virtual void onTickEnd() = 0;
    virtual void update(double deltatime) = 0;
    virtual void fixedUpdate(double deltatime) = 0;
    virtual void preRender() = 0;
    virtual void render() = 0;
    virtual void postRender() = 0;

};

}

#endif //VANADIUM_STATE_H
