#include "Camera.h"

namespace Vanadium
{

void Camera::setProjection(const glm::mat4 &matrix) noexcept
{
    this->shouldUpdateVP = true;
    this->projection = matrix;
}

void Camera::setView(const glm::mat4 &matrix) noexcept
{
    this->shouldUpdateVP = true;
    this->view = matrix;
}

glm::mat4 Camera::getVP() noexcept
{
    if (this->shouldUpdateVP)
    {
        this->shouldUpdateVP = false;
        this->VP = this->projection * this->view;
    }
    return this->VP;
}

const glm::mat4 &Camera::getProjection() noexcept
{
    return this->projection;
}

const glm::mat4 &Camera::getView() noexcept
{
    return this->view;
}

void Camera::lookAt(const glm::vec3 &eye, const glm::vec3 &center, const glm::vec3 &up) noexcept
{
    this->shouldUpdateVP = true;
    this->projection = glm::lookAt(eye, center, up);
}

}