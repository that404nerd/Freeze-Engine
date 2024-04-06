#include "Camera.h"

namespace Freeze
{
    Camera::Camera(const glm::vec4 &camBounds)
        : m_ProjectionMatrix(glm::ortho(camBounds.x, camBounds.y, camBounds.z, camBounds.w, -1.0f, 1.0f)), // Create a ortho camera because it's 2D!
          m_CameraBounds(camBounds),
          m_ViewMatrix(glm::mat4(1.0f))
    {
        m_ProjectionViewMatrix = m_ProjectionMatrix * m_ViewMatrix;
    }

    void Camera::CalculateViewMatrix()
    {
        // Calculate the transformation matrix (translation * rotation)
        glm::mat4 transformMatrix =
            glm::translate(glm::mat4(1.0f), m_Position) *
            glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation), glm::vec3(0.0f, 0.0f, 1.0f));

        m_ViewMatrix = glm::inverse(transformMatrix); // View Matrix / Camera - Just the inverse of the transformation matrix
        m_ProjectionViewMatrix = m_ProjectionMatrix * m_ViewMatrix; // Make sure to calculate the projection view matrix
    }

    Camera::~Camera() {}
};
