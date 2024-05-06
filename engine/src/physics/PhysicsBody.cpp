#include "PhysicsBody.h"

namespace Freeze {

  namespace Physics {
    
    ////////////////////// DYNAMIC BODY ///////////////////////
    DynamicBody::DynamicBody(const std::string& bodyID)
      : m_Friction(0.0f), m_Density(0.0f), m_Restitution(0.0f), m_DefDirection(BODY_DIRECTION::RIGHT), m_BodyID(bodyID)
    {
    }

    void DynamicBody::CreateBody(const b2Vec2& size, const b2Vec2& position) {
      // Create a new DynamicBodyData instance
      DynamicBodyData* dynamicBodyData = new DynamicBodyData();

      // Initialize size and position
      dynamicBodyData->Size = size;
      dynamicBodyData->Positions = position;

      // Calculate half body size
      b2Vec2 halfBodySize = b2Vec2(size.x * 0.5f, size.y * 0.5f);

      // Configure body definition
      dynamicBodyData->BodyDef.type = b2_dynamicBody;
      dynamicBodyData->BodyDef.position = dynamicBodyData->Positions;

      // Create body in physics world
      dynamicBodyData->Body = PhysicsModule::GetPhysicsWorld()->CreateBody(&dynamicBodyData->BodyDef);

      // Set shape as a box
      dynamicBodyData->Shape.SetAsBox(halfBodySize.x, halfBodySize.y);

      // Configure fixture definition
      dynamicBodyData->FixtureDef.shape = &dynamicBodyData->Shape;
      dynamicBodyData->FixtureDef.density = m_Density;
      dynamicBodyData->FixtureDef.friction = m_Friction;
      dynamicBodyData->FixtureDef.restitution = m_Restitution;

      // Create fixture
      dynamicBodyData->Body->CreateFixture(&dynamicBodyData->FixtureDef);

      dynamicBodyData->BodyID = m_BodyID;

      m_Current = dynamicBodyData;
      m_BodyData.push_back(dynamicBodyData);
    }

    void DynamicBody::RenderBody(const glm::vec4& color) {
      for(auto& body : m_BodyData)
      {
        b2Vec2 position = body->Body->GetPosition();
        b2Vec2 size = body->Size;

        body->RendShape->DrawQuad({ position.x, position.y }, { size.x, size.y }, color);
      }
    }

    void DynamicBody::MoveBody(const b2Vec2& force, BODY_DIRECTION direction)
    {
      m_Current->Body->SetAwake(true); // When body goes to sleep, moving the body causes some issues
      m_Current->Body->ApplyForce(force, m_Current->Body->GetWorldCenter(), m_Current->Body->IsAwake());

      if(direction == BODY_DIRECTION::NONE) 
        m_CurrentDirection = m_DefDirection;
      else
        m_CurrentDirection = direction;
    }

    DynamicBody::DynamicBodyData* DynamicBody::GetBodyData()
    {
      return m_Current;
    }

    DynamicBody::~DynamicBody()
    {
      m_Current->Body->SetAwake(false);
      for(auto& bodyData : m_BodyData) {
        delete bodyData;
        bodyData = nullptr;
      }
    }
    
    /////////////////////// STATIC BODY ////////////////////
    StaticBody::StaticBody(const std::string& bodyID)
      : m_BodyID(bodyID)
    {
    }

    void StaticBody::CreateBody(const b2Vec2& size, const b2Vec2& positions)
    {
      StaticBodyData* staticBodyData = new StaticBodyData();

      staticBodyData->Size = size;
      staticBodyData->Positions = positions;

      b2Vec2 halfBodySize = b2Vec2(size.x * 0.5f, size.y * 0.5f);

      staticBodyData->BodyDef.type = b2_staticBody;
      staticBodyData->BodyDef.position = staticBodyData->Positions;
      
      staticBodyData->Body = PhysicsModule::GetPhysicsWorld()->CreateBody(&staticBodyData->BodyDef);
      staticBodyData->Shape.SetAsBox(halfBodySize.x, halfBodySize.y, b2Vec2(0.0f, 0.0f), 0.0f);

      staticBodyData->Body->CreateFixture(&staticBodyData->Shape, 0.0f);
      
      m_Current = staticBodyData;

      m_Current->BodyID = m_BodyID;
      m_BodyData.push_back(staticBodyData); 
    }

    void StaticBody::RenderBody(const glm::vec4& color)
    {
      for(auto& body : m_BodyData)
      {
        b2Vec2 position = body->Body->GetPosition();
        b2Vec2 size = body->Size;

        body->RendShape->DrawQuad({ position.x, position.y }, { size.x, size.y }, color);
      }
    }

    StaticBody::~StaticBody()
    {
      for(auto& bodyData : m_BodyData)
        delete bodyData;
    }


  }

}
