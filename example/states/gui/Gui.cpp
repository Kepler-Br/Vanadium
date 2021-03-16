#include "Gui.h"
#include "../imgui_sdl.h"
#include "../imgui_opengl3.h"
//#include <imgui.h>
#include <imgui_internal.h>
#include "platform/default/DefaultWindow.h"
#include "platform/opengl/OpenGLFramebuffer.h"
#include "../CustomState.h"
#include "ThemeSelector.h"

void Gui::drawRenderViewPort()
{

//    printf("%f %f\n", mouseDelta.x, mouseDelta.y);
    if(ImGui::Begin("Render viewport"))
    {
        ImGui::BeginChild("Render side");
//        if(ImGui::IsWindowHovered() && ImGui::IsMouseDragging(ImGuiMouseButton_Left))
        if(ImGui::IsWindowHovered() && ImGui::IsMouseClicked(ImGuiMouseButton_Middle))
        {
            this->isMouseClickedOnRenderViewport = true;
        }
        if(ImGui::IsWindowHovered() && ImGui::IsMouseClicked(ImGuiMouseButton_Left))
        {
//            this->model.currentlySelectedItemType = SelectedTreeItem::None;
            this->model.selectedModels.clear();
            this->model.currentlySelectedItemType = SelectedTreeItem::None;
        }

        if (ImGui::IsWindowHovered())
        {
            ImGuiIO &io = ImGui::GetIO();
            this->state->addMainCameraScale(-io.MouseWheel/10.0f);
        }
        if (!ImGui::IsMouseDown(ImGuiMouseButton_Middle))
        {
            this->isMouseClickedOnRenderViewport = false;
        }
        if (this->isMouseClickedOnRenderViewport)
        {
            ImGui::SetMouseCursor(ImGuiMouseCursor_ResizeAll);
            Ref<PositionCamera> camera = this->state->getMainRenderCamera();
            glm::vec3 right = camera->getRight();
            glm::vec3 newPosition = camera->getRight() * (this->mouseDelta.x/100.0f);
            newPosition += -camera->getUp() * (this->mouseDelta.y/100.0f);
            newPosition *= this->state->getMainCameraScale();
            this->state->addMainCameraPosition(newPosition);
        }

        ImVec2 wsize = ImGui::GetWindowSize();

        VNuint tex = *(VNuint *)this->renderFramebuffer->getColorAttachment(0);
        ImGui::Image((void*)(intptr_t)tex, wsize, ImVec2(0, 1), ImVec2(1, 0));
        if (wsize.x != this->model.renderViewportSize.x ||
            wsize.y != this->model.renderViewportSize.y)
        {
            this->model.renderViewportSize = {wsize.x, wsize.y};
            this->state->onGuiViewportSizeChange(this->model.renderViewportSize);
        }
        ImGui::EndChild();
    }
    ImGui::End();
}

void Gui::drawSceneTreeWindow()
{
    if(ImGui::Begin("Scene tree"))
    {
        SvgModelContainer *container = this->state->getModelContainer();
        for (auto modelID : container->getModelsIDs())
        {
            this->drawModelNode(modelID);
        }
    }
    ImGui::End();
}

void Gui::drawAccessoriesWindow()
{
//    if(ImGui::Begin("Accessories"))
//    {
//        SvgModelContainer *container = this->state->getModelContainer();
//        auto svgModels = container->getModels();
//        VNuint modelIndex = 0;
//        for (auto &svgModel : svgModels)
//        {
//            this->drawModelNode(svgModel.second, modelIndex);
//            modelIndex++;
//        }
//    }
//    ImGui::End();
}

void Gui::drawOpenedSvgFilesTree()
{
    if(ImGui::Begin("Opened SVG files"))
    {
        SvgModelContainer *container = this->state->getModelContainer();
        auto &documentContainer = container->getDocuments();
        VNuint documentIndex = 0;
        for (auto &document : documentContainer)
        {
            ImGuiTreeNodeFlags svgNodeFlags = ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_OpenOnArrow;
            if (this->model.currentlySelectedItemType == SelectedTreeItem::Document &&
                this->model.documentSelectedIndex == documentIndex)
            {
                svgNodeFlags |= ImGuiTreeNodeFlags_Selected;
            }
            bool activated = ImGui::TreeNodeEx(document.first.c_str(), svgNodeFlags);
            if(ImGui::IsItemClicked())
            {
                this->model.currentlySelectedItemType = SelectedTreeItem::Document;
                this->model.documentSelectedIndex = documentIndex;
                this->model.selectedModels.clear();
            }
            if (ImGui::BeginPopupContextItem())
            {
                if (ImGui::MenuItem("Close document"))
                    ;
                ImGui::EndPopup();
            }
            if (activated)
            {
                ImGui::PushID(document.first.c_str());
                VNuint layerIndex = 0;
                for (auto *layer : document.second->getLayers())
                {
                    ImGuiTreeNodeFlags svgNodeLeafFlags = ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_Leaf;
                    if (this->model.currentlySelectedItemType == SelectedTreeItem::DocumentLayer &&
                        this->model.documentLayerSelectedIndex == layerIndex &&
                        this->model.documentSelectedIndex == documentIndex)
                    {
                        svgNodeLeafFlags |= ImGuiTreeNodeFlags_Selected;
                    }
                    ImGui::PushID(layer->getName().c_str());
                    if (ImGui::TreeNodeEx(layer->getName().c_str(), svgNodeLeafFlags))
                    {
                        if(ImGui::IsItemClicked())
                        {
                            this->model.selectedModels.clear();
                            this->model.currentlySelectedItemType = SelectedTreeItem::DocumentLayer;
                            this->model.documentLayerSelectedIndex = layerIndex;
                            this->model.documentSelectedIndex = documentIndex;
                        }
                        ImGui::TreePop();
                    }
                    ImGui::PopID();
                    layerIndex++;
                }
                ImGui::PopID();
                ImGui::TreePop();
            }
            documentIndex++;
        }


//        if (ImGui::TreeNodeEx("Some label", flags))
//        {
//            flags |= ImGuiTreeNodeFlags_Leaf;
//
//            ImGui::TreeNodeEx("Basic", flags, "Oh noes");
//            ImGuiDragDropFlags src_flags = 0;
//            src_flags |= ImGuiDragDropFlags_SourceNoDisableHover;     // Keep the source displayed as hovered
//            src_flags |= ImGuiDragDropFlags_SourceNoHoldToOpenOthers; // Because our dragging is local, we disable the feature of opening foreign treenodes/tabs while dragging
//            //src_flags |= ImGuiDragDropFlags_SourceNoPreviewTooltip; // Hide the tooltip
//            if (ImGui::BeginDragDropSource(src_flags))
//            {
//                if (!(src_flags & ImGuiDragDropFlags_SourceNoPreviewTooltip))
//                    ImGui::Text("Moving ");
//                const char *text = "test/move/ha";
//                ImGui::SetDragDropPayload("DND_DEMO_NAME", text, strlen(text));
//                ImGui::EndDragDropSource();
//            }
//
//            if (ImGui::BeginPopupContextItem())
//            {
//                if (ImGui::MenuItem("Delete Entity"))
//                    ;
//                ImGui::Separator();
//                ImGui::MenuItem("I'm sorry");
//                ImGui::EndPopup();
//            }
//            ImGui::TreePop();
//            ImGui::TreePop();
//        }

    }
    ImGui::End();
}

