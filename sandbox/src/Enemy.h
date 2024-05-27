#pragma once

#include "Entity.h"

#include "physics/PhysicsBody.h"
#include "event/KeyboardInput.h"
#include "renderer/Renderer2D.h"

#include <memory>

class Enemy : public Entity {
public:
  Enemy();
  void CreateEntity() override;
  void RenderEntity(float dt) override;

  void OnEvent(Freeze::Event& event);

  ~Enemy() = default;
private:
  std::shared_ptr<Freeze::Physics::DynamicBody> m_EnemyBody = std::make_shared<Freeze::Physics::DynamicBody>("Enemy");
  std::shared_ptr<Freeze::ShapeRenderer> m_EnemyShape = std::make_shared<Freeze::ShapeRenderer>();
};
