#include "PhysicsBody.h"

namespace Freeze {

  namespace Physics {
    
    ////////////////////// DYNAMIC BODY ///////////////////////
    DynamicBody::DynamicBody(const std::string& bodyID)
      : m_Friction(0.0f), m_Density(0.0f), m_Restitution(0.0f), /* m_DefDirection(BODY_DIRECTION::RIGHT) */ m_BodyID(bodyID)
    {
    }

    void DynamicBody::CreateBody(const b2Vec2& size, const b2Vec2& positions, float rotation, glm::vec4 color) {

      m_PhysicsBodyData->PhysicsEntity = PhysicsModule::GetPhysicsEntManager().CreateEntity();

      // Refering to PhysicsEntManager since naming it just EntManager is kinda confusing so whatever...
      auto& physicsComponentType = PhysicsModule::GetPhysicsEntManager().AddComponent<Freeze::PhysicsComponent>(m_PhysicsBodyData->PhysicsEntity);

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
      GetPhysicsBodyDataInst()->BodyID = m_BodyID;

      physicsComponentType.Body = GetPhysicsBodyDataInst()->Body;

      physicsComponentType.Color = color;

    }

    DynamicBody::~DynamicBody()
    {
    }
    
    /////////////////////// STATIC BODY ////////////////////
    StaticBody::StaticBody(const std::string& bodyID)
      : m_BodyID(bodyID)
    {
    }

    void StaticBody::CreateBody(const b2Vec2& size, const b2Vec2& positions, float rotation, glm::vec4 color)
    {
      m_PhysicsBodyData->PhysicsEntity = PhysicsModule::GetPhysicsEntManager().CreateEntity();
      auto& physicsComponentType = PhysicsModule::GetPhysicsEntManager().AddComponent<Freeze::PhysicsComponent>(m_PhysicsBodyData->PhysicsEntity);

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

      physicsComponentType.Body = GetPhysicsBodyDataInst()->Body;

      physicsComponentType.Color = color;

    }

    StaticBody::~StaticBody()
    {
    }


  }

}
