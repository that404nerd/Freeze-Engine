#include "PhysicsBody.h"

namespace Freeze {

  namespace Physics {
    
   // Static members initialisation
   std::vector<b2Body*> StaticBody::m_StaticBodies;

    ////////////////////// DYNAMIC BODY ///////////////////////
    DynamicBody::DynamicBody()
      :m_Friction(0.0f), m_Density(0.0f), m_Restitution(0.0f)
    {
    }

    void DynamicBody::CreateBody(const b2Vec2& size, const b2Vec2& position) {
        // Create a new DynamicBodyData instance
        DynamicBodyData* newBodyData = new DynamicBodyData();

        // Initialize size and position
        newBodyData->Size = size;
        newBodyData->Positions = position;

        // Calculate half body size
        b2Vec2 halfBodySize = b2Vec2(size.x * 0.5f, size.y * 0.5f);

        // Configure body definition
        newBodyData->BodyDef.type = b2_dynamicBody;
        newBodyData->BodyDef.position = position;

        // Create body in physics world
        newBodyData->Body = PhysicsModule::GetPhysicsWorld()->CreateBody(&newBodyData->BodyDef);

        // Set shape as a box
        newBodyData->Shape.SetAsBox(halfBodySize.x, halfBodySize.y);

        // Configure fixture definition
        newBodyData->FixtureDef.shape = &newBodyData->Shape;
        newBodyData->FixtureDef.density = m_Density;
        newBodyData->FixtureDef.friction = m_Friction;
        newBodyData->FixtureDef.restitution = m_Restitution;

        // Create fixture
        newBodyData->Body->CreateFixture(&newBodyData->FixtureDef);

        // Add new body data to the linked list
        if (!m_Head) {
            m_Head = newBodyData;
        } else {
            // Find the last node and append newBodyData
            DynamicBodyData* current = m_Head;
            while (current->next)
                current = current->next;
            current->next = newBodyData;
        }
    }


    void DynamicBody::RenderBody(const glm::vec4& color) {
      DynamicBodyData* current = m_Head;
      while (current) {
          // Access position and size from DynamicBodyData and render the body
          b2Vec2 position = current->Body->GetPosition();
          b2Vec2 size = current->Size;
          Freeze::Renderer2D::DrawQuad({ position.x, position.y }, { size.x, size.y }, color);
          
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
       m_StaticBodyData = new StaticBodyData();
       m_StaticBodyData->Size = b2Vec2(size.x, size.y);
       b2Vec2 halfBodySize = b2Vec2(m_StaticBodyData->Size.x * 0.5f, m_StaticBodyData->Size.y * 0.5f);
       m_StaticBodyData->Positions = b2Vec2(positions.x, positions.y);

       m_StaticBodyData->BodyDef.type = b2_staticBody;
       m_StaticBodyData->BodyDef.position = m_StaticBodyData->Positions;
      
       m_StaticBodyData->Body = PhysicsModule::GetPhysicsWorld()->CreateBody(&m_StaticBodyData->BodyDef);
       m_StaticBodyData->Shape.SetAsBox(halfBodySize.x, halfBodySize.y, b2Vec2(0.0f, 0.0f), 0.0f);

       m_StaticBodyData->Body->CreateFixture(&m_StaticBodyData->Shape, 0.0f);

       m_StaticBodies.push_back(m_StaticBodyData->Body);
    }

    void StaticBody::RenderBody(const glm::vec4& color)
    {
        for(auto& staticBody : m_StaticBodies)
        {
            Freeze::Renderer2D::DrawQuad({ staticBody->GetPosition().x, staticBody->GetPosition().y }, 
                                            { m_StaticBodyData->Size.x, m_StaticBodyData->Size.y }, color);
        } 
    }

    void StaticBody::DeleteBody()
    {
    }

    StaticBody::~StaticBody()
    {
      delete m_StaticBodyData;
    }


  }

}