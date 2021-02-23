#ifndef VANADIUM_STATE_H
#define VANADIUM_STATE_H

#include <functional>
#warning "add getFramebuffer."



namespace Vanadium
{

class UserEndApplication;
class Framebuffer;

class State
{
public:
    virtual ~State() = default;

    virtual void onAttach(UserEndApplication *application) = 0;
    virtual void onDetach() = 0;
    virtual void loadResources(const std::function<void ()> &callback) = 0;
    virtual void loadResources() = 0;
    virtual void onTickStart() = 0;
    virtual void onTickEnd() = 0;
    virtual void update(double deltatime) = 0;
    virtual void fixedUpdate(double deltatime) = 0;
    virtual void preRender() = 0;
    virtual void render() = 0;
    virtual void postRender() = 0;
    virtual Framebuffer *getTargetFramebuffer() const noexcept = 0;

};

}

#endif //VANADIUM_STATE_H
