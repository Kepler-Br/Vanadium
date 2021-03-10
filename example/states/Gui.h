#ifndef VANADIUM_GUI_H
#define VANADIUM_GUI_H

#include "include/vanadium/Vanadium.h"


using namespace Vanadium;

class CustomState;

class Gui
{
public:
    struct Model
    {
    public:
        glm::vec2 renderViewportSize = {1.0f, 1.0f};

        glm::vec3 borderColor = glm::vec3(1.0f);
        glm::vec3 fillColor = glm::vec3(0.0f, 0.0f, 0.0f);
        glm::vec3 auraColor = glm::vec3(1.0f, 0.0f, 0.0f);
        VNfloat interpolation = 0.726f;
        VNfloat deltaSpeed = 1.0f;
        VNfloat glowPower = 0.5f;
        VNint quality = 5;
        VNint skipSteps = 5;
        bool immediateInterpolation = false;
        bool hueScrolling = false;
        bool isFastBlur = false;
        bool skipInterpolationFrames = false;
        bool extrapolation = false;

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

    struct Item
    {
        std::string name = "None";
        VNfloat interpolation = 0.0f;
    };

    std::vector<Item> interpolations;

private:
    Model model;
    Ref<Framebuffer> renderFramebuffer;
    UserEndApplication *application;

    bool settingsWindowOpened = false;
    CustomState *state;

public:
    Gui(Ref<Framebuffer> renderFramebuffer, UserEndApplication *application, CustomState *state);
    ~Gui();

    void render();

    [[nodiscard]]
    Model *getModel() noexcept;
};

#endif //VANADIUM_GUI_H
