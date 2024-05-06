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
  m_PhysicsEntity->CreateBody({ 3.0f, 3.0f }, { 0.0f, 3.0f });
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
  if(Freeze::KeyboardInput::IsKeyPressed(GLFW_KEY_Q))
  {
    m_PhysicsEntity->MoveBody(b2Vec2(20.0f, 0.0f), Freeze::Physics::DynamicBody::BODY_DIRECTION::RIGHT);
  }

  m_PhysicsEntity->RenderBody({ 0.2f, 0.1f, 0.4f, 1.0f });
}

Player::~Player() {}
