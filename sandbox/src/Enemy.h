#pragma once

#include "Entity.h"

#include "physics/PhysicsBody.h"
#include "event/KeyboardInput.h"

class Enemy : public Entity {
public:
  Enemy();
  void CreateEntity() override;
  void RenderEntity() override;

  void OnEvent(Freeze::Event& event);

  ~Enemy() = default;
private:
  std::shared_ptr<Freeze::Physics::DynamicBody> m_EnemyBody = std::make_shared<Freeze::Physics::DynamicBody>("Enemy");
};