void Gui::drawPropertiesWindow()
{
    if(ImGui::Begin("Properties"))
    {
        if (this->model.selectedModels.size() == 1)
        {
            size_t id = *this->model.selectedModels.begin();
            SvgModel::ModelType type = this->state->getModelContainer()->getType(id);
            switch (type)
            {
                case SvgModel::ModelType::Model:
                    this->drawCurrentModelProperties();
                    break;
                case SvgModel::ModelType::Group:
                    this->drawCurrentGroupProperties();
                    break;
                case SvgModel::ModelType::KeyedElement:
                    this->drawCurrentKeyedElementProperties();
                    break;
                case SvgModel::ModelType::Key:
                    this->drawCurrentKeyProperties();
                    break;
                default:
                    break;
            }
        }
    }
    ImGui::End();


//    if(ImGui::Begin("Properties"))
//    {
//        SvgModelContainer *container = this->state->getModelContainer();
//        if (this->model.currentlySelectedItemType == SelectedTreeItem::DocumentLayer)
//        {
//            ImGui::Text("Document layer properties:");
//            ImGui::Separator();
//            const std::string &documentPath = container->getDocumentPathByIndex(this->model.documentSelectedIndex);
//            Ref<Svg::Document> document = container->getDocuments()[documentPath];
//            Svg::Layer *layer = document->getLayers()[this->model.documentLayerSelectedIndex];
//            ImGui::Text("Document path: %s", documentPath.c_str());
//            ImGui::Text("Layer name: %s", layer->getName().c_str());
//        }
//        if (this->model.currentlySelectedItemType == SelectedTreeItem::Element)
//        {
//            ImGui::Text("Model element properties:");
//            ImGui::Separator();
//            SvgModelContainer *modelContainer = this->state->getModelContainer();
//            SvgModelContainer::Model *svgModel = modelContainer->getModelByIndex(this->model.modelSelectedIndex);
//            SvgModelContainer::ModelElement *svgElement = &svgModel->elements[this->model.elementSelectedIndex];
//            ImGui::Text("Model name: %s", modelContainer->getModelNameByIndex(this->model.modelSelectedIndex).c_str());
//            ImGui::Text("Element name: %s", svgElement->name.c_str());
//            ImGui::Text("Vertices total: %lu", svgElement->vertices.size());
//            ImGui::Text("Is root element: %s", this->model.elementSelectedIndex == 0 ? "Yes" : "No");
//            ImGui::Text("Intermediate elements count: %lu", svgElement->intermediateElements.size());
//            if (this->model.elementSelectedIndex != 0)
//            {
//                ImGui::Text("Interpolation: ");
//                ImGui::SliderFloat("###svgElementInterpolation", &svgElement->targetInterpolation, 0.0f, 1.0f);
//            }
//
//            Gui::drawVec2Control("Position", svgElement->position, 0.0f, 100.0f, 0.001f);
//            Gui::drawVec2Control("Scale", svgElement->scale, 0.0f, 100.0f, 0.01f);
//            ImGui::Text("Rotation:");
//            ImGui::DragFloat("###Rotation", &svgElement->rotation, 0.5f);
//        }
//        if (this->model.currentlySelectedItemType == SelectedTreeItem::Model)
//        {
//            ImGui::Text("Model properties:");
//            ImGui::Separator();
//            SvgModelContainer *modelContainer = this->state->getModelContainer();
//            SvgModelContainer::Model *svgModelByIndex = modelContainer->getModelByIndex(this->model.modelSelectedIndex);
//            ImGui::Text("Model name:");
//            static char *ssss = new char[256];
//            ImGui::InputText("###Model name", ssss, 256);
//            ImGui::Button("Submit name");
//            static glm::vec2 pos;
//            Gui::drawVec2Control("Position", pos, 0.0f, 100.0f, 0.001f);
//            Gui::drawVec2Control("Scale", pos, 1.0f, 100.0f, 0.01f);
//            static VNfloat rotation;
//            ImGui::Text("Rotation:");
//            ImGui::DragFloat("###Rotation", &rotation, 0.5f);
//            ImGui::Spacing();
//            ImGui::Separator();
//
//            if (svgModelByIndex->elements.empty())
//            {
//                ImGui::Text("Root element: NONE");
//            }
//            else
//            {
//                ImGui::Text("Root element: %s", svgModelByIndex->elements[0].name.c_str());
//            }
//            ImGui::Text("Element count: %lu", svgModelByIndex->elements.size());
//            ImGui::Separator();
//
//            static bool drawAsWireframe = false;
//            ImGui::Checkbox("Draw as wireframe", &drawAsWireframe);
//            ImGui::Separator();
//
//            ImGui::Text("Interpolations:");
//            for (VNuint elementIndex = 1; elementIndex < svgModelByIndex->elements.size(); elementIndex++)
//            {
//                SvgModelContainer::ModelElement *element = &svgModelByIndex->elements[elementIndex];
//                ImGui::PushID(elementIndex);
//                ImGui::Text("%s", element->name.c_str());
//                if (ImGui::SliderFloat("###svgModelElementInterpolation", &element->targetInterpolation, 0.0f, 1.0f))
//                    this->state->updateModelPreview();
//                ImGui::PopID();
//            }
//        }
//        if (this->model.currentlySelectedItemType == SelectedTreeItem::Document)
//        {
//            ImGui::Text("Document properties:");
//            ImGui::Separator();
//            const std::string &documentPath = container->getDocumentPathByIndex(this->model.documentSelectedIndex);
//            Ref<Svg::Document> document = container->getDocuments()[documentPath];
//            ImGui::Text("Document path: %s", documentPath.c_str());
//            ImGui::Text("Document total layers: %lu", document->getLayers().size());
//        }





















//        for (VNint i = 0; i < interpolations.size(); i ++)
//        {
//            Item &item = this->interpolations[i];
//            ImGui::PushID(i);
//            ImGui::InputText("###InterpolationPath", (char *)item.name.c_str(), item.name.size(), ImGuiInputTextFlags_ReadOnly);
//
//            if (ImGui::BeginDragDropTarget())
//            {
//                ImGuiDragDropFlags target_flags = 0;
////                target_flags |= ImGuiDragDropFlags_AcceptNoDrawDefaultRect; // Don't display the yellow rectangle
//                if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("DND_DEMO_NAME", target_flags))
//                {
//                    const char *input = (const char*)payload->Data;
//                    item.name = std::string(input);
//                }
//                ImGui::EndDragDropTarget();
//            }
//            ImGui::SameLine(0.0f, 0.0f);
//            if(ImGui::Button("Clear"))
//            {
//                item.name = "None";
//            }
//            ImGui::SameLine(0.0f, 0.0f);
//            ImGui::Button("Remove");
//            const VNfloat sliderMin = this->model.extrapolation ? -5.0f : 0.0f;
//            const VNfloat sliderMax = this->model.extrapolation ? 5.0f : 1.0f;
//            ImGui::SliderFloat("###Object interpolation slider", &item.interpolation, sliderMin, sliderMax);
//            item.interpolation = glm::clamp(item.interpolation, sliderMin, sliderMax);
//            ImGui::PopID();
//        }











//    }
//    ImGui::End();

}


