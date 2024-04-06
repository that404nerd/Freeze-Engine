#pragma once

#include <glm/glm.hpp>
#include <memory>

#include "physics/PhysicsBody.h"
#include "renderer/Camera.h"
#include "renderer/Renderer2D.h"

#include "core/AudioSystem.h"
#include "Player.h"

class World {
public:
    World();

    void Init();
    void InitPlatformData();
    void RenderPlatform();

    void OnImGui();

    glm::mat4 GetCurrentProjectionMatrix() { return m_Camera->GetProjectionViewMatrix(); }
    std::shared_ptr<Player> GetPlayerInstance() { return m_Player; }

    void Update(GLFWwindow* window, float deltaTime);

    ~World();
private:
    std::shared_ptr<Freeze::Camera> m_Camera;
    std::shared_ptr<Freeze::Audio> m_Audio;

    std::shared_ptr<Freeze::Physics::StaticBody> m_Platform = std::make_shared<Freeze::Physics::StaticBody>();

    std::shared_ptr<Player> m_Player = std::make_shared<Player>();
private:
    bool m_OpenImGui = true;

    float m_CamRotationDefVal = 0.0f;
    const glm::vec3 m_CamDefPos = { 0.0f, 0.0f, 0.0f };
    float m_CamSpeed = 0.0f;
};
