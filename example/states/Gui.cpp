#include "Gui.h"
#include "imgui_sdl.h"
#include "imgui_opengl3.h"
#include <imgui.h>
#include <imgui_internal.h>
#include "../../vanadium/src/platform/default/DefaultWindow.h"
#include "../../vanadium/src/platform/opengl/OpenGLFramebuffer.h"
#include "CustomState.h"

void Gui::drawRenderViewPort()
{
    if(ImGui::Begin("Render viewport"))
    {


        ImGui::BeginChild("Render side");
        if(ImGui::IsWindowHovered() && ImGui::IsMouseDragging(ImGuiMouseButton_Left))
        {
            ImGui::SetMouseCursor(ImGuiMouseCursor_ResizeAll);
//            ImGui::GetMouseDragDelta(ImGuiMouseButton_Left);
            printf("Ohnoes\n");
        }

        ImVec2 wsize = ImGui::GetWindowSize();
        this->model.renderViewportSize = {wsize.x, wsize.y};
        VNuint tex = ((OpenGLFramebuffer*)this->renderFramebuffer.get())->getColorAttachment(0);
        ImGui::Image((void*)(intptr_t)tex, wsize, ImVec2(0, 1), ImVec2(1, 0));
        ImGui::EndChild();
    }
    ImGui::End();
}

void Gui::drawSceneTreeWindow()
{
    if(ImGui::Begin("Scene tree"))
    {
        SvgModelContainer *container = this->state->getModelContainer();
        auto svgModels = container->getModels();
        VNuint modelIndex = 0;
        for (auto &svgModel : svgModels)
        {
            this->drawModelNode(svgModel.second, modelIndex);
            modelIndex++;
        }
    }
    ImGui::End();
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
            ImGuiID dock_right_id = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Right, 0.4f, nullptr,
                                                                &dock_main_id);
            ImGuiID dock_left_id = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Left, 0.6f, nullptr,
                                                               &dock_main_id);
            ImGuiID dock_right_up_id = ImGui::DockBuilderSplitNode(dock_right_id, ImGuiDir_Up, 0.3f, nullptr,
                                                                   &dock_right_id);
            ImGuiID dock_right_down_id = ImGui::DockBuilderSplitNode(dock_right_id, ImGuiDir_Down, 0.4f, nullptr,
                                                                   &dock_right_id);
            ImGuiID dock_left_down_id = ImGui::DockBuilderSplitNode(dock_left_id, ImGuiDir_Down, 0.3f, nullptr,
                                                                     &dock_left_id);

            ImGui::DockBuilderDockWindow("Render viewport", dock_left_id);
            ImGui::DockBuilderDockWindow("Properties", dock_right_id);
            ImGui::DockBuilderDockWindow("Scene tree", dock_right_up_id);
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
    ImGuiWindowFlags flags = ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoCollapse;

    bool activated = ImGui::Begin("Settings window", &this->settingsWindowOpened, flags);
    if (activated)
    {
        ImGui::SliderFloat("Interpolation speed", &this->model.interpolationSpeed, 0.01f, 1.0f);

        ImGui::SliderInt("Model quality", &this->model.quality, 0, 50);
        ImGui::SliderInt("Skip step count", &this->model.skipSteps, 1, 15);

        ImGui::Checkbox("Is fast blur", &this->model.isFastBlur);
        ImGui::Checkbox("Skip interpolation frames", &this->model.skipInterpolationFrames);

        ImGui::SliderFloat("Glow power", &this->model.glowPower, 0.0f, 2.0f);

        ImGui::ColorEdit3("Fill color", &this->model.fillColor.x);
        ImGui::ColorEdit3("Aura color", &this->model.auraColor.x);
        ImGui::Checkbox("Draw model borders", &this->model.drawBorders);
        ImGui::Checkbox("Draw blur", &this->model.drawBlur);
        ImGui::Checkbox("Draw body", &this->model.drawBody);
    }
    ImGui::End();
}

void Gui::drawPreviewViewport()
{
    if(ImGui::Begin("Document layer renderer"))
    {
        ImGui::BeginChild("Render side");

        ImVec2 wsize = ImGui::GetWindowSize();
        if (wsize.x != this->model.previewViewportSize.x ||
            wsize.y != this->model.previewViewportSize.y)
        {
            this->previewShouldBeUpdated = true;
            this->previewWindowSizeChanged = true;
        }
        this->model.previewViewportSize = {wsize.x, wsize.y};
        VNuint tex = ((OpenGLFramebuffer*)this->framebufferLayerPreview.get())->getColorAttachment(0);
        ImGui::Image((void*)(intptr_t)tex, wsize, ImVec2(0, 1), ImVec2(1, 0));
        ImGui::EndChild();
    }
    ImGui::End();
}

