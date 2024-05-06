#include "Enemy.h"

Enemy::Enemy()
  : Entity("Enemy")
{
  FZ_INFO("Entity: {}", Entity::PrintEntityName());
}

void Enemy::CreateEntity()
{
  float x = -2.0f;
  float y = 3.0f;

  for(int i = 0; i < 1; i++)
  {
    m_EnemyBody->SetFriction(0.3f);
    m_EnemyBody->SetDensity(0.3f);
    m_EnemyBody->SetRestitution(0.4f);
    m_EnemyBody->CreateBody({ 2.0f, 2.0f }, { x, y });

    x += 1.0f;
    y += 1.0f;
  }
}

void Enemy::OnEvent(Freeze::Event& e)
{

}

void Enemy::RenderEntity()
{
  if(Freeze::KeyboardInput::IsKeyPressed(GLFW_KEY_X))
  {
    m_EnemyBody->MoveBody(b2Vec2(20.0f, 0.0f), Freeze::Physics::DynamicBody::BODY_DIRECTION::RIGHT);
  }

  m_EnemyBody->RenderBody({ 0.8f, 0.2f, 0.1f, 1.0f });
}
