#include "PhysicsBody.h"

namespace Freeze {

  namespace Physics {
    
    ////////////////////// DYNAMIC BODY ///////////////////////
    DynamicBody::DynamicBody()
      :m_Friction(0.0f), m_Density(0.0f), m_Restitution(0.0f)
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

        // Add new body data to the linked list
        if (!m_Head) {
            m_Head = dynamicBodyData;
        } else {
            // Find the last node and append dynamicBodyData
            DynamicBodyData* current = m_Head;
            while (current->next)
                current = current->next;
            current->next = dynamicBodyData;
        }
    }


    void DynamicBody::RenderBody(const glm::vec4& color) {
      DynamicBodyData* current = m_Head;
      while (current) {
          // Access position and size from DynamicBodyData and render the body
          b2Vec2 position = current->Body->GetPosition();
          b2Vec2 size = current->Size;
          Renderer2D::DrawQuad({ position.x, position.y }, { size.x, size.y }, color);
          
          // Move to the next node in the linked list
          current = current->next;
      }
    }

    void DynamicBody::DeleteBody()
    {
      
    }

    DynamicBody::~DynamicBody()
    {
      DynamicBodyData* current = m_Head;
        while (current) {
            DynamicBodyData* next = current->next;
            delete current;
            current = next;
        }
    }
    

    /////////////////////// STATIC BODY ////////////////////
    StaticBody::StaticBody()
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

       // Add new body data to the linked list
        if (!m_Head) {
            m_Head = staticBodyData;
        } else {
            // Find the last node and append staticBodyData
            StaticBodyData* current = m_Head;
            while (current->next)
                current = current->next;
            current->next = staticBodyData;
        }

    }

    void StaticBody::RenderBody(const glm::vec4& color)
    {
      StaticBodyData* current = m_Head;
      while (current) {
          // Access position and size from StaticBodyData and render the body
          b2Vec2 position = current->Body->GetPosition();
          b2Vec2 size = current->Size;
          Renderer2D::DrawQuad({ position.x, position.y }, { size.x, size.y }, color);
          
          // Move to the next node in the linked list
          current = current->next;
      }
    }

    void StaticBody::DeleteBody()
    {
    }

    StaticBody::~StaticBody()
    {
      StaticBodyData* current = m_Head;
        while (current) {
            StaticBodyData* next = current->next;
            delete current;
            current = next;
        }
    }


  }

}