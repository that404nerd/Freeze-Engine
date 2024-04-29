#include "Player.h"

Player::Player() 
    : Entity("Player")
{
    FZ_INFO("Entity: {}", PrintEntityName());
}

void Player::CreateEntity() {

    {
        m_PhysicsEntity->SetFriction(0.3f);
        m_PhysicsEntity->SetDensity(0.3f);
        m_PhysicsEntity->SetRestitution(0.8f);
        m_PhysicsEntity->CreateBody({ 3.0f, 3.0f }, { 0.0f, 3.0f });
    }

    {
        float x = -22.0f; // Start from the left boundary
        float y = 15.0f;  // Start from the top boundary
        // Set properties and create body for m_PhysicsEntity1
        m_PhysicsEntity1->SetFriction(0.3f);
        m_PhysicsEntity1->SetDensity(0.3f); // You might want to set restitution here too if needed
        m_PhysicsEntity1->SetRestitution(0.5f);
        m_PhysicsEntity1->CreateBody({ 2.0f, 1.0f }, { x, y });
    }
}

void Player::MovePlayer() {
}

void Player::OnImGui() {
    if(ImGui::Button("Create body"))
    {
        m_PhysicsEntity->CreateBody({ 1.0f, 1.0f }, { 0.0f, 0.0f });
    }
}

void Player::RenderEntity() 
{
    m_PhysicsEntity->RenderBody({ 0.2f, 0.1f, 0.4f, 1.0f });

    // Manual way of doing physics rendering
    b2Vec2 position = m_PhysicsEntity1->GetBodyData()->Body->GetPosition();
    b2Vec2 size = m_PhysicsEntity1->GetBodyData()->Size;
    m_Shape->DrawQuad({ position.x, position.y }, { size.x, size.y }, { 0.2f, 0.1f, 0.4f, 1.0f });
}

Player::~Player() {}
