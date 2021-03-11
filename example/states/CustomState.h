#ifndef VANADIUM_CUSTOMSTATE_H
#define VANADIUM_CUSTOMSTATE_H

#include "../../src/include/vanadium/Vanadium.h"
#include "SvgModelContainer.h"
//#include "Gui.h"

using namespace Vanadium;

class Gui;

class CustomState : public State
{
private:
    Ref<Gui> gui;

    Ref<Texture> texture;
    Ref<Camera> camera;

    Ref<Shader> lineShader;
    Ref<Mesh> previewLayerMesh;

    Ref<Postprocessing> glow;
    Ref<Postprocessing> fastGlow;

    Ref<Framebuffer> framebufferForGui;
    Ref<Framebuffer> framebufferForLayerPreview;

    SvgModelContainer svgModelContainer;

    glm::vec2 windowViewportSize = glm::vec2(800, 600);

    VNfloat currentInterpolation = 0.726f;
    bool shouldUpdateModelPreview = false;

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

    SvgModelContainer *getModelContainer() noexcept;

    void renderLayerPreview() noexcept;
    void updateModelPreview() noexcept;


};


#endif //VANADIUM_CUSTOMSTATE_H
