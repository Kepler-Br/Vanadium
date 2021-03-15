#ifndef VANADIUM_GUI_H
#define VANADIUM_GUI_H

#include "include/vanadium/Vanadium.h"
#include "../SvgModelContainer.h"
#include <imgui.h>


using namespace Vanadium;

class CustomState;

class Gui
{
public:
    enum class SelectedTreeItem
    {
        None = 0,
        Model,
        Group,
        KeyedElement,
        Key,
        DocumentLayer,
        Document,
    };

    struct Model
    {
    public:
        char itemName[256];
        glm::vec2 renderViewportSize = {1.0f, 1.0f};
        glm::vec2 previewViewportSize = {1.0f, 1.0f};

        glm::vec3 wireframeColor = glm::vec3(1.0f);
        glm::vec3 bodyColor = glm::vec3(0.0f, 0.0f, 0.0f);
        glm::vec3 auraColor = glm::vec3(1.0f, 0.0f, 0.0f);
        VNfloat interpolationSpeed = 0.6f;
        VNfloat glowPower = 0.6f;
        VNint quality = 5;
        VNint skipSteps = 5;
        bool skipInterpolationFrames = false;
        bool drawWireframes = false;
        bool drawWireframeOnly = false;
        bool drawBlur = true;
        bool overrideAuraColor = false;
        bool overrideBodyColor = false;
        bool overrideWireframeColor = false;

        bool isLocalCoordinateSystem = false;

        size_t modelID = 0;
        VNint blurQuality = 1;
        SelectedTreeItem currentlySelectedItemType = SelectedTreeItem::None;

        bool qualityChanged()
        {
            if (this->oldQuality != this->quality)
            {
                return true;
            }
            return false;
        }

        void update()
        {
            this->oldQuality = this->quality;
        }

    private:
        VNint oldQuality = this->quality;

    };

private:
    Model model;
    Ref<Framebuffer> renderFramebuffer;
    Ref<Framebuffer> framebufferLayerPreview;
    UserEndApplication *application;

    bool settingsWindowOpened = false;
    CustomState *state;

    void drawRenderViewPort();
    void drawSceneTreeWindow();
    void drawAccessoriesWindow();
    void drawOpenedSvgFilesTree();
    void drawPropertiesWindow();
    void drawMainWindow();
    void drawPreviewViewport();
    void drawSettingsWindow();

    static bool drawVec2Control(const std::string& label, glm::vec2& values, VNfloat resetValue = 0.0f, VNfloat columnWidth = 100.0f, VNfloat speed = 0.1f);

    void drawModelNode(size_t id);
    void drawGroupElementNode(size_t id);
    void drawKeyedElementNode(size_t id);
    void drawKeyNode(size_t id);

    void drawCurrentKeyProperties();
    void drawCurrentKeyedElementProperties();
    void drawCurrentGroupProperties();
    void drawCurrentModelProperties();

//    void drawModelElementNode(SvgModelContainer::Model &svgModel, SvgModelContainer::Element &svgElement,
//                              VNuint modelIndex, VNuint elementIndex);
//    void drawIntermediateElementNode(SvgModelContainer::Model &svgModel, SvgModelContainer::Element &svgElement, SvgModelContainer::Element &svgIntermediateElement,
//                                     VNuint modelIndex, VNuint elementIndex, VNuint intermediateElementIndex);
//     bool previewShouldBeUpdated = false;
//     bool previewWindowSizeChanged = false;
    bool isMouseClickedOnRenderViewport = false;

public:
    Gui(Ref<Framebuffer> renderFramebuffer, Ref<Framebuffer> framebufferLayerPreview, UserEndApplication *application, CustomState *state);
    ~Gui();

    void render();

    [[nodiscard]]
    Model *getModel() noexcept;
    ImVec2 mouseDelta;

    void processEvent(Event *event);
//    bool shouldBePreviewUpdated();
//    bool wasPreviewWindowSizeChanged();
};

#endif //VANADIUM_GUI_H
