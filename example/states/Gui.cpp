#include "Gui.h"
#include "imgui_sdl.h"
#include "imgui_opengl3.h"
#include <imgui.h>
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
        ImGui::Begin("SVG model parameters");
        ImGui::ColorEdit3("Border color", &model.borderColor.x);
        ImGui::ColorEdit3("Fill color", &model.fillColor.x);
        ImGui::SliderFloat("Glow hue", &model.glowHue, 0.0f, 1.0f);
        ImGui::SliderFloat("Changing speed", &this->guiModel.deltaSpeed, 0.5f, 50.0f);
        ImGui::SliderFloat("Interpolation", &this->guiModel.interpolation, 0.0f, 1.0f);
        ImGui::SliderFloat("Glow power", &this->guiModel.glowPower, 0.0f, 2.0f);
        ImGui::SliderInt("Model quality", &this->guiModel.quality, 0, 50);
        ImGui::Checkbox("Hue scrolling", &this->guiModel.hueScrolling);
        ImGui::Checkbox("Is fast blur", &this->guiModel.isFastBlur);
        ImGui::Checkbox("Skip interpolation frames", &this->guiModel.skipInterpolationFrames);
//        if(ImGui::BeginCombo("##Oh noes", "Shh~~", 1))
//        {
//            ImGui::Text("Shit");
//            ImGui::EndCombo();
//        }

        ImGui::End();
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
    {
        ImGui::Begin("Tree");
        ImGuiTreeNodeFlags flags = 0;

        flags |= ImGuiTreeNodeFlags_SpanAvailWidth;

        if (ImGui::TreeNodeEx("Some label", flags))
        {
            flags |= ImGuiTreeNodeFlags_Leaf;

            bool opened = ImGui::TreeNodeEx("Basic", flags, "Oh noes");

            if (ImGui::BeginPopupContextItem())
            {
                if (ImGui::MenuItem("Delete Entity"))
                    ;
                ImGui::Separator();
                ImGui::MenuItem("I'm sorry");
                ImGui::EndPopup();
            }
            if (opened)
            {
                ImGui::TreePop();
            }
            ImGui::TreePop();
        }

//            const char* items[] = { "AAAA", "BBBB", "CCCC", "DDDD", "EEEE", "FFFF", "GGGG", "HHHH", "IIIIIII", "JJJJ", "KKKKKKK" };
//            static int item_current = 0;
//            ImGui::Combo("combo", &item_current, items, IM_ARRAYSIZE(items));



        ImGui::End();
    }

    ImGui::Render();
    glViewport(0, 0, this->window->getWidth(), this->window->getHeight());
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

const Gui::Model *Gui::getModel() const noexcept
{
    return &this->model;
}
