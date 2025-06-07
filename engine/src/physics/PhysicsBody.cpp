#include "PhysicsBody.h"
#include <typeinfo>

namespace Freeze {

  namespace Physics {
    
    ////////////////////// DYNAMIC BODY ///////////////////////

    void DynamicBody::CreateBody(const b2Vec2& size, const b2Vec2& positions, float rotation, glm::vec4 color) {

      GetPhysicsBodyDataInst()->PhysicsEntity = PhysicsModule::GetPhysicsEntManager().CreateEntity();

      // Refering to PhysicsEntManager since naming it just EntManager is kinda confusing so whatever...
      auto& physicsComponentType = PhysicsModule::GetPhysicsEntManager().AddComponent<Freeze::PhysicsComponent>(GetPhysicsBodyDataInst()->PhysicsEntity);

      // Initialize size and position
      physicsComponentType.Size = size;
      physicsComponentType.Positions = positions;
      physicsComponentType.Rotation = rotation;

      // Calculate half body size
      b2Vec2 halfBodySize = b2Vec2(size.x * 0.5f, size.y * 0.5f);

      // Configure body definition
      GetPhysicsBodyDataInst()->BodyDef.type = b2_dynamicBody;
      GetPhysicsBodyDataInst()->BodyDef.position = physicsComponentType.Positions;
      GetPhysicsBodyDataInst()->BodyDef.angle = physicsComponentType.Rotation;

      GetPhysicsBodyDataInst()->Body = PhysicsModule::GetPhysicsWorld()->CreateBody(&GetPhysicsBodyDataInst()->BodyDef);
      // Set shape as a box
      GetPhysicsBodyDataInst()->Shape.SetAsBox(halfBodySize.x, halfBodySize.y);

      // Configure fixture definition
      GetPhysicsBodyDataInst()->FixtureDef.shape = &GetPhysicsBodyDataInst()->Shape;
      GetPhysicsBodyDataInst()->FixtureDef.density = physicsComponentType.Density;
      GetPhysicsBodyDataInst()->FixtureDef.friction = physicsComponentType.Friction;
      GetPhysicsBodyDataInst()->FixtureDef.restitution = physicsComponentType.Restitution;

      // Create fixture
      GetPhysicsBodyDataInst()->Body->CreateFixture(&GetPhysicsBodyDataInst()->FixtureDef);
      GetPhysicsBodyDataInst()->BodyID = GetPhysicsBodyDataInst()->BodyID; // Set the Body ID

      physicsComponentType.Color = color;

      GetPhysicsBodyDataInst()->Body->GetUserData().pointer = reinterpret_cast<uintptr_t>(GetPhysicsBodyDataInst().get());
      physicsComponentType.RuntimeBody = GetPhysicsBodyDataInst()->Body;
    }


    void StaticBody::CreateBody(const b2Vec2& size, const b2Vec2& positions, float rotation, glm::vec4 color)
    {
      GetPhysicsBodyDataInst()->PhysicsEntity = PhysicsModule::GetPhysicsEntManager().CreateEntity();
      auto& physicsComponentType = PhysicsModule::GetPhysicsEntManager().AddComponent<Freeze::PhysicsComponent>(GetPhysicsBodyDataInst()->PhysicsEntity);

      // Initialize size and position
      physicsComponentType.Size = size;
      physicsComponentType.Positions = positions;
      physicsComponentType.Rotation = rotation;

      b2Vec2 halfBodySize = b2Vec2(size.x * 0.5f, size.y * 0.5f);

      GetPhysicsBodyDataInst()->BodyDef.type = b2_staticBody;
      GetPhysicsBodyDataInst()->BodyDef.position = physicsComponentType.Positions;
      GetPhysicsBodyDataInst()->BodyDef.angle = physicsComponentType.Rotation;
      
      GetPhysicsBodyDataInst()->Body = PhysicsModule::GetPhysicsWorld()->CreateBody(&GetPhysicsBodyDataInst()->BodyDef);
      GetPhysicsBodyDataInst()->Shape.SetAsBox(halfBodySize.x, halfBodySize.y, b2Vec2(0.0f, 0.0f), 0.0f);

      GetPhysicsBodyDataInst()->Body->CreateFixture(&GetPhysicsBodyDataInst()->Shape, 0.0f);

      physicsComponentType.Color = color;

      GetPhysicsBodyDataInst()->Body->GetUserData().pointer = reinterpret_cast<uintptr_t>(GetPhysicsBodyDataInst().get());
      physicsComponentType.RuntimeBody = GetPhysicsBodyDataInst()->Body;
    }

  }

}
