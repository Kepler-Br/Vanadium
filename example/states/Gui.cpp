#include "Gui.h"
#include "imgui_sdl.h"
#include "imgui_opengl3.h"
#include <imgui.h>
#include <imgui_internal.h>
#include "../../vanadium/src/platform/default/DefaultWindow.h"

Gui::Gui(Ref<Framebuffer> renderFramebuffer, UserEndApplication *application):
    renderFramebuffer(std::move(renderFramebuffer)),
    application(application)
{
    const char* glsl_version = "#version 330 core";
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls

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
    {
//        ImGui::Begin("SVG model parameters");
//        ImGui::ColorEdit3("Border color", &model.borderColor.x);
//        ImGui::ColorEdit3("Fill color", &model.fillColor.x);
//        ImGui::SliderFloat("Glow hue", &model.glowHue, 0.0f, 1.0f);
//        ImGui::SliderFloat("Changing speed", &this->model.deltaSpeed, 0.5f, 50.0f);
//        ImGui::SliderFloat("Interpolation", &this->model.interpolation, 0.0f, 1.0f);
//        ImGui::SliderFloat("Glow power", &this->model.glowPower, 0.0f, 2.0f);
//        ImGui::SliderInt("Model quality", &this->model.quality, 0, 50);
//        ImGui::SliderInt("Skip step count", &this->model.skipSteps, 1, 15);
//        ImGui::Checkbox("Hue scrolling", &this->model.hueScrolling);
//        ImGui::Checkbox("Is fast blur", &this->model.isFastBlur);
//        ImGui::Checkbox("Skip interpolation frames", &this->model.skipInterpolationFrames);
//        ImGui::Checkbox("Immediate transformation", &this->model.immediateInterpolation);
//        ImGui::End();
    }
//    {
//        ImGui::Begin("Framebuffer rendering test.");
//        ImGui::BeginChild("Render side");
//
//        ImVec2 wsize = ImGui::GetWindowSize();
//        windowViewportSize = {wsize.x, wsize.y};
////        this->framebufferForGui->resize(wsize.x, wsize.y);
//        VNuint tex = ((OpenGLFramebuffer*)this->framebufferForGui.get())->getColorAttachment(0);
//        ImGui::Image((void*)(intptr_t)tex, wsize, ImVec2(0, 1), ImVec2(1, 0));
////        this->framebufferForGui->resize(wsize.x, wsize.y);
//        ImGui::EndChild();
//        ImGui::End();
//    }
//    {
//        ImGui::Begin("Tree");
//        ImGuiTreeNodeFlags flags = 0;
//
//        flags |= ImGuiTreeNodeFlags_SpanAvailWidth;
//
//        if (ImGui::TreeNodeEx("Some label", flags))
//        {
//            flags |= ImGuiTreeNodeFlags_Leaf;
//
//            bool opened = ImGui::TreeNodeEx("Basic", flags, "Oh noes");
//
//            if (ImGui::BeginPopupContextItem())
//            {
//                if (ImGui::MenuItem("Delete Entity"))
//                    ;
//                ImGui::Separator();
//                ImGui::MenuItem("I'm sorry");
//                ImGui::EndPopup();
//            }
//            if (opened)
//            {
//                ImGui::TreePop();
//            }
//            ImGui::TreePop();
//        }

//            const char* items[] = { "AAAA", "BBBB", "CCCC", "DDDD", "EEEE", "FFFF", "GGGG", "HHHH", "IIIIIII", "JJJJ", "KKKKKKK" };
//            static int item_current = 0;
//            ImGui::Combo("combo", &item_current, items, IM_ARRAYSIZE(items));



//        ImGui::End();
//    }


    bool open = true;

    if (ImGui::DockBuilderGetNode(ImGui::GetID("MyDockSpace")) == NULL)
    {
        ImGuiID dockspace_id = ImGui::GetID("MyDockspace");
        ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::DockBuilderRemoveNode(dockspace_id); // Clear out existing layout
        ImGui::DockBuilderAddNode(dockspace_id); // Add empty node

        ImGuiID dock_main_id = dockspace_id; // This variable will track the document node, however we are not using it here as we aren't docking anything into it.
        ImGuiID dock_id_left = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Left, 0.20f, NULL, &dock_main_id);
        ImGuiID dock_id_top = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Up, 0.80f, NULL, &dock_main_id);
        ImGuiID dock_id_right = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Right, 0.20f, NULL, &dock_main_id);
        ImGuiID dock_id_bottom = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Down, 0.20f, NULL, &dock_main_id);

        ImGui::DockBuilderDockWindow("James_1", dock_id_left);
        ImGui::DockBuilderDockWindow("James_2", dock_id_top);
        ImGui::DockBuilderDockWindow("James_3", dock_id_right);
        ImGui::DockBuilderDockWindow("James_4", dock_id_bottom);
        ImGui::DockBuilderFinish(dockspace_id);
    }

    static bool opt_fullscreen = true;
    static bool opt_padding = false;
    static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

    // We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
    // because it would be confusing to have two docking targets within each others.
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
    if (opt_fullscreen)
    {
        const ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->WorkPos);
        ImGui::SetNextWindowSize(viewport->WorkSize);
        ImGui::SetNextWindowViewport(viewport->ID);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
        window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
    }
    else
    {
        dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
    }

    // When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
    // and handle the pass-thru hole, so we ask Begin() to not render a background.
    if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
        window_flags |= ImGuiWindowFlags_NoBackground;

    // Important: note that we proceed even if Begin() returns false (aka window is collapsed).
    // This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
    // all active windows docked into it will lose their parent and become undocked.
    // We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
    // any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
    if (!opt_padding)
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGui::Begin("DockSpace Demo", nullptr, window_flags);
    if (!opt_padding)
        ImGui::PopStyleVar();

    if (opt_fullscreen)
        ImGui::PopStyleVar(2);

    // DockSpace
    ImGuiIO& io = ImGui::GetIO();
    if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
    {
        ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
        ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
//        if (ImGui::DockBuilderGetNode(dockspace_id) == nullptr)
//        {
//            ImGui::DockBuilderRemoveNode(dockspace_id); // Clear out existing layout
//            ImGui::DockBuilderAddNode(dockspace_id, ImGuiDockNodeFlags_DockSpace); // Add empty node
//            ImGui::DockBuilderSetNodeSize(dockspace_id, {80, 60});
//
//            ImGuiID dock_main_id = dockspace_id; // This variable will track the document node, however we are not using it here as we aren't docking anything into it.
//            ImGuiID dock_id_prop = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Left, 0.20f, NULL, &dock_main_id);
//            ImGuiID dock_id_bottom = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Down, 0.20f, NULL, &dock_main_id);
//
//            ImGui::DockBuilderDockWindow("SVG model parameters", dock_id_bottom);
//            ImGui::DockBuilderFinish(dockspace_id);
//        }
    }
    else
    {
//        ShowDockingDisabledMessage();
    }

    if (ImGui::BeginMenuBar())
    {
        if (ImGui::BeginMenu("Options"))
        {
            // Disabling fullscreen would allow the window to be moved to the front of other windows,
            // which we can't undo at the moment without finer window depth/z control.
            ImGui::MenuItem("Fullscreen", NULL, &opt_fullscreen);
            ImGui::MenuItem("Padding", NULL, &opt_padding);
            ImGui::Separator();

            if (ImGui::MenuItem("Flag: NoSplit",                "", (dockspace_flags & ImGuiDockNodeFlags_NoSplit) != 0))                 { dockspace_flags ^= ImGuiDockNodeFlags_NoSplit; }
            if (ImGui::MenuItem("Flag: NoResize",               "", (dockspace_flags & ImGuiDockNodeFlags_NoResize) != 0))                { dockspace_flags ^= ImGuiDockNodeFlags_NoResize; }
            if (ImGui::MenuItem("Flag: NoDockingInCentralNode", "", (dockspace_flags & ImGuiDockNodeFlags_NoDockingInCentralNode) != 0))  { dockspace_flags ^= ImGuiDockNodeFlags_NoDockingInCentralNode; }
            if (ImGui::MenuItem("Flag: AutoHideTabBar",         "", (dockspace_flags & ImGuiDockNodeFlags_AutoHideTabBar) != 0))          { dockspace_flags ^= ImGuiDockNodeFlags_AutoHideTabBar; }
            if (ImGui::MenuItem("Flag: PassthruCentralNode",    "", (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode) != 0, opt_fullscreen)) { dockspace_flags ^= ImGuiDockNodeFlags_PassthruCentralNode; }
            ImGui::Separator();

            if (ImGui::MenuItem("Close", NULL, false, false))
                ;
            ImGui::EndMenu();
        }

        ImGui::EndMenuBar();
    }


    ImGui::End();