void Gui::drawVec2Control(const std::string& label, glm::vec2& values, VNfloat resetValue, VNfloat columnWidth, VNfloat speed)
{
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
        values.x = resetValue;
    ImGui::PopStyleColor(3);

    ImGui::SameLine();
    ImGui::DragFloat("##X", &values.x, speed, 0.0f, 0.0f, "%.4f");
    ImGui::PopItemWidth();
    ImGui::SameLine();

    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.3f, 0.8f, 0.3f, 1.0f });
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
    if (ImGui::Button("Y", buttonSize))
        values.y = resetValue;
    ImGui::PopStyleColor(3);

    ImGui::SameLine();
    ImGui::DragFloat("##Y", &values.y, speed, 0.0f, 0.0f, "%.4f");
    ImGui::PopItemWidth();
    ImGui::SameLine();

    ImGui::PopItemWidth();

    ImGui::PopStyleVar();

    ImGui::Columns(1);

    ImGui::PopID();
}

void Gui::drawModelNode(SvgModelContainer::Model &svgModel, VNuint modelIndex)
{
    ImGuiTreeNodeFlags svgNodeFlags = ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_OpenOnArrow;
    if (this->model.currentlySelectedItemType == SelectedTreeItem::Model &&
        this->model.modelSelectedIndex == modelIndex)
    {
        svgNodeFlags |= ImGuiTreeNodeFlags_Selected;
    }
    if (svgModel.groups.empty())
    {
        svgNodeFlags |= ImGuiTreeNodeFlags_Leaf;
    }
    bool activated = ImGui::TreeNodeEx(svgModel.name.c_str(), svgNodeFlags);
    if (ImGui::IsItemClicked())
    {
        this->model.currentlySelectedItemType = SelectedTreeItem::Model;
        this->model.modelSelectedIndex = modelIndex;
        this->previewShouldBeUpdated = true;
    }
    if (activated)
    {
        ImGui::PushID(modelIndex);
        for (VNuint groupIndex = 0; groupIndex < svgModel.groups.size(); groupIndex++)
        {
            ImGui::PushID(groupIndex);
            auto &svgGroup = svgModel.groups[groupIndex];
            this->drawGroupElementNode(svgGroup, modelIndex, groupIndex);
            ImGui::PopID();
        }
        ImGui::PopID();
        ImGui::TreePop();
    }
}

void Gui::drawGroupElementNode(SvgModelContainer::Group &svgGroup, VNuint modelIndex, VNuint groupIndex)
{
    ImGuiTreeNodeFlags svgNodeFlags = ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_OpenOnArrow;
    if (this->model.currentlySelectedItemType == SelectedTreeItem::Group &&
        this->model.modelSelectedIndex == modelIndex &&
        this->model.groupSelectedIndex == groupIndex)
    {
        svgNodeFlags |= ImGuiTreeNodeFlags_Selected;
    }
    if (svgGroup.keyedElements.empty())
    {
        svgNodeFlags |= ImGuiTreeNodeFlags_Leaf;
    }
    bool activated = ImGui::TreeNodeEx(svgGroup.name.c_str(), svgNodeFlags);
    if (ImGui::IsItemClicked())
    {
        this->model.currentlySelectedItemType = SelectedTreeItem::Group;
        this->model.modelSelectedIndex = modelIndex;
        this->model.groupSelectedIndex = groupIndex;
        this->previewShouldBeUpdated = true;
    }
    if (activated)
    {
        for (VNuint keyedElementIndex = 0; keyedElementIndex < svgGroup.keyedElements.size(); keyedElementIndex++)
        {
            ImGui::PushID(keyedElementIndex);
            auto &svgKeyedElement = svgGroup.keyedElements[keyedElementIndex];
            this->drawKeyedElementNode(svgKeyedElement, modelIndex, groupIndex, keyedElementIndex);
            ImGui::PopID();
        }
        ImGui::TreePop();
    }
}

