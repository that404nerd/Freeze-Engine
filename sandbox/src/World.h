#pragma once

#include "core/Entity.h"
#include "physics/PhysicsBody.h"

#include "Character.h"

#include <memory>

class World 
{
public:
  void OnInit()
  {
    m_Camera = glm::vec4(-16.0f, 16.0f, -9.0f, 9.0f);

    m_PlatformBody->CreateBody({ 200.0f, 1.0f }, { 0.0f, -1.0f });
    m_Player->OnInit();
  }

  void OnUpdate(float dt)
  {
    const auto view = Freeze::Physics::PhysicsModule::GetPhysicsEntManager().GetRegistry().view<Freeze::PhysicsComponent>(); // WTF???

    m_Player->OnUpdate(dt, m_Camera);

    for(auto entity : view)
    {
      auto& physComp = view.get<Freeze::PhysicsComponent>(entity);
      if (physComp.RuntimeBody == nullptr) continue;

      physComp.Positions = physComp.RuntimeBody->GetPosition();
      physComp.Rotation = physComp.RuntimeBody->GetAngle();

      Freeze::Renderer2D::DrawRotatedQuad(
          { physComp.Positions.x, physComp.Positions.y },
          { physComp.Size.x, physComp.Size.y },
          physComp.Rotation,
          physComp.Color
      );
    }
  }

  void OnDestroy()
  {
    m_Player->OnDestroy();
  }

private:
  std::shared_ptr<Freeze::Physics::StaticBody> m_PlatformBody = std::make_shared<Freeze::Physics::StaticBody>("Body2");
  Freeze::Camera m_Camera;
  std::unique_ptr<Player> m_Player = std::make_unique<Player>();
};
