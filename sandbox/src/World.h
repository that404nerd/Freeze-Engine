#pragma once

#include <glm/glm.hpp>
#include <memory>

#include "physics/PhysicsBody.h"
#include "renderer/Camera.h"
#include "renderer/Renderer2D.h"
#include "core/AudioSystem.h"

#include "event/Event.h"
#include "event/KeyboardInput.h"
#include "event/MouseInput.h"
#include "event/KeyEvent.h"

#include "Player.h"
#include "Enemy.h"

class World {

public:
  World();

  void Init();
  void InitPlatformData();

  static void OnEvent(Freeze::Event& e);

  void OnImGui();

  glm::mat4 GetCurrentProjectionMatrix() { return m_Camera->GetProjectionViewMatrix(); }
  std::shared_ptr<Player> GetPlayerInstance() { return m_Player; }

  void Update(float dt);

  ~World();
private:
  std::shared_ptr<Freeze::Physics::StaticBody> m_Platform = std::make_shared<Freeze::Physics::StaticBody>("Platform");
  std::shared_ptr<Freeze::ShapeRenderer> m_QuadShape = std::make_shared<Freeze::ShapeRenderer>();
  std::shared_ptr<Player> m_Player = std::make_shared<Player>();
  std::shared_ptr<Enemy> m_Enemy = std::make_shared<Enemy>();

  std::shared_ptr<Freeze::Camera> m_Camera;
private:
  bool m_OpenImGui = true;

  float m_CamRotationDefVal = 0.0f;
  const glm::vec3 m_CamDefPos = { 0.0f, 0.0f, 0.0f };
  float m_CamSpeed = 0.0f;
};
