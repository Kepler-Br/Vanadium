#ifndef VANADIUM_CUSTOMSTATE_H
#define VANADIUM_CUSTOMSTATE_H

#include "../../src/include/vanadium/Vanadium.h"

using namespace Vanadium;

class CustomState : public State
{
private:
    struct GuiModel
    {
    public:
        glm::vec3 borderColor = glm::vec3(1.0f);
        glm::vec3 fillColor = glm::vec3(0.0f, 0.0f, 0.0f);
        VNfloat glowHue = 1.0f;
        VNfloat interpolation = 0.726f;
        VNfloat deltaSpeed = 1.0f;
        VNfloat glowPower = 0.5f;
        VNint quality = 5;
        bool hueScrolling = false;
        bool isFastBlur = false;
        bool skipInterpolationFrames = false;

        bool interpolationUpdated()
        {
            if (this->interpolation != this->interpolationOld)
            {
                this->interpolationOld = this->interpolation;
                return true;
            }
            return false;
        }

        bool deltaSpeedUpdated()
        {
            if (this->deltaSpeed != this->deltaSpeedOld)
            {
                this->deltaSpeedOld = this->deltaSpeed;
                return true;
            }
            return false;
        }

        bool qualityUpdated()
        {
            if (this->quality != this->qualityOld)
            {
                this->qualityOld = this->quality;
                return true;
            }
            return false;
        }

    private:
        VNfloat interpolationOld = this->interpolation;
        VNfloat deltaSpeedOld = this->deltaSpeed;
        VNint qualityOld = this->quality;
    };

private:
    GuiModel guiModel;

    Ref<Texture> texture;
    Ref<Camera> camera;

    Ref<Shader> lineShader;
    Ref<Mesh> svgPathTriangulated;
    Ref<Mesh> pathInterpolated;

    Ref<Postprocessing> glow;
    Ref<Postprocessing> fastGlow;

    Ref<Framebuffer> framebufferForGui;

    std::vector<VNfloat> firstFrame;
    std::vector<VNfloat> lastFrame;
    std::vector<VNfloat> interpolatedFrame;

    glm::vec2 windowViewportSize = glm::vec2(800, 600);

    VNfloat currentInterpolation = 0.726f;
    bool deltaUpdated = true;

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

};


#endif //VANADIUM_CUSTOMSTATE_H