void Gui::drawMainWindow()
{
    ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->Pos);
    ImGui::SetNextWindowSize(viewport->Size);
    ImGui::SetNextWindowViewport(viewport->ID);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

    ImGuiWindowFlags windowFlags =
            ImGuiWindowFlags_MenuBar |
            ImGuiWindowFlags_NoDocking |
            ImGuiWindowFlags_NoTitleBar |
            ImGuiWindowFlags_NoCollapse |
            ImGuiWindowFlags_NoResize |
            ImGuiWindowFlags_NoMove |
            ImGuiWindowFlags_NoBringToFrontOnFocus;

    ImGui::Begin("SVG shapeshifter", nullptr, windowFlags);
    {
        ImGui::PopStyleVar(3);

        if (ImGui::BeginMenuBar())
        {
            if (ImGui::BeginMenu("File"))
            {
                if (ImGui::MenuItem("New", NULL, false))
                    printf("Oh my!\n");
                if (ImGui::MenuItem("Open...", NULL, false))
                    printf("Oh my!\n");
                if (ImGui::MenuItem("Reload from disk", NULL, false))
                    printf("Oh my!\n");
                ImGui::Separator();


                if (ImGui::MenuItem("Exit", NULL, false))
                    ;
                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("View"))
            {
                if (ImGui::MenuItem("Settings", "", false))
                    this->settingsWindowOpened = true;
                if (ImGui::MenuItem("Logs", "", false))
                    ;
                if (ImGui::BeginMenu("Theme"))
                {
                    bool selected;
                    selected = ThemeSelector::getCurrent() == ThemeSelector::Theme::Classic;
                    if (ImGui::MenuItem("Classic", "", selected))
                    {
                        ThemeSelector::setTheme(ThemeSelector::Theme::Classic);
                    }

                    selected = ThemeSelector::getCurrent() == ThemeSelector::Theme::Dark;
                    if (ImGui::MenuItem("Dark", "", selected))
                    {
                        ThemeSelector::setTheme(ThemeSelector::Theme::Dark);
                    }

                    selected = ThemeSelector::getCurrent() == ThemeSelector::Theme::Light;
                    if (ImGui::MenuItem("Light", "", selected))
                    {
                        ThemeSelector::setTheme(ThemeSelector::Theme::Light);
                    }

                    selected = ThemeSelector::getCurrent() == ThemeSelector::Theme::Reddish;
                    if (ImGui::MenuItem("Reddish", "", selected))
                    {
                        ThemeSelector::setTheme(ThemeSelector::Theme::Reddish);
                    }

                    selected = ThemeSelector::getCurrent() == ThemeSelector::Theme::Grayish;
                    if (ImGui::MenuItem("Grayish", "", selected))
                    {
                        ThemeSelector::setTheme(ThemeSelector::Theme::Grayish);
                    }

                    selected = ThemeSelector::getCurrent() == ThemeSelector::Theme::Blender;
                    if (ImGui::MenuItem("Blender", "", selected))
                    {
                        ThemeSelector::setTheme(ThemeSelector::Theme::Blender);
                    }

                    selected = ThemeSelector::getCurrent() == ThemeSelector::Theme::Source;
                    if (ImGui::MenuItem("Source", "", selected))
                    {
                        ThemeSelector::setTheme(ThemeSelector::Theme::Source);
                    }

                    ImGui::EndMenu();
                }
                ImGui::Separator();
                ImGui::EndMenu();
            }

        }
        ImGui::EndMenuBar();

        ImGuiDockNodeFlags dockspaceFlags = ImGuiDockNodeFlags_None;
        ImGuiID dockspaceID = ImGui::GetID("ID().c_str()");
        if (!ImGui::DockBuilderGetNode(dockspaceID))
        {
            ImGui::DockBuilderRemoveNode(dockspaceID);
            ImGui::DockBuilderAddNode(dockspaceID, ImGuiDockNodeFlags_None);

            ImGuiID dock_main_id = dockspaceID;
            ImGuiID dock_right_id = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Right, 0.3f, nullptr,
                                                                &dock_main_id);
            ImGuiID dock_left_id = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Left, 0.6f, nullptr,
                                                               &dock_main_id);
            ImGuiID dock_right_up_id = ImGui::DockBuilderSplitNode(dock_right_id, ImGuiDir_Up, 0.3f, nullptr,
                                                                   &dock_right_id);
            ImGuiID dock_right_down_id = ImGui::DockBuilderSplitNode(dock_right_id, ImGuiDir_Down, 0.4f, nullptr,
                                                                   &dock_right_id);
            ImGuiID dock_left_down_id = ImGui::DockBuilderSplitNode(dock_left_id, ImGuiDir_Down, 0.15f, nullptr,
                                                                     &dock_left_id);

            ImGui::DockBuilderDockWindow("Render viewport", dock_left_id);
            ImGui::DockBuilderDockWindow("Properties", dock_right_id);
            ImGui::DockBuilderDockWindow("Scene tree", dock_right_up_id);
            ImGui::DockBuilderDockWindow("Accessories", dock_right_up_id);
            ImGui::DockBuilderDockWindow("Opened SVG files", dock_left_down_id);
            ImGui::DockBuilderDockWindow("Document layer renderer", dock_right_down_id);
            ImGuiDockNode *node = ImGui::DockBuilderGetNode(dock_right_id);
            node->LocalFlags |= ImGuiDockNodeFlags_NoTabBar;
            node = ImGui::DockBuilderGetNode(dock_left_id);
            node->LocalFlags |= ImGuiDockNodeFlags_NoTabBar;
            node = ImGui::DockBuilderGetNode(dock_right_up_id);
            node->LocalFlags |= ImGuiDockNodeFlags_NoWindowMenuButton;
            node = ImGui::DockBuilderGetNode(dock_left_down_id);
            node->LocalFlags |= ImGuiDockNodeFlags_NoWindowMenuButton;
//            node = ImGui::DockBuilderGetNode(dock_right_down_id);
//            node->LocalFlags |= ImGuiDockNodeFlags_NoTabBar;

            ImGui::DockBuilderFinish(dock_main_id);
        }
        ImGui::DockSpace(dockspaceID, ImVec2(0.0f, 0.0f), dockspaceFlags);
    }
    ImGui::End();
}