void Gui::drawKeyedElementNode(SvgModelContainer::KeyedElement &svgKeyedElement, VNuint modelIndex, VNuint groupIndex, VNuint keyedElementIndex)
{
    ImGuiTreeNodeFlags svgNodeFlags = ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_OpenOnArrow;
    if (this->model.currentlySelectedItemType == SelectedTreeItem::KeyedElement &&
        this->model.modelSelectedIndex == modelIndex &&
        this->model.groupSelectedIndex == groupIndex &&
        this->model.keyedElementSelectedIndex == keyedElementIndex)
    {
        svgNodeFlags |= ImGuiTreeNodeFlags_Selected;
    }
    if (svgKeyedElement.keys.empty())
    {
        svgNodeFlags |= ImGuiTreeNodeFlags_Leaf;
    }
    bool activated = ImGui::TreeNodeEx(svgKeyedElement.name.c_str(), svgNodeFlags);
    if (ImGui::IsItemClicked())
    {
        this->model.currentlySelectedItemType = SelectedTreeItem::KeyedElement;
        this->model.modelSelectedIndex = modelIndex;
        this->model.groupSelectedIndex = groupIndex;
        this->model.keyedElementSelectedIndex = keyedElementIndex;
        this->previewShouldBeUpdated = true;
    }
    if (activated)
    {
        for (VNuint keyIndex = 0; keyIndex < svgKeyedElement.keys.size(); keyIndex++)
        {
            ImGui::PushID(keyIndex);
            auto &svgKey = svgKeyedElement.keys[keyIndex];
            this->drawKeyNode(svgKey, modelIndex, groupIndex, keyedElementIndex, keyIndex);
            ImGui::PopID();
        }
        ImGui::TreePop();
    }
}

void Gui::drawKeyNode(SvgModelContainer::Element &svgKey, VNuint modelIndex, VNuint groupIndex, VNuint keyedElementIndex, VNuint keyIndex)
{
    ImGuiTreeNodeFlags svgNodeFlags = ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_Leaf;
    if (this->model.currentlySelectedItemType == SelectedTreeItem::Element &&
        this->model.modelSelectedIndex == modelIndex &&
        this->model.groupSelectedIndex == groupIndex &&
        this->model.keyedElementSelectedIndex == keyedElementIndex &&
        this->model.elementSelectedIndex == keyIndex)
    {
        svgNodeFlags |= ImGuiTreeNodeFlags_Selected;
    }
    bool activated = ImGui::TreeNodeEx(svgKey.name.c_str(), svgNodeFlags);
    if (ImGui::IsItemClicked())
    {
        this->model.currentlySelectedItemType = SelectedTreeItem::Element;
        this->model.modelSelectedIndex = modelIndex;
        this->model.groupSelectedIndex = groupIndex;
        this->model.keyedElementSelectedIndex = keyedElementIndex;
        this->model.elementSelectedIndex = keyIndex;
        this->previewShouldBeUpdated = true;
    }
    if (activated)
    {
        ImGui::TreePop();
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

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer backends
    ImGui_ImplSDL2_InitForOpenGL((SDL_Window *)this->application->getWindow()->getRaw(), ((DefaultWindow *)this->application->getWindow())->getContext());
    ImGui_ImplOpenGL3_Init(glsl_version);
}

Gui::~Gui()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
}

void Gui::render()
{
    this->model.update();
    this->previewShouldBeUpdated = false;
    this->previewWindowSizeChanged = false;
    Window *window = this->application->getWindow();
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame((SDL_Window *)window->getRaw());
    ImGui::NewFrame();
//            const char* items[] = { "AAAA", "BBBB", "CCCC", "DDDD", "EEEE", "FFFF", "GGGG", "HHHH", "IIIIIII", "JJJJ", "KKKKKKK" };
//            static int item_current = 0;
//            ImGui::Combo("combo", &item_current, items, IM_ARRAYSIZE(items));

    this->drawMainWindow();
    if (this->settingsWindowOpened)
    {
        this->drawSettingsWindow();
    }
    if (this->model.currentlySelectedItemType != SelectedTreeItem::None)
    {
        this->drawPreviewViewport();
    }
    this->drawPropertiesWindow();
    this->drawRenderViewPort();
    this->drawSceneTreeWindow();
    this->drawOpenedSvgFilesTree();

    ImGui::Render();
    glViewport(0, 0, window->getWidth(), window->getHeight());
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
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

bool Gui::shouldBePreviewUpdated()
{
    return this->previewShouldBeUpdated;
}

bool Gui::wasPreviewWindowSizeChanged()
{
    return this->previewWindowSizeChanged;
}
