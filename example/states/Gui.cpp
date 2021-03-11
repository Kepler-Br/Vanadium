#include "Gui.h"
#include "imgui_sdl.h"
#include "imgui_opengl3.h"
#include <imgui.h>
#include <imgui_internal.h>
#include "../../vanadium/src/platform/default/DefaultWindow.h"
#include "../../vanadium/src/platform/opengl/OpenGLFramebuffer.h"
#include "CustomState.h"

Gui::Gui(Ref<Framebuffer> renderFramebuffer, UserEndApplication *application, CustomState *state):
    renderFramebuffer(std::move(renderFramebuffer)),
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
    io.IniFilename = NULL;

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
    Window *window = this->application->getWindow();
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame((SDL_Window *)window->getRaw());
    ImGui::NewFrame();
//            const char* items[] = { "AAAA", "BBBB", "CCCC", "DDDD", "EEEE", "FFFF", "GGGG", "HHHH", "IIIIIII", "JJJJ", "KKKKKKK" };
//            static int item_current = 0;
//            ImGui::Combo("combo", &item_current, items, IM_ARRAYSIZE(items));





    ImGuiWindowFlags windowFlags =
            ImGuiWindowFlags_MenuBar |
            ImGuiWindowFlags_NoDocking |
            ImGuiWindowFlags_NoTitleBar |
            ImGuiWindowFlags_NoCollapse |
            ImGuiWindowFlags_NoResize |
            ImGuiWindowFlags_NoMove |
            ImGuiWindowFlags_NoBringToFrontOnFocus;

    static bool p_open = true;
    ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->Pos);
    ImGui::SetNextWindowSize(viewport->Size);
    ImGui::SetNextWindowViewport(viewport->ID);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGui::Begin("SVG shapeshifter", &p_open, windowFlags);

    ImGui::PopStyleVar(3);

    if (ImGui::BeginMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if(ImGui::MenuItem("New", NULL, false))
                printf("Oh my!\n");
            if(ImGui::MenuItem("Open...", NULL, false))
                printf("Oh my!\n");
            if(ImGui::MenuItem("Reload from disk", NULL, false))
                printf("Oh my!\n");
            ImGui::Separator();

            if (ImGui::MenuItem("Settings", "", false))
                this->settingsWindowOpened = true;

            ImGui::Separator();

            if (ImGui::MenuItem("Exit", NULL, false))
                ;
            ImGui::EndMenu();
        }

        ImGui::EndMenuBar();
    }


    ImGuiDockNodeFlags dockspaceFlags = ImGuiDockNodeFlags_None;
    ImGuiID dockspaceID = ImGui::GetID("ID().c_str()");
    if (!ImGui::DockBuilderGetNode(dockspaceID)) {
        ImGui::DockBuilderRemoveNode(dockspaceID);
        ImGui::DockBuilderAddNode(dockspaceID, ImGuiDockNodeFlags_None);

        ImGuiID dock_main_id = dockspaceID;
        ImGuiID dock_right_id = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Right, 0.4f, nullptr, &dock_main_id);
        ImGuiID dock_left_id = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Left, 0.6f, nullptr, &dock_main_id);
        ImGuiID dock_right_up_id = ImGui::DockBuilderSplitNode(dock_right_id, ImGuiDir_Up, 0.2f, nullptr, &dock_right_id);

        ImGui::DockBuilderDockWindow("Render viewport", dock_left_id);
        ImGui::DockBuilderDockWindow("Element settings", dock_right_id);
        ImGui::DockBuilderDockWindow("Opened SVG files", dock_right_up_id);
        ImGui::DockBuilderDockWindow("Scene tree", dock_right_up_id);


        ImGuiDockNode* node = ImGui::DockBuilderGetNode(dock_right_id);
        node->LocalFlags |= (ImGuiDockNodeFlags_NoTabBar);
        node = ImGui::DockBuilderGetNode(dock_left_id);
        node->LocalFlags |= (ImGuiDockNodeFlags_NoTabBar);
        node = ImGui::DockBuilderGetNode(dock_right_up_id);
        node->LocalFlags |= ImGuiDockNodeFlags_NoWindowMenuButton;

        ImGui::DockBuilderFinish(dock_main_id);
    }
    ImGui::DockSpace(dockspaceID, ImVec2(0.0f, 0.0f), dockspaceFlags);





    ImGui::End();

    if(this->settingsWindowOpened)
    {
        ImGuiWindowFlags flags = ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoCollapse;

        ImGui::Begin("Settings window", &this->settingsWindowOpened, flags);
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
        ImGui::End();
    }

    if(ImGui::Begin("Element settings"))
    {
//        if(ImGui::Button("Add interpolation target"))
//        {
//            this->interpolations.emplace_back();
//        }
        ImGui::Separator();
        SvgModelContainer *container = this->state->getModelContainer();
        std::unordered_map<std::string, SvgModelContainer::Model> *models = container->getModels();
        for (auto &svgModel : *models)
        {
            ImGui::PushID(svgModel.first.c_str());
            for (VNuint i = 0; i < svgModel.second.elements.size(); i++)
            {
                if (i == 0)
                    continue;
                auto &svgElement = svgModel.second.elements[i];
                ImGui::PushID(i);
                ImGui::SliderFloat("###svgElementInterpolation", &svgElement.targetInterpolation, 0.0f, 1.0f);

//                container->scheduleModelUpdate(svgModel.first);
                ImGui::PopID();
            }
            ImGui::PopID();
        }
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
        ImGui::End();
    }


    if(ImGui::Begin("Render viewport"))
    {
        ImGui::BeginChild("Render side");

        ImVec2 wsize = ImGui::GetWindowSize();
        this->model.renderViewportSize = {wsize.x, wsize.y};
        VNuint tex = ((OpenGLFramebuffer*)this->renderFramebuffer.get())->getColorAttachment(0);
        ImGui::Image((void*)(intptr_t)tex, wsize, ImVec2(0, 1), ImVec2(1, 0));
        ImGui::EndChild();
        ImGui::End();
    }

    if(ImGui::Begin("Opened SVG files"))
    {
        ImGuiTreeNodeFlags svgNodeFlags = ImGuiTreeNodeFlags_SpanAvailWidth;
        ImGuiTreeNodeFlags svgNodeLeafFlags = ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_Leaf;
        SvgModelContainer *container = this->state->getModelContainer();
        auto *documentContainer = container->getDocuments();

        for (auto &document : *documentContainer)
        {
            bool activated = ImGui::TreeNodeEx(document.first.c_str(), svgNodeFlags);
            if (ImGui::BeginPopupContextItem())
            {
                if (ImGui::MenuItem("Close document"))
                    ;
                ImGui::EndPopup();
            }
            if (activated)
            {
                ImGui::PushID(document.first.c_str());
                for (auto *layer : document.second->getLayers())
                {
                    ImGui::PushID(layer->getName().c_str());
                    if (ImGui::TreeNodeEx(layer->getName().c_str(), svgNodeLeafFlags))
                    {
                        ImGui::TreePop();
                    }
                    ImGui::PopID();
                }
                ImGui::PopID();
                ImGui::TreePop();
            }
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
        ImGui::End();
    }

    if(ImGui::Begin("Scene tree"))
    {
        ImGuiTreeNodeFlags svgNodeFlags = ImGuiTreeNodeFlags_SpanAvailWidth;
        ImGuiTreeNodeFlags svgNodeLeafFlags = ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_Leaf;
        SvgModelContainer *container = this->state->getModelContainer();
        auto *svgModels = container->getModels();

        for (auto &svgModel : *svgModels)
        {
            bool activated = ImGui::TreeNodeEx(svgModel.first.c_str(), svgNodeFlags);
            if (activated)
            {
                ImGui::PushID(svgModel.first.c_str());
                // Todo: change this to index.
                for (VNint i = 0; i < svgModel.second.elements.size(); i++)
                {
                    auto &element = svgModel.second.elements[i];
                    ImGui::PushID(i);
                    activated = ImGui::TreeNodeEx(element.name.c_str(), svgNodeLeafFlags);
                    if (activated)
                    {
                        ImGui::TreePop();
                    }
                    ImGui::PopID();
                }
                ImGui::PopID();
                ImGui::TreePop();
            }
        }
        ImGui::End();
    }

    ImGui::Render();
    glViewport(0, 0, window->getWidth(), window->getHeight());
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

Gui::Model *Gui::getModel() noexcept
{
    return &this->model;
}
