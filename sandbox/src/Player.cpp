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
        // m_PhysicsEntity->SetRestitution(0.8f);
        m_PhysicsEntity->CreateBody({ 3.0f, 3.0f }, { 0.0f, 3.0f });
    }

    {
        float x = -22.0f; // Start from the left boundary
        float y = 15.0f;  // Start from the top boundary
        for(int i = 0; i < 10; i++)
        {
            // Set properties and create body for m_PhysicsEntity1
            m_PhysicsEntity1->SetFriction(0.3f);
            m_PhysicsEntity1->SetDensity(0.3f); // You might want to set restitution here too if needed
            m_PhysicsEntity1->SetRestitution(0.5f);
            m_PhysicsEntity1->CreateBody({ 1.0f, 1.0f }, { x += 1.0f, y += 1.0f });
        }
    }
}

void Player::MovePlayer(float dt) {
  
}

void Player::OnImGui() {
}

void Player::RenderEntity() 
{
    m_PhysicsEntity->RenderBody({ 0.2f, 0.1f, 0.4f, 1.0f });
    m_PhysicsEntity1->RenderBody({ 0.2f, 0.1f, 0.4f, 1.0f });
}

Player::~Player() {}
