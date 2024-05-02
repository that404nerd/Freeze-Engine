#pragma once

#include "Entity.h"

#include "physics/PhysicsBody.h"

class Enemy : public Entity {
public:
  Enemy();
  void CreateEntity() override;
  void RenderEntity() override;

  ~Enemy() = default;
private:
    std::shared_ptr<Freeze::Physics::DynamicBody> m_EnemyBody = std::make_shared<Freeze::Physics::DynamicBody>();
};
