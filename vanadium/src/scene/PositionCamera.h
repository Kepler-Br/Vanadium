#ifndef VANADIUM_POSITIONCAMERA_H
#define VANADIUM_POSITIONCAMERA_H

#include "Camera.h"

namespace Vanadium
{

class PositionCamera : public Camera
{
protected:
    glm::vec3 eye;
    glm::vec3 center;
    glm::vec3 up;

public:
    PositionCamera(const glm::vec3 &eye, const glm::vec3 &center, const glm::vec3 &up);
    ~PositionCamera() override = default;
    void lookAt(const glm::vec3 &eye, const glm::vec3 &center, const glm::vec3 &up) noexcept override;
    void addLookAt(const glm::vec3 &eye, const glm::vec3 &center, const glm::vec3 &up) noexcept;
    void addPosition(const glm::vec3 &position);
    void setPosition(const glm::vec3 &position);
    const glm::vec3 &getPosition();
    const glm::vec3 &getCenter();
    void setCenter(const glm::vec3 &newCenter);
    void addCenter(const glm::vec3 &newCenter);
    const glm::vec3 &getWorldUp();

};

}

#endif //VANADIUM_POSITIONCAMERA_H