void Gui::drawSettingsWindow()
{
    ImGuiWindowFlags flags = ImGuiWindowFlags_NoCollapse;

    bool activated = ImGui::Begin("Settings window", &this->settingsWindowOpened, flags);
    if (activated)
    {
        ImGui::SliderFloat("Interpolation speed", &this->model.interpolationSpeed, 0.01f, 1.0f);

        ImGui::SliderInt("Model quality", &this->model.quality, 0, 50);
        ImGui::SliderInt("Skip step count", &this->model.skipSteps, 1, 15);

        ImGui::SliderInt("Blur quality", &this->model.blurQuality, 0, 2);
        ImGui::Checkbox("Skip interpolation frames", &this->model.skipInterpolationFrames);

        ImGui::SliderFloat("Aura power", &this->model.glowPower, 0.0f, 2.0f);
        ImGui::ColorEdit3("Body color", &this->model.bodyColor.x);
        ImGui::ColorEdit3("Aura color", &this->model.auraColor.x);
        ImGui::ColorEdit3("Wireframe color", &this->model.wireframeColor.x);
        ImGui::Checkbox("Override aura color", &this->model.overrideAuraColor);
        ImGui::Checkbox("Override body color", &this->model.overrideBodyColor);
        ImGui::Checkbox("Override wireframe color", &this->model.overrideWireframeColor);
        ImGui::Checkbox("Draw models wireframes", &this->model.drawWireframes);
        ImGui::Checkbox("Draw wireframe only", &this->model.drawWireframeOnly);
        ImGui::Checkbox("Draw blur", &this->model.drawBlur);


//        ImGui::Checkbox("Draw body", &this->model.drawBody);
    }
    ImGui::End();
}

void Gui::drawPreviewViewport()
{
    if(ImGui::Begin("Document layer renderer"))
    {

        ImGui::BeginChild("Render side");
        if (ImGui::IsWindowHovered())
        {
            ImGuiIO &io = ImGui::GetIO();
            this->state->addPreviewCameraScale(-io.MouseWheel/10.0f);
        }
        ImVec2 wsize = ImGui::GetWindowSize();
        VNuint tex = *(VNuint *)this->framebufferLayerPreview->getColorAttachment(0);
        ImGui::Image((void*)(intptr_t)tex, wsize, ImVec2(0, 1), ImVec2(1, 0));
        if (wsize.x != this->model.previewViewportSize.x ||
            wsize.y != this->model.previewViewportSize.y)
        {
            this->model.previewViewportSize = {wsize.x, wsize.y};
            this->state->onGuiPreviewViewportSizeChange(this->model.previewViewportSize);
        }
        ImGui::EndChild();
    }
    ImGui::End();
}

bool Gui::drawVec2Control(const std::string& label, glm::vec2& values, VNfloat resetValue, VNfloat columnWidth, VNfloat speed)
{
    bool changed = false;
    ImGui::PushID(label.c_str());

    ImGui::Columns(2);
    ImGui::SetColumnWidth(0, columnWidth);
    ImGui::Text("%s", label.c_str());
    ImGui::NextColumn();

    ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 0 });

    float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
    ImVec2 buttonSize = { lineHeight + 3.0f, lineHeight };

    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.9f, 0.2f, 0.2f, 1.0f });
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
    if (ImGui::Button("X", buttonSize))
    {
        changed = true;
        values.x = resetValue;
    }
    ImGui::PopStyleColor(3);

    ImGui::SameLine();
    if(ImGui::DragFloat("##X", &values.x, speed, 0.0f, 0.0f, "%.4f"))
    {
        changed = true;
    }
    ImGui::PopItemWidth();
    ImGui::SameLine();

    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.3f, 0.8f, 0.3f, 1.0f });
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
    if (ImGui::Button("Y", buttonSize))
    {
        changed = true;
        values.y = resetValue;
    }
    ImGui::PopStyleColor(3);

    ImGui::SameLine();
    if (ImGui::DragFloat("##Y", &values.y, speed, 0.0f, 0.0f, "%.4f"))
    {
        changed = true;
    }
    ImGui::PopItemWidth();
    ImGui::SameLine();

    ImGui::PopItemWidth();

    ImGui::PopStyleVar();

    ImGui::Columns(1);

    ImGui::PopID();
    return changed;
}

void Gui::drawModelNode(size_t id)
{
    auto *container = this->state->getModelContainer();
    ImGuiTreeNodeFlags svgNodeFlags = ImGuiTreeNodeFlags_SpanAvailWidth |
                                      ImGuiTreeNodeFlags_OpenOnDoubleClick |
                                      ImGuiTreeNodeFlags_OpenOnArrow;
    if (container->getType(id) == SvgModel::ModelType::Model &&
        this->model.hasIDInSelected(id))
    {
        svgNodeFlags |= ImGuiTreeNodeFlags_Selected;
    }
    Ref<SvgModel::Model> modelObject = this->state->getModelContainer()->getModel(id);
    if (modelObject == nullptr)
    {
        svgNodeFlags |= ImGuiTreeNodeFlags_Leaf;
        ImGui::PushStyleColor(ImGuiCol_Text, 0xFF0000FF);
        if(ImGui::TreeNodeEx("Missing", svgNodeFlags))
        {
            ImGui::TreePop();
        }
        ImGui::PopStyleColor();
        return;
    }
    if (modelObject->groupsIDs.empty())
    {
        svgNodeFlags |= ImGuiTreeNodeFlags_Leaf;
    }
    auto *style = &ImGui::GetStyle();
    VNfloat oldAlpha = style->Alpha;
    if (modelObject->disabled)
    {
        style->Alpha = 0.5f;
    }
    bool activated = ImGui::TreeNodeEx(modelObject->name.c_str(), svgNodeFlags);
    if (modelObject->disabled)
    {
        style->Alpha = oldAlpha;
    }
    this->drawSceneTreePopup(id);
    this->selectModelOnClickFromTree(id);
    if (activated)
    {
        ImGui::PushID(id);
        for (size_t groupID : modelObject->groupsIDs)
        {
            ImGui::PushID(groupID);
            this->drawGroupElementNode(groupID);
            ImGui::PopID();
        }
        ImGui::PopID();
        ImGui::TreePop();
    }
}

void Gui::drawGroupElementNode(size_t id)
{
    auto *container = this->state->getModelContainer();
    ImGuiTreeNodeFlags svgNodeFlags = ImGuiTreeNodeFlags_SpanAvailWidth |
                                      ImGuiTreeNodeFlags_OpenOnDoubleClick |
                                      ImGuiTreeNodeFlags_OpenOnArrow;
    if (container->getType(id) == SvgModel::ModelType::Group &&
        this->model.hasIDInSelected(id))
    {
        svgNodeFlags |= ImGuiTreeNodeFlags_Selected;
    }
    Ref<SvgModel::Group> groupObject = this->state->getModelContainer()->getGroup(id);
    if (groupObject == nullptr)
    {
        svgNodeFlags |= ImGuiTreeNodeFlags_Leaf;
        ImGui::PushStyleColor(ImGuiCol_Text, 0xFF0000FF);
        if(ImGui::TreeNodeEx("Missing", svgNodeFlags))
        {
            ImGui::TreePop();
        }
        ImGui::PopStyleColor();
        return;
    }
    if (groupObject->keyedElementsIDs.empty())
    {
        svgNodeFlags |= ImGuiTreeNodeFlags_Leaf;
    }
    auto *style = &ImGui::GetStyle();
    VNfloat oldAlpha = style->Alpha;
    if (groupObject->disabled)
    {
        style->Alpha = 0.5f;
    }
    bool activated = ImGui::TreeNodeEx(groupObject->name.c_str(), svgNodeFlags);
    if (groupObject->disabled)
    {
        style->Alpha = oldAlpha;
    }
    this->drawSceneTreePopup(id);
    this->selectModelOnClickFromTree(id);
    if (activated)
    {
        for (size_t keyedElementID : groupObject->keyedElementsIDs)
        {
            ImGui::PushID(keyedElementID);
            this->drawKeyedElementNode(keyedElementID);
            ImGui::PopID();
        }
        ImGui::TreePop();
    }
}

void Gui::drawKeyedElementNode(size_t id)
{
    auto *container = this->state->getModelContainer();
    ImGuiTreeNodeFlags svgNodeFlags = ImGuiTreeNodeFlags_SpanAvailWidth |
                                      ImGuiTreeNodeFlags_OpenOnDoubleClick |
                                      ImGuiTreeNodeFlags_OpenOnArrow;
    if (container->getType(id) == SvgModel::ModelType::KeyedElement &&
        this->model.hasIDInSelected(id))
    {
        svgNodeFlags |= ImGuiTreeNodeFlags_Selected;
    }
    Ref<SvgModel::KeyedElement> keyedElementObject = this->state->getModelContainer()->getKeyedElement(id);
    if (keyedElementObject == nullptr)
    {
        svgNodeFlags |= ImGuiTreeNodeFlags_Leaf;
        ImGui::PushStyleColor(ImGuiCol_Text, 0xFF0000FF);
        if(ImGui::TreeNodeEx("Missing", svgNodeFlags))
        {
            ImGui::TreePop();
        }
        ImGui::PopStyleColor();
        return;
    }
    if (keyedElementObject->keysIDs.empty())
    {
        svgNodeFlags |= ImGuiTreeNodeFlags_Leaf;
    }
    auto *style = &ImGui::GetStyle();
    VNfloat oldAlpha = style->Alpha;
    if (keyedElementObject->disabled)
    {
        style->Alpha = 0.5f;
    }
    bool activated = ImGui::TreeNodeEx(keyedElementObject->name.c_str(), svgNodeFlags);
    if (keyedElementObject->disabled)
    {
        style->Alpha = oldAlpha;
    }
    this->drawSceneTreePopup(id);
    this->selectModelOnClickFromTree(id);
    if (activated)
    {
        for (size_t keyID : keyedElementObject->keysIDs)
        {
            ImGui::PushID(keyID);
            this->drawKeyNode(keyID);
            ImGui::PopID();
        }
        ImGui::TreePop();
    }
}

void Gui::drawKeyNode(size_t id)
{
    auto *container = this->state->getModelContainer();
    ImGuiTreeNodeFlags svgNodeFlags = ImGuiTreeNodeFlags_SpanAvailWidth |
                                      ImGuiTreeNodeFlags_Leaf;
    if (container->getType(id) == SvgModel::ModelType::Key &&
        this->model.hasIDInSelected(id))
    {
        svgNodeFlags |= ImGuiTreeNodeFlags_Selected;
    }
    Ref<SvgModel::Key> keyObject = this->state->getModelContainer()->getKey(id);
    if (keyObject == nullptr)
    {
        ImGui::PushStyleColor(ImGuiCol_Text, 0xFF0000FF);
        if(ImGui::TreeNodeEx("Missing", svgNodeFlags))
        {
            ImGui::TreePop();
        }
        ImGui::PopStyleColor();
        return;
    }
    auto *style = &ImGui::GetStyle();
    VNfloat oldAlpha = style->Alpha;
    if (keyObject->disabled)
    {
        style->Alpha = 0.5f;
    }
    bool layerValid = container->isLayerAvailable(keyObject->documentPath, keyObject->layerName);
    if (!layerValid)
    {
        ImGui::PushStyleColor(ImGuiCol_Text, 0xFF0000FF);
    }
    if(ImGui::TreeNodeEx(keyObject->name.c_str(), svgNodeFlags))
    {
        ImGui::TreePop();
    }
    if (!layerValid)
    {
        ImGui::PopStyleColor();
    }
    if (keyObject->disabled)
    {
        style->Alpha = oldAlpha;
    }
    this->drawSceneTreePopup(id);
    this->selectModelOnClickFromTree(id);
}

void Gui::drawSceneTreePopup(size_t clickedID)
{
    if (ImGui::BeginPopupContextItem())
    {
        if(GImGui->IO.KeyShift)
        {
            this->model.selectedModels.emplace(clickedID);
        }
        else
        {
            this->model.selectedModels.clear();
            this->model.selectedModels.emplace(clickedID);
        }
        if (this->model.selectedModels.size() == 1)
        {
            auto *container = this->state->getModelContainer();
            Ref<SvgModel::Object> object = container->getObject(clickedID);
            if (object == nullptr)
            {
                return;
            }
            if (object->getType() == SvgModel::ModelType::Model)
            {
                if (ImGui::MenuItem("Add group"))
                {
                    this->state->getModelContainer()->addGroup(clickedID);
                }
            }
            else if (object->getType() == SvgModel::ModelType::Group)
            {
                if (ImGui::MenuItem("Add keyed element"))
                {
                    this->state->getModelContainer()->addKeyedElement(clickedID);
                }
            }
            else if (object->getType() == SvgModel::ModelType::KeyedElement)
            {
                if (ImGui::MenuItem("Add key"))
                {
                    this->state->getModelContainer()->addKey(clickedID);
                }
            }
            if (ImGui::MenuItem("Duplicate"))
            {
                this->state->getModelContainer()->duplicate(clickedID);
            }
            ImGui::Separator();
            if (!object->isDisabled() && ImGui::MenuItem("Disable"))
            {
                object->setDisabled(true);
            }
            if (object->isDisabled() && ImGui::MenuItem("Enable"))
            {
                object->setDisabled(false);
            }
        }
        else if (this->model.selectedModels.size() > 1)
        {
            if (ImGui::MenuItem("Disable"))
            {
                for (auto id : this->model.selectedModels)
                {
                    Ref<SvgModel::Object> object = this->state->getModelContainer()->getObject(id);
                    object->setDisabled(true);
                }
            }
            if (ImGui::MenuItem("Enable"))
            {
                for (auto id : this->model.selectedModels)
                {
                    Ref<SvgModel::Object> object = this->state->getModelContainer()->getObject(id);
                    object->setDisabled(false);
                }
            }
        }
        ImGui::Separator();
        if (ImGui::MenuItem("Delete"))
        {
            this->model.openModelDeletePopup = true;
        }
        ImGui::EndPopup();
    }
}

