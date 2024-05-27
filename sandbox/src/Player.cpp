#include "Player.h"

Player::Player() : Entity("Player") {
  FZ_INFO("Entity: {}", PrintEntityName());
}

void Player::CreateEntity() {
  m_PhysicsEntity->SetFriction(0.3f);
  m_PhysicsEntity->SetDensity(0.3f);
  m_PhysicsEntity->CreateBody({2.0f, 2.0f}, {0.0f, 5.0f}, 70.0f);
}

void Player::MovePlayer() {}

void Player::OnImGui() {
 
}

void Player::RenderEntity(float dt) {
  if (Freeze::KeyboardInput::IsKeyPressed(GLFW_KEY_Q)) {
    m_PhysicsEntity->MoveBody(b2Vec2(20.0f, 0.0f), Freeze::Physics::DynamicBody::BODY_DIRECTION::RIGHT);
  }

  m_PhysicsEntity->GetBody()->SetTransform(m_PhysicsEntity->GetBody()->GetPosition(), m_PhysicsEntity->GetBody()->GetAngle());
  float entityRotation = m_PhysicsEntity->GetBody()->GetAngle();
  m_PlayerShape->DrawRotatedQuad({ m_PhysicsEntity->GetBody()->GetPosition().x, m_PhysicsEntity->GetBody()->GetPosition().y }, 
                     { m_PhysicsEntity->GetBodyData()->Size.x, m_PhysicsEntity->GetBodyData()->Size.y }, 
                     entityRotation,
                     { 0.6f, 0.1f, 0.3f, 1.0f });
}

Player::~Player() {}
