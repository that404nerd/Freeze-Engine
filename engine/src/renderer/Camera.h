#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "core/Core.h"

/* Basic Camera System.
   Keyboard Controls are supported now! (31-12-2023)
   Rotation is supported only in the z-axis otherwise you would see weird results!
   For now there is no Update() function and whenever you set a position / rotation manually it recalculates the view matrix which is fine.
*/

namespace Freeze {

    class Camera {
    public:
        Camera() {};
        Camera(const glm::vec4& camPos);

        void SetPosition(const glm::vec3& position) { m_Position = position; CalculateViewMatrix(); }
        void SetRotation(float rotation) { m_Rotation = rotation; CalculateViewMatrix(); }

        const glm::vec3& GetPosition() const { return m_Position; }
        const float GetRotation() const { return m_Rotation; }

        // Required for the shader so that positions and rotation works!
        const glm::mat4 GetProjectionViewMatrix() const { return m_ProjectionViewMatrix; }

        static glm::vec4 GetCameraBounds() { return m_CameraBounds; }

        void CalculateViewMatrix();
        void Update();

        ~Camera();
    private:
      glm::mat4 m_ProjectionMatrix;
      glm::mat4 m_ViewMatrix;
      glm::mat4 m_ProjectionViewMatrix;

      static glm::vec4 m_CameraBounds; 

      glm::vec3 m_Position = glm::vec3(0.0f, 0.0f, 0.0f);
      float m_Rotation = 0.0f;
    };

};