void Gui::drawCurrentKeyedElementProperties()
{
    SvgModelContainer *container = this->state->getModelContainer();
    if (this->model.selectedModels.size() != 1)
    {
        return;
    }
    size_t id = *this->model.selectedModels.begin();
    Ref<SvgModel::KeyedElement> keyedElementObject = container->getKeyedElement(id);
    if (keyedElementObject == nullptr)
    {
        ImGui::PushStyleColor(ImGuiCol_Text, 0xFF0000FF);
        ImGui::Text("Keyed element is missing!");
        ImGui::PopStyleColor();
        return;
    }
    if(ImGui::CollapsingHeader("Name", ImGuiTreeNodeFlags_DefaultOpen))
    {
        ImGui::InputText("###GroupName", this->model.itemName, 255);
        ImGui::Button("Submit###GroupName");
    }

    if(ImGui::CollapsingHeader("Transformation", ImGuiTreeNodeFlags_DefaultOpen))
    {
        auto *style = &ImGui::GetStyle();
        VNfloat oldSpacing = style->ItemSpacing.y;

        style->ItemSpacing.y = 10.0f;
        Gui::drawVec2Control("Position", keyedElementObject->position, 0.0f, 100.0f, 0.008f);
        style->ItemSpacing.y = oldSpacing;
        Gui::drawVec2Control("Scale", keyedElementObject->scale, 1.0f, 100.0f, 0.008f);

        ImGui::Text("Rotation:");
        ImGui::DragFloat("###GroupRotation", &keyedElementObject->rotation, 0.5f);
        ImGui::Spacing();
        if(ImGui::Button("Center object to children"))
        {
            this->state->getModelContainer()->centerObjectToChildren(id);
        }
        if(ImGui::Button("Center children to object"))
        {

        }
        ImGui::Separator();
    }

    if(ImGui::CollapsingHeader("Draw", ImGuiTreeNodeFlags_DefaultOpen))
    {
        ImGui::Checkbox("Disabled ", &keyedElementObject->disabled);
        ImGui::Separator();
    }

    if(ImGui::CollapsingHeader("Interpolation", ImGuiTreeNodeFlags_DefaultOpen))
    {
        ImGui::Text("Key position:");
        ImGui::SliderFloat("###Key position", &keyedElementObject->targetKeyPosition, 0.0f, 1.0f);
        ImGui::Checkbox("Animate key", &keyedElementObject->sinusInterpolationUpdate);
        ImGui::Separator();
        if (!keyedElementObject->keysPositions.empty())
        {
            for (VNuint i = 0; i < keyedElementObject->keysPositions.size(); i++)
            {
                VNfloat &keyPosition = keyedElementObject->keysPositions[i];
                size_t keyID = keyedElementObject->keysIDs[i];
                Ref<SvgModel::Key> key = container->getKey(keyID);
                if (key == nullptr)
                {
                    ImGui::PushStyleColor(ImGuiCol_Text, 0xFF0000FF);
                    ImGui::Text("Key %d is missing!", i + 1);
                    ImGui::PopStyleColor();
                    continue;
                }
                else
                {
                    ImGui::PushID(i);
                    auto *style = &ImGui::GetStyle();
                    VNfloat oldAlpha = style->Alpha;
                    bool layerAvail = container->isLayerAvailable(key->documentPath, key->layerName);
                    if(!layerAvail)
                    {
                        ImGui::PushStyleColor(ImGuiCol_Text, 0xFF0000FF);
                    }
                    if (key->disabled)
                    {
                        style->Alpha = 0.5f;
                    }
                    ImGui::Text("%s", key->name.c_str());

                    ImGui::SliderFloat("###Interpolation", &keyPosition, 0.0f, 1.0f);
                    if(!layerAvail)
                    {
                        ImGui::PopStyleColor();
                    }
                    if (key->disabled)
                    {
                        style->Alpha = oldAlpha;
                    }
                    ImGui::PopID();
                }
            }
        }
        else
        {
            ImGui::TextWrapped("Not enough keys to be able to change interpolations.");
        }
        ImGui::Separator();
    }
}

void Gui::drawCurrentKeyProperties()
{
    SvgModelContainer *container = this->state->getModelContainer();
    if (this->model.selectedModels.size() != 1)
    {
        return;
    }
    size_t id = *this->model.selectedModels.begin();
    Ref<SvgModel::Key> key = container->getKey(id);
    if (key == nullptr)
    {
        ImGui::PushStyleColor(ImGuiCol_Text, 0xFF0000FF);
        ImGui::Text("Key is missing!");
        ImGui::PopStyleColor();
        return;
    }
    if(ImGui::CollapsingHeader("Name", ImGuiTreeNodeFlags_DefaultOpen))
    {
        ImGui::InputText("###KeyName", this->model.itemName, 255);
        ImGui::Button("Submit###KeyName");
    }

    if(ImGui::CollapsingHeader("Transformation", ImGuiTreeNodeFlags_DefaultOpen))
    {
        auto *style = &ImGui::GetStyle();
        VNfloat oldSpacing = style->ItemSpacing.y;

        style->ItemSpacing.y = 10.0f;
        Gui::drawVec2Control("Position", key->position, 0.0f, 100.0f, 0.008f);
        style->ItemSpacing.y = oldSpacing;
        Gui::drawVec2Control("Scale", key->scale, 1.0f, 100.0f, 0.008f);

        ImGui::Text("Rotation:");
        ImGui::DragFloat("###KeyRotation", &key->rotation, 0.5f);
        ImGui::Separator();
    }

    if(ImGui::CollapsingHeader("Draw", ImGuiTreeNodeFlags_DefaultOpen))
    {
        ImGui::Checkbox("Disabled ", &key->disabled);
        ImGui::Separator();
    }
}

