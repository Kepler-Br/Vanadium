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
    Ref<PositionCamera> guiViewportCamera;
    Ref<PositionCamera> guiPreviewViewportCamera;

    Ref<Shader> plainColorShader;
    Ref<Mesh> grid;
    Ref<Mesh> unitWireframePlane;
    Ref<Mesh> screenPlane;

    Ref<Postprocessing> blurPostProcessing;

    Ref<Shader> slowBlurShader;
    Ref<Shader> blurShader;
    Ref<Shader> fastBlurShader;
    Ref<Shader> plainColor2D;

    Ref<Framebuffer> framebuffer1;
    Ref<Framebuffer> framebuffer2;
    Ref<Framebuffer> framebufferMain;
    Ref<Framebuffer> framebufferPreview;

    SvgModelContainer svgModelContainer;

    glm::vec2 windowViewportSize = glm::vec2(800, 600);

    VNfloat previewCameraScale = 1.0f;
    VNfloat targetPreviewCameraScale = 1.0f;
    VNfloat mainCameraScale = 10.0f;
    VNfloat targetMainCameraScale = 1.0f;
    glm::vec2 mainCameraPosition = glm::vec2(0.0f);
    glm::vec2 targetMainCameraPosition = glm::vec2(0.0f);

    void setUpEvents() noexcept;
    void onKeyPressed(KeyPressedEvent *event) noexcept;
    void onKeyReleased(KeyReleasedEvent *event) noexcept;
    void onWindowClose(WindowCloseEvent *event) noexcept;
    void onWindowResized(WindowSizeChangedEvent *event) noexcept;
    void onMouseMove(MouseMoveEvent *event) noexcept;
    void onMouseScroll(MouseScrollEvent *event) noexcept;

    void initSvgModelContainer() noexcept;

    void renderModels();
    void drawModelWireframe(const SvgModelContainer::Model &model,
                            const glm::vec4 &color = glm::vec4(1.0f));
    void drawGroupWireframe(const SvgModelContainer::Group &group,
                            const glm::vec4 &color = glm::vec4(1.0f),
                            const glm::mat2 &rot = glm::mat2(1.0f),
                            const glm::mat2 &scale = glm::mat2(1.0f),
                            const glm::vec2 &pos = glm::vec2(0.0f));
    void drawKeyElementWireframe(const SvgModelContainer::KeyedElement &keyedElement,
                                 const glm::vec4 &color = glm::vec4(1.0f),
                                 const glm::mat2 &rot = glm::mat2(1.0f),
                                 const glm::mat2 &scale = glm::mat2(1.0f),
                                 const glm::vec2 &pos = glm::vec2(0.0f));
    void drawElementWireframe(const SvgModelContainer::Element &element,
                                 const glm::vec4 &color = glm::vec4(1.0f),
                                 const glm::mat2 &rot = glm::mat2(1.0f),
                                 const glm::mat2 &scale = glm::mat2(1.0f),
                                 const glm::vec2 &pos = glm::vec2(0.0f));
    void renderPreview() noexcept;

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

    void onGuiViewportSizeChange(const glm::vec2 &newViewportSize);
    void onGuiPreviewViewportSizeChange(const glm::vec2 &newGeometry);

    Ref<PositionCamera> getPreviewCamera() noexcept;
    Ref<PositionCamera> getMainRenderCamera() noexcept;

    void setMainCameraScale(VNfloat scale);
    void addMainCameraScale(VNfloat scale);
    VNfloat getMainCameraScale();

    void setPreviewCameraScale(VNfloat scale);
    void addPreviewCameraScale(VNfloat scale);

    void setMainCameraPosition(const glm::vec2 &newPosition);
    void addMainCameraPosition(const glm::vec2 &newPosition);


};


#endif //VANADIUM_CUSTOMSTATE_H
