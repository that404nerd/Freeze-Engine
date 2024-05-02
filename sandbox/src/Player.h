#pragma once

#include <glm/glm.hpp>
#include <imgui.h>

#include <memory>

#include "core/Core.h"
#include "event/Event.h"
#include "event/KeyEvent.h"
#include "event/MouseEvent.h"

#include "Entity.h"
#include "renderer/Renderer2D.h"
#include "physics/PhysicsBody.h"

class Player : public Entity {
public:
  Player();

  void CreateEntity() override;
  void RenderEntity() override;

  void OnImGui();

  void MovePlayer();

  ~Player();
private:
  std::shared_ptr<Freeze::Physics::DynamicBody> m_PhysicsEntity = std::make_shared<Freeze::Physics::DynamicBody>(); // dynamic
  Freeze::ShapeRenderer* m_Shape = new Freeze::ShapeRenderer();
};
