#ifndef VANADIUM_CUSTOMSTATE_H
#define VANADIUM_CUSTOMSTATE_H

#include "../../src/include/vanadium/Vanadium.h"

using namespace Vanadium;

class CustomState : public State
{
private:
    Ref<Shader> shader;
    Ref<Texture> texture;
    Ref<Mesh> mesh;
    Ref<Camera> camera;
    Ref<Framebuffer> framebuffer;

    Ref<Mesh> screenPlane;
    Ref<Shader> framebufferShader;

    Ref<Shader> lineShader;
    Ref<Mesh> svgPath;
    Ref<Mesh> svgPathTriangulated;

    void setUpEvents() noexcept;
    void onKeyPressed(KeyPressedEvent *event) noexcept;
    void onKeyReleased(KeyReleasedEvent *event) noexcept;
    void onWindowClose(WindowCloseEvent *event) noexcept;
    void onWindowResized(WindowSizeChangedEvent *event) noexcept;
    void onMouseMove(MouseMoveEvent *event) noexcept;
    void onMouseScroll(MouseScrollEvent *event) noexcept;

public:
    void onAttach(UserEndApplication *application, const std::string &name) override;
    void onDetach() override;
    void onStateLostPriority() override;
    void onStateGainedPriority() override;
    void loadResources(const std::function<void ()> &callback) override;
    void loadResources() override;
    void onTickStart() override;
    void onTickEnd() override;
    void update(double deltatime) override;
    void fixedUpdate(double deltatime) override;
    void preRender() override;
    void render() override;
    void postRender() override;
    [[nodiscard]]
    const std::string &getName() const noexcept override;
//    Ref<Framebuffer> getTargetFramebuffer() const noexcept override;

};


#endif //VANADIUM_CUSTOMSTATE_H