//    static int initialized = 0;
//    static int new_window = 0;
//    ImGuiWindowFlags flags = ImGuiWindowFlags_MenuBar;
//    flags |= ImGuiWindowFlags_NoDocking;
//    ImGuiViewport* viewport = ImGui::GetMainViewport();
//    ImGui::SetNextWindowPos(viewport->Pos);
//    ImGui::SetNextWindowSize(viewport->Size);
//    ImGui::SetNextWindowViewport(viewport->ID);
//    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
//    flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
//    flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
//    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
//    ImGui::Begin("DockSpace Demo", 0, flags);
//    ImGui::PopStyleVar();
//
//    if (ImGui::BeginMenuBar())
//    {
//        if (initialized == 0)
//        {
//            if (ImGui::Button("1. Initialize"))
//                initialized = 1;
//        }
//        if (initialized > 0 && new_window == 0)
//        {
//            if (ImGui::Button("2. New Window"))
//                new_window = 1;
//        }
//        ImGui::EndMenuBar();
//    }
//
////    ImGuiIO& io = ImGui::GetIO();
//    ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
//
//    if (initialized == 1)
//    {
//        initialized = 2;
//        ImGui::DockBuilderRemoveNode(dockspace_id); // Clear out existing layout
//        ImGui::DockBuilderAddNode(dockspace_id, ImGui::GetMainViewport()->Size.x); // Add empty node
//
//        ImGuiID dock_main_id = dockspace_id; // This variable will track the document node, however we are not using it here as we aren't docking anything into it.
//        ImGuiID dock_id_prop = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Left, 0.20f, NULL, &dock_main_id);
//        ImGuiID dock_id_bottom = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Down, 0.20f, NULL, &dock_main_id);
//
//        ImGui::DockBuilderDockWindow("Log", dock_id_bottom);
//        ImGui::DockBuilderDockWindow("Properties", dock_id_prop);
//        ImGui::DockBuilderFinish(dockspace_id);
//    }
//
//    ImGui::DockSpace(dockspace_id);
//    if (initialized == 2)
//    {
//        ImGui::Begin("Properties");
//
//        ImGui::End();
//
//        ImGui::Begin("Log");
//        ImGui::End();
//    }
//
//    if (new_window == 1)
//    {
//        // Should dock window to empty space, instead window is not docked anywhere.
//        ImGui::SetNextWindowDockID(dockspace_id, ImGuiCond_Once);
//        ImGui::Begin("New Window");
//        ImGui::End();
//    }

//    ImGui::End();
//    ImGui::PopStyleVar();







    ImGui::Render();
    glViewport(0, 0, window->getWidth(), window->getHeight());
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

Gui::Model *Gui::getModel() noexcept
{
    return &this->model;
}
