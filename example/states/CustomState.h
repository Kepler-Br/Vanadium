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
    Ref<Mesh> arrow;
    Ref<Mesh> modelCenter;
    Ref<Mesh> scaleArrow;
    Ref<Mesh> cross;

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

    void drawArrows(const glm::vec2 &position, const glm::mat2 &transMatrix, VNfloat alpha = 1.0f);
    void drawScaleArrows(const glm::vec2 &position, const glm::mat2 &transMatrix, VNfloat alpha = 1.0f);
    void drawCircle(const glm::vec2 &position, VNfloat alpha = 1.0f);
    void drawCross(const glm::vec2 &position, const glm::vec4 &color);

    void renderSelected();
    void renderMarkedWireframeModels();
    void renderPatches(int layerNumber, bool affectAura, bool affectBodyColor);
    void renderBlur(int layerNumber);
    void renderBodies(int layerNumber);
    void renderModels();

    void drawModelWireframe(size_t id, const glm::vec4 &color = glm::vec4(1.0f), bool drawArrows = true);
    void drawGroupWireframe(size_t id, const glm::vec4 &color = glm::vec4(1.0f), bool drawArrows = true);
    void drawKeyElementWireframe(size_t id, const glm::vec4 &color = glm::vec4(1.0f), bool drawArrows = true);
    void drawKeyWireframe(size_t id, const glm::vec4 &color = glm::vec4(1.0f), bool drawArrows = true);

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
