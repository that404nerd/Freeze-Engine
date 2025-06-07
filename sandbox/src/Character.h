#pragma once

#include <memory>

#include "core/Entity.h"
#include "physics/PhysicsBody.h"
#include "event/KeyboardInput.h"
#include "renderer/Camera.h"

class Character {
public:
  Character() {};

  virtual void OnInit() = 0;
  virtual void OnUpdate(float dt, Freeze::Camera& camera) = 0;
  virtual void OnDestroy() = 0;

  glm::vec2& GetPosition() { return m_Positions; }
  glm::vec2& GetSize() { return m_Size; }
  float GetRotation() { return m_Rotation; }

  virtual ~Character() {};
private:
  glm::vec2 m_Positions, m_Size;
  float m_Rotation;
};

class Player : public Character {
public:

  void OnInit() override;
  void OnUpdate(float dt, Freeze::Camera& camera) override;
  void OnDestroy() override;

private:
  b2Vec2 m_Velocity;

  const float acc = 30.0f;
  const float MAX_SPEED = 30.0f;
  
  int jumpCount = 2;

  std::shared_ptr<Freeze::Physics::DynamicBody> m_Body = std::make_shared<Freeze::Physics::DynamicBody>("Player");
};
