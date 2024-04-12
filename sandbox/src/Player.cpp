#include "Player.h"

Player::Player() : Entity("Player"), m_X(0.0f), m_Y(0.0f) {
    FZ_INFO("Entity: {}", PrintEntityName());
    m_PhysicsEntity = std::make_shared<Freeze::Physics::DynamicBody>();
    m_PhysicsEntity1 = std::make_shared<Freeze::Physics::DynamicBody>();
}

void Player::CreateEntity() {
    for (int i = 0; i < 4; i++) {
        m_PhysicsEntity1->SetFriction(0.3f);
        m_PhysicsEntity1->SetDensity(0.3f);
        m_PhysicsEntity1->SetRestitution(0.4f);
        m_PhysicsEntity1->CreateBody({0.5f, 0.5f}, {0.2 + 0.4f, 0.2 + 0.3f});
    }
}

void Player::MovePlayer(GLFWwindow *window, float dt) {
    if (Freeze::KeyboardInput::IsKeyPressed(window, GLFW_KEY_D)) // Move Right
    {
        m_X += 500.0f * dt;
    }
    if (Freeze::KeyboardInput::IsKeyPressed(window, GLFW_KEY_A)) // Move Left
    {
        m_X -= 500.0f * dt;
    }
    if (Freeze::KeyboardInput::IsKeyPressed(window, GLFW_KEY_SPACE)) {
        m_Y += 500.0f * dt;
    }
    if (Freeze::KeyboardInput::IsKeyPressed(window, GLFW_KEY_S)) {
        m_Y -= 500.0f * dt;
    }
}

void Player::OnImGui() {
    ImGui::ColorEdit4("Color", playerColors);

    ImGui::Text("X Coord: %f", m_X);
    ImGui::Text("Y Coord: %f", m_Y);
}

void Player::RenderEntity(const glm::mat4 &projectionMatrix) {
    m_PhysicsEntity->RenderBody({0.4f, 0.1f, 0.7f, 1.0f});


    Freeze::Renderer2D::DrawQuad({ 0.3f, 0.4f }, { 0.2f, 0.2f },{ 0.4f, 0.2f, 0.3f, 1.0f });
    Freeze::Renderer2D::DrawQuad({ 0.4f, 0.7f }, { 0.2f, 0.2f }, { 0.4f, 0.2f, 0.2f, 1.0f});

    Freeze::Renderer2D::DrawTriangle({ 0.5f, 0.6f }, { 0.2f, 0.2f }, { 0.2f, 0.5f, 0.1f, 1.0f });

}

Player::~Player() {}
