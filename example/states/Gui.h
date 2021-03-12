#ifndef VANADIUM_GUI_H
#define VANADIUM_GUI_H

#include "include/vanadium/Vanadium.h"
#include "SvgModelContainer.h"


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
        Element,
        DocumentLayer,
        Document,
    };

    struct Model
    {
    public:
        glm::vec2 renderViewportSize = {1.0f, 1.0f};
        glm::vec2 previewViewportSize = {1.0f, 1.0f};

        glm::vec3 borderColor = glm::vec3(1.0f);
        glm::vec3 fillColor = glm::vec3(0.0f, 0.0f, 0.0f);
        glm::vec3 auraColor = glm::vec3(1.0f, 0.0f, 0.0f);
        VNfloat interpolationSpeed = 0.6f;
        VNfloat glowPower = 0.5f;
        VNint quality = 5;
        VNint skipSteps = 5;
        bool isFastBlur = false;
        bool skipInterpolationFrames = false;
        bool drawBorders = false;
        bool drawBlur = true;
        bool drawBody = true;

        VNuint modelSelectedIndex = 0;
        VNuint elementSelectedIndex = 0;
        VNuint documentLayerSelectedIndex = 0;
        VNuint documentSelectedIndex = 0;
        VNuint groupSelectedIndex = 0;
        VNuint keyedElementSelectedIndex = 0;
        SelectedTreeItem currentlySelectedItemType = SelectedTreeItem::None;

        bool qualityChanged()
        {
            if (this->oldQuality != this->quality)
            {
                return true;
            }
            return false;
        }

        bool selectedIndexesChanged()
        {
//            if (this->oldDocumentLayerSelectedIndex != this->documentLayerSelectedIndex ||
//                this->oldDocumentSelectedIndex != this->documentSelectedIndex ||
//                this->oldElementSelectedIndex != this->elementSelectedIndex ||
//                this->oldModelSelectedIndex != this->modelSelectedIndex ||
//                this->oldIntermediateElementSelectedIndex != this->intermediateElementSelectedIndex)
//            {
//                return true;
//            }
//            return false;
            return false;
        }

        bool selectedItemTypeChanged()
        {
            if (this->oldCurrentlySelectedItemType != this->currentlySelectedItemType)
            {
                return true;
            }
            return false;
        }

        bool renderViewportSizeChanged()
        {
//            if (this->oldDocumentLayerRendererViewportSize != this->previewViewportSize)
//            {
//                return true;
//            }
            return false;
        }

        void update()
        {
//            this->oldDocumentSelectedIndex = this->documentSelectedIndex;
//            this->oldDocumentLayerSelectedIndex = this->documentLayerSelectedIndex;
//            this->oldDocumentLayerRendererViewportSize = this->previewViewportSize;
//            this->oldElementSelectedIndex = this->elementSelectedIndex;
//            this->oldModelSelectedIndex = this->modelSelectedIndex;
//            this->oldIntermediateElementSelectedIndex = this->intermediateElementSelectedIndex;

            this->oldCurrentlySelectedItemType = this->currentlySelectedItemType;

            this->oldQuality = this->quality;
        }

    private:
//        glm::vec2 oldDocumentLayerRendererViewportSize = this->previewViewportSize;
//        VNuint oldDocumentLayerSelectedIndex = this->documentLayerSelectedIndex;
//        VNuint oldDocumentSelectedIndex = this->documentSelectedIndex;
//        VNuint oldElementSelectedIndex = this->elementSelectedIndex;
//        VNuint oldModelSelectedIndex = this->modelSelectedIndex;
//        VNuint oldIntermediateElementSelectedIndex = this->intermediateElementSelectedIndex;

        SelectedTreeItem oldCurrentlySelectedItemType = currentlySelectedItemType;
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
    void drawOpenedSvgFilesTree();
    void drawPropertiesWindow();
    void drawMainWindow();
    void drawPreviewViewport();
    static void drawVec2Control(const std::string& label, glm::vec2& values, VNfloat resetValue = 0.0f, VNfloat columnWidth = 100.0f, VNfloat speed = 0.1f);

    void drawModelNode(SvgModelContainer::Model &svgModel, VNuint modelIndex);
    void drawGroupElementNode(SvgModelContainer::Group &svgGroup, VNuint modelIndex, VNuint groupIndex);
    void drawKeyedElementNode(SvgModelContainer::KeyedElement &svgKeyedElement, VNuint modelIndex, VNuint groupIndex, VNuint keyedElementIndex);
    void drawKeyNode(SvgModelContainer::Element &svgKey, VNuint modelIndex, VNuint groupIndex, VNuint keyedElementIndex, VNuint keyIndex);
//    void drawModelElementNode(SvgModelContainer::Model &svgModel, SvgModelContainer::Element &svgElement,
//                              VNuint modelIndex, VNuint elementIndex);
//    void drawIntermediateElementNode(SvgModelContainer::Model &svgModel, SvgModelContainer::Element &svgElement, SvgModelContainer::Element &svgIntermediateElement,
//                                     VNuint modelIndex, VNuint elementIndex, VNuint intermediateElementIndex);
     bool previewShouldBeUpdated = false;
     bool previewWindowSizeChanged = false;

public:
    Gui(Ref<Framebuffer> renderFramebuffer, Ref<Framebuffer> framebufferLayerPreview, UserEndApplication *application, CustomState *state);
    ~Gui();

    void render();

    [[nodiscard]]
    Model *getModel() noexcept;

    void drawSettingsWindow();
    void processEvent(Event *event);
    bool shouldBePreviewUpdated();
    bool wasPreviewWindowSizeChanged();
};

#endif //VANADIUM_GUI_H
