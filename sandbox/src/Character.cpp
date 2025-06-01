#include "Character.h"

void Player::OnInit()
{
  m_Body->CreateBody({ 2.0f, 2.0f }, { 1.0f, 5.0f }, 45.0f, { 0.2f, 0.3f, 0.1f, 1.0f });
}

void Player::OnUpdate(float dt, Freeze::Camera& camera)
{
  b2Vec2 velocity = m_Body->GetBody()->GetLinearVelocity(); 
  b2Vec2 position = m_Body->GetBody()->GetPosition(); 

  if(Freeze::KeyboardInput::IsKeyPressed(GLFW_KEY_D))
  {
    velocity.x += acc * dt;
  } else if(Freeze::KeyboardInput::IsKeyPressed(GLFW_KEY_A))
  {
    velocity.x -= acc * dt;
  } else if(Freeze::KeyboardInput::IsKeyReleased(GLFW_KEY_D) || Freeze::KeyboardInput::IsKeyReleased(GLFW_KEY_A)) {
    velocity.x *= 0.8f;
  }

  if (Freeze::KeyboardInput::IsKeyPressed(GLFW_KEY_SPACE))
  {
      // This is your jump impulse, crank it up or down
      float jumpImpulse = 2.0f;
      m_Body->GetBody()->ApplyLinearImpulseToCenter(b2Vec2(0.0f, jumpImpulse), true);
  }

  camera.SetPosition(glm::vec3(position.x, position.y, 0.0f));

  velocity.x = std::clamp(velocity.x, -MAX_SPEED, MAX_SPEED);

  b2Vec2 currentVelocity = m_Body->GetBody()->GetLinearVelocity();
  currentVelocity.x = velocity.x; // keep your controlled horizontal velocity
  m_Body->GetBody()->SetLinearVelocity(currentVelocity);
}

void Player::OnDestroy()
{

}
