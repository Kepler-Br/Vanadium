#ifndef VANADIUM_CUSTOMSTATE_H
#define VANADIUM_CUSTOMSTATE_H

#include "../../src/include/vanadium/Vanadium.h"

using namespace Vanadium;

class CustomState : public State
{
private:
    UserEndApplication *application;
    UserEndEventProvider *eventProvider;
    UserEndStateStack *stateStack;
    std::string name;

public:
    void onAttach(UserEndApplication *application, const std::string &name) override;
    void onDetach() override;
    void loadResources(const std::function<void ()> &callback) override;
    void loadResources() override;
    void onTickStart() override;
    void onTickEnd() override;
    void update(double deltatime) override;
    void fixedUpdate(double deltatime) override;
    void preRender() override;
    void render() override;
    void postRender() override;
    const std::string &getName() const noexcept override;
    Ref<Framebuffer> getTargetFramebuffer() const noexcept override;

};


#endif //VANADIUM_CUSTOMSTATE_H
