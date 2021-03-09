#ifndef VANADIUM_CUSTOMSTATE_H
#define VANADIUM_CUSTOMSTATE_H

#include "../../src/include/vanadium/Vanadium.h"

using namespace Vanadium;

class CustomState : public State
{
private:
    struct GuiModel
    {
    private:
        VNfloat interpolationOld = this->interpolation;
        VNfloat deltaSpeedOld = this->deltaSpeed;
        VNint qualityOld = this->quality;

    public:
        glm::vec3 borderColor = glm::vec3(1.0f);
        glm::vec3 fillColor = glm::vec3(1.0f, 0.0f, 0.0f);
        VNfloat glowHue = 1.0f;
        VNfloat interpolation = 0.0f;
        VNfloat deltaSpeed = 0.5f;
        VNfloat glowPower = 1.0f;
        VNint quality = 5;

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
    };

private:
    GuiModel guiModel;

    Ref<Shader> shader;
    Ref<Texture> texture;
    Ref<Mesh> mesh;
    Ref<Camera> camera;
    Ref<Framebuffer> framebuffer;

    Ref<Mesh> screenPlane;
    Ref<Shader> framebufferShader;

    Ref<Shader> lineShader;
    Ref<Mesh> svgPath;
    Ref<Mesh> svgPathTriangulated;
    Ref<Mesh> pathInterpolated;

    Ref<Postprocessing> glow;

    std::vector<VNfloat> firstFrame;
    std::vector<VNfloat> lastFrame;
    std::vector<VNfloat> interpolatedFrame;
    Ref<Shader> blurShader;

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
