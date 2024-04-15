#include "Player.h"

Player::Player() 
    : Entity("Player")
{
    FZ_INFO("Entity: {}", PrintEntityName());
}

void Player::CreateEntity() {

    m_PhysicsEntity->SetFriction(0.3f);
    m_PhysicsEntity->SetDensity(0.3f);
    m_PhysicsEntity->SetRestitution(0.8f);
    m_PhysicsEntity->CreateBody({ 1.0f, 1.0f }, { 0.0f, 2.0f });

    m_PhysicsEntity1->SetFriction(0.3f);
    m_PhysicsEntity1->SetDensity(0.3f);
    m_PhysicsEntity1->SetRestitution(0.5f);

    float x = 3.0f;
    float y = 2.0;

    for (int i = 0; i < 4; i++) {
        m_PhysicsEntity1->SetFriction(0.3f);
        m_PhysicsEntity1->SetDensity(0.3f);
        m_PhysicsEntity1->SetRestitution(0.4f);
        m_PhysicsEntity1->CreateBody({ 1.0f, 1.0f }, { x, y });

        x += 2.0f;
        y += 2.0f;
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
