#ifndef VANADIUM_CAMERA_H
#define VANADIUM_CAMERA_H

#include <glm/gtc/matrix_transform.hpp>
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>

namespace Vanadium
{

class Camera
{
private:
    glm::mat4 projection = glm::mat4(1.0f);
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 VP = glm::mat4(1.0f);
    bool shouldUpdateVP = true;

public:
    virtual void setProjection(const glm::mat4 &matrix) noexcept;
    virtual void setView(const glm::mat4 &matrix) noexcept;
    virtual glm::mat4 getVP() noexcept;
    virtual const glm::mat4 &getProjection() noexcept;
    virtual const glm::mat4 &getView() noexcept;
    virtual void lookAt(const glm::vec3 &eye, const glm::vec3 &center, const glm::vec3 &up) noexcept;

};

}
#endif //VANADIUM_CAMERA_H