void Gui::drawCurrentGroupProperties()
{
    SvgModelContainer *container = this->state->getModelContainer();
    if (this->model.selectedModels.size() != 1)
    {
        return;
    }
    size_t id = *this->model.selectedModels.begin();
    Ref<SvgModel::Group> groupObject = container->getGroup(id);
    if (groupObject == nullptr)
    {
        ImGui::PushStyleColor(ImGuiCol_Text, 0xFF0000FF);
        ImGui::Text("Group is missing!");
        ImGui::PopStyleColor();
        return;
    }
    if(ImGui::CollapsingHeader("Name", ImGuiTreeNodeFlags_DefaultOpen))
    {
        ImGui::InputText("###GroupName", this->model.itemName, 255);
        ImGui::Button("Submit###GroupName");
    }

    if(ImGui::CollapsingHeader("Transformation", ImGuiTreeNodeFlags_DefaultOpen))
    {
        auto *style = &ImGui::GetStyle();
        VNfloat oldSpacing = style->ItemSpacing.y;

        style->ItemSpacing.y = 10.0f;
        Gui::drawVec2Control("Position", groupObject->position, 0.0f, 100.0f, 0.008f);
        style->ItemSpacing.y = oldSpacing;
        Gui::drawVec2Control("Scale", groupObject->scale, 1.0f, 100.0f, 0.008f);

        ImGui::Text("Rotation:");
        ImGui::DragFloat("###GroupRotation", &groupObject->rotation, 0.5f);
        ImGui::Separator();
    }
    if(ImGui::CollapsingHeader("Color", ImGuiTreeNodeFlags_DefaultOpen))
    {
        ImGui::ColorEdit3("Aura color", &groupObject->auraColor.x);
        ImGui::ColorEdit3("Wireframe color", &groupObject->wireframeColor.x);
        ImGui::ColorEdit3("Body color", &groupObject->bodyColor.x);
        ImGui::Separator();
    }

    if(ImGui::CollapsingHeader("Draw", ImGuiTreeNodeFlags_DefaultOpen))
    {

        ImGui::SliderInt("Draw layer", &groupObject->drawLayer, 0, container->getTotalLayers() - 1);
        if(ImGui::Button("Move up"))
        {
            if (groupObject->drawLayer < container->getTotalLayers())
            {
                groupObject->drawLayer += 1;
            }
        }
        ImGui::SameLine();
        if(ImGui::Button("Move down"))
        {
            if (groupObject->drawLayer > 0)
            {
                groupObject->drawLayer -= 1;
            }
        }
        ImGui::Checkbox("Draw as wireframe", &groupObject->drawAsWireframe);
        ImGui::Checkbox("Disabled ", &groupObject->disabled);
        ImGui::Checkbox("Is color patch", &groupObject->isPatch);
        ImGui::Checkbox("Patch affects aura color", &groupObject->affectAura);
        ImGui::Checkbox("Patch affects body color", &groupObject->affectBodyColor);
        ImGui::Separator();
    }

    if(ImGui::CollapsingHeader("Interpolation", ImGuiTreeNodeFlags_DefaultOpen))
    {
        if (groupObject->keyedElementsIDs.size() > 1)
        {
            for (VNuint i = 1; i < groupObject->keyedElementsIDs.size(); i++)
            {
                size_t id = groupObject->keyedElementsIDs[i];
                Ref<SvgModel::KeyedElement> keyedElement = container->getKeyedElement(id);
                if (keyedElement == nullptr)
                {
                    ImGui::PushStyleColor(ImGuiCol_Text, 0xFF0000FF);
                    ImGui::Text("Keyed element %d is missing!", i);
                    ImGui::PopStyleColor();
                }
                else
                {
                    VNfloat &targetKeyedElementInterpolation = groupObject->targetKeyedElementsInterpolations[i - 1];
                    ImGui::PushID(i);
                    auto *style = &ImGui::GetStyle();
                    VNfloat oldAlpha = style->Alpha;
                    if (keyedElement->disabled)
                    {
                        style->Alpha = 0.5f;
                    }
                    ImGui::Text("%s", keyedElement->name.c_str());
                    ImGui::SliderFloat("###Interpolation", &targetKeyedElementInterpolation, 0.0f, 1.0f);
                    if (keyedElement->disabled)
                    {
                        style->Alpha = oldAlpha;
                    }
                    ImGui::PopID();
                }
            }
        }
        else
        {
            ImGui::TextWrapped("Not enough keyed elements to be able to change interpolations.");
        }
        ImGui::Separator();
    }
}

void Gui::drawCurrentModelProperties()
{
    SvgModelContainer *container = this->state->getModelContainer();
    if (this->model.selectedModels.size() != 1)
    {
        return;
    }
    size_t id = *this->model.selectedModels.begin();
    Ref<SvgModel::Model> modelObject = container->getModel(id);
    if (modelObject == nullptr)
    {
        ImGui::PushStyleColor(ImGuiCol_Text, 0xFF0000FF);
        ImGui::Text("Model is missing!");
        ImGui::PopStyleColor();
        return;
    }
    if(ImGui::CollapsingHeader("Name", ImGuiTreeNodeFlags_DefaultOpen))
    {
        ImGui::InputText("###ModelName", this->model.itemName, 255);
        ImGui::Button("Submit###ModelName");
    }

    if(ImGui::CollapsingHeader("Transformation", ImGuiTreeNodeFlags_DefaultOpen))
    {
        auto *style = &ImGui::GetStyle();
        VNfloat oldSpacing = style->ItemSpacing.y;

        style->ItemSpacing.y = 10.0f;
        Gui::drawVec2Control("Position", modelObject->position, 0.0f, 100.0f, 0.008f);
        style->ItemSpacing.y = oldSpacing;
        Gui::drawVec2Control("Scale", modelObject->scale, 1.0f, 100.0f, 0.008f);

        ImGui::Text("Rotation:");
        ImGui::DragFloat("###GroupRotation", &modelObject->rotation, 0.5f);
        ImGui::Separator();
    }

    if(ImGui::CollapsingHeader("Draw", ImGuiTreeNodeFlags_DefaultOpen))
    {
        ImGui::Checkbox("Draw as wireframe", &modelObject->drawAsWireframe);
        ImGui::Checkbox("Disabled ", &modelObject->disabled);
        ImGui::Separator();
    }
    ImGui::Separator();
}


void Gui::modelDeletePopup()
{
    if (this->model.openModelDeletePopup && !this->model.dontAskAboutModelDelete)
    {
        ImGui::OpenPopup("Are you sure?###DeleteModelPopup");
    }
    if (ImGui::BeginPopupModal("Are you sure?###DeleteModelPopup", &this->model.openModelDeletePopup, ImGuiWindowFlags_AlwaysAutoResize))
    {
        ImGui::Text("Are you sure you want to delete these models?\n\n");
        ImGui::Separator();

        ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0, 0));
        ImGui::Checkbox("Don't ask me next time", &this->model.dontAskAboutModelDelete);
        ImGui::PopStyleVar();

        if (ImGui::Button("OK", ImVec2(120, 0)))
        {
            this->model.openModelDeletePopup = false;
            for (size_t selectedID : this->model.selectedModels)
            {
                this->state->getModelContainer()->removeFromScene(selectedID);
            }
            this->model.selectedModels.clear();
            ImGui::CloseCurrentPopup();
        }
        ImGui::SetItemDefaultFocus();
        ImGui::SameLine();
        if (ImGui::Button("Cancel", ImVec2(120, 0)))
        {
            this->model.openModelDeletePopup = false;
            ImGui::CloseCurrentPopup();
        }
        ImGui::EndPopup();
    }
}

void Gui::selectModelOnClickFromTree(size_t id)
{
    if (ImGui::IsItemClicked())
    {
        Ref<SvgModel::Object> object = this->state->getModelContainer()->getObject(id);
        this->model.currentlySelectedItemType = SelectedTreeItem::None;
        if (object == nullptr)
        {
            return;
        }
        if(GImGui->IO.KeyShift)
        {
            auto found = this->model.selectedModels.find(id);
            if (found == this->model.selectedModels.end())
            {
                this->model.selectedModels.emplace(id);
            }
            else
            {
                this->model.selectedModels.erase(found);
            }
        }
        else
        {
            this->model.selectedModels.clear();
            this->model.selectedModels.emplace(id);
        }
        if (this->model.selectedModels.size() == 1)
        {
            VNsize nameLen = object->getName().size();
            if (nameLen > 255)
            {
                std::memcpy(this->model.itemName, object->getName().c_str(), 254);
                this->model.itemName[255] = '\0';
            }
            else
            {
                std::memcpy(this->model.itemName, object->getName().c_str(), nameLen);
                this->model.itemName[nameLen] = '\0';
            }
        }
    }
}

