#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <imgui.h>

#include <memory>

#include "core/Core.h"

#include "Entity.h"
#include "renderer/Renderer2D.h"
#include "physics/PhysicsBody.h"

class Player : public Entity {
public:
    Player();

    void CreateEntity() override;
    void RenderEntity() override;

    void OnImGui();

    void MovePlayer(float dt);

    ~Player();
private:
    std::shared_ptr<Freeze::Physics::DynamicBody> m_PhysicsEntity = std::make_shared<Freeze::Physics::DynamicBody>(); // dynamic
    std::shared_ptr<Freeze::Physics::DynamicBody> m_PhysicsEntity1 = std::make_shared<Freeze::Physics::DynamicBody>(); // dynamic

    glm::mat4 m_PlayerMove = glm::mat4(1.0f); 
    glm::vec4 m_ColorChoose = { 0.3f, 0.6f, 0.4f, 0.2f };
    float playerColors[4] = { 0.3f, 0.6f, 0.4f, 0.2f };
};