//void Gui::drawModelElementNode(SvgModelContainer::Model &svgModel, SvgModelContainer::Element &svgElement,
//                               VNuint modelIndex, VNuint elementIndex)
//{
//    ImGuiTreeNodeFlags svgElementNodeFlags = ImGuiTreeNodeFlags_SpanAvailWidth;
//    if (this->model.currentlySelectedItemType == SelectedTreeItem::Element &&
//        this->model.modelSelectedIndex == modelIndex &&
//        this->model.elementSelectedIndex == elementIndex)
//    {
//        svgElementNodeFlags |= ImGuiTreeNodeFlags_Selected;
//    }
//    if (svgElement.intermediateElements.empty())
//    {
//        svgElementNodeFlags |= ImGuiTreeNodeFlags_Leaf;
//    }
//    else
//    {
//        svgElementNodeFlags |= ImGuiTreeNodeFlags_OpenOnDoubleClick;
//    }
//    ImGui::PushID(elementIndex);
//    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 0.0f, 1.0f));
//    bool activated = ImGui::TreeNodeEx(svgElement.name.c_str(), svgElementNodeFlags);
//    ImGui::PopStyleColor();
//    if (activated)
//    {
//        if (ImGui::IsItemClicked())
//        {
//            this->model.currentlySelectedItemType = SelectedTreeItem::Element;
//            this->model.modelSelectedIndex = modelIndex;
//            this->model.elementSelectedIndex = elementIndex;
//        }
//        VNuint totalIntermediateElements = svgModel.elements[elementIndex].intermediateElements.size();
//        for (VNint intermediateElementIndex = 0;
//             intermediateElementIndex < totalIntermediateElements; intermediateElementIndex++)
//        {
//            SvgModelContainer::ModelElement &svgIntermediateElement = svgElement.intermediateElements[intermediateElementIndex];
//            Gui::drawIntermediateElementNode(svgModel, svgElement, svgIntermediateElement,
//                                             modelIndex, elementIndex, intermediateElementIndex);
//        }
//        ImGui::TreePop();
//    }
//    ImGui::PopID();
//}

//void Gui::drawIntermediateElementNode(SvgModelContainer::Model &svgModel, SvgModelContainer::Element &svgElement, SvgModelContainer::Element &svgIntermediateElement,
//                                      VNuint modelIndex, VNuint elementIndex, VNuint intermediateElementIndex)
//{
//    ImGuiTreeNodeFlags svgIntermediateElementNodeFlags =
//            ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_Leaf;
//    if (this->model.currentlySelectedItemType == SelectedTreeItem::ElementIntermediate &&
//        this->model.modelSelectedIndex == modelIndex &&
//        this->model.elementSelectedIndex == elementIndex &&
//        this->model.intermediateElementSelectedIndex == intermediateElementIndex)
//    {
//        svgIntermediateElementNodeFlags |= ImGuiTreeNodeFlags_Selected;
//    }
//    auto &intermediateElement = svgModel.elements[elementIndex].intermediateElements[intermediateElementIndex];
//    ImGui::PushID(intermediateElementIndex);
//    if (ImGui::TreeNodeEx(svgIntermediateElement.name.c_str(),
//                          svgIntermediateElementNodeFlags))
//    {
//        if (ImGui::IsItemClicked())
//        {
//            this->model.currentlySelectedItemType = SelectedTreeItem::ElementIntermediate;
//            this->model.modelSelectedIndex = modelIndex;
//            this->model.elementSelectedIndex = elementIndex;
//            this->model.intermediateElementSelectedIndex = intermediateElementIndex;
//        }
//        ImGui::TreePop();
//    }
//    ImGui::PopID();
//}

Gui::Gui(Ref<Framebuffer> renderFramebuffer, Ref<Framebuffer> framebufferLayerPreview, UserEndApplication *application, CustomState *state):
    renderFramebuffer(std::move(renderFramebuffer)),
    framebufferLayerPreview(std::move(framebufferLayerPreview)),
    application(application),
    state(state)
{
    const char* glsl_version = "#version 330 core";
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.IniFilename = nullptr;
    io.WantCaptureKeyboard = true;
    io.WantTextInput = true;

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer backends
    ImGui_ImplSDL2_InitForOpenGL((SDL_Window *)this->application->getWindow()->getRaw(), ((DefaultWindow *)this->application->getWindow())->getContext());
    ImGui_ImplOpenGL3_Init(glsl_version);

    ThemeSelector::reapply();
}

Gui::~Gui()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
}

void Gui::render()
{
//    this->mouseDelta = {ImGui::GetMousePos().x - this->prevMousePos.x,
//                        ImGui::GetMousePos().y - this->prevMousePos.y};
//    this->prevMousePos = ImGui::GetMousePos();
    this->model.update();
//    this->previewShouldBeUpdated = false;
    Window *window = this->application->getWindow();
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame((SDL_Window *)window->getRaw());
    ImGui::NewFrame();


//        ImGui::ShowDemoWindow();

//            const char* items[] = { "AAAA", "BBBB", "CCCC", "DDDD", "EEEE", "FFFF", "GGGG", "HHHH", "IIIIIII", "JJJJ", "KKKKKKK" };
//            static int item_current = 0;
//            ImGui::Combo("combo", &item_current, items, IM_ARRAYSIZE(items));

    this->drawMainWindow();
    if (this->settingsWindowOpened)
    {
        this->drawSettingsWindow();
    }
    if (this->model.currentlySelectedItemType == SelectedTreeItem::DocumentLayer)
    {
        this->drawPreviewViewport();
    }
    this->drawPropertiesWindow();
    this->drawRenderViewPort();
    this->drawAccessoriesWindow();
    this->drawSceneTreeWindow();
    this->drawOpenedSvgFilesTree();
//    this->popups();
    this->modelDeletePopup();

//    this->popups();
    ImGui::Render();
    glViewport(0, 0, window->getWidth(), window->getHeight());
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    this->mouseDelta = {0.0f, 0.0f};
}

Gui::Model *Gui::getModel() noexcept
{
    return &this->model;
}

void Gui::processEvent(Event *event)
{
    if (event->getRaw() == nullptr)
    {
        return;
    }
    ImGui_ImplSDL2_ProcessEvent((SDL_Event *)event->getRaw());
}



//bool Gui::shouldBePreviewUpdated()
//{
//    return this->previewShouldBeUpdated;
//}
//
//bool Gui::wasPreviewWindowSizeChanged()
//{
//    return this->previewWindowSizeChanged;
//}
