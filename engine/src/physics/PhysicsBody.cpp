#include "PhysicsBody.h"

namespace Freeze {

  namespace Physics {
    
   // Static members initialisation
   std::vector<b2Body*> DynamicBody::m_DynamicBodies;
   std::vector<b2Body*> StaticBody::m_StaticBodies;

    ////////////////////// DYNAMIC BODY ///////////////////////
    DynamicBody::DynamicBody()
      :m_Friction(0.0f), m_Density(0.0f), m_Restitution(0.0f)
    {
    }

    void DynamicBody::CreateBody(const b2Vec2& size, const b2Vec2& positions)
    {
      m_DynamicBodyData = new DynamicBodyData();
      m_DynamicBodyData->Size = b2Vec2(size.x, size.y);
      b2Vec2 halfBodySize = b2Vec2(m_DynamicBodyData->Size.x * 0.5f, m_DynamicBodyData->Size.y * 0.5f);
      m_DynamicBodyData->Positions = b2Vec2(positions.x, positions.y);
      
      m_DynamicBodyData->BodyDef.type = b2_dynamicBody;
      m_DynamicBodyData->BodyDef.position = m_DynamicBodyData->Positions;
      
      m_DynamicBodyData->Body = PhysicsModule::GetPhysicsWorld()->CreateBody(&m_DynamicBodyData->BodyDef);
      
      m_DynamicBodyData->Shape.SetAsBox(halfBodySize.x, halfBodySize.y);

      m_DynamicBodyData->FixtureDef.shape = &m_DynamicBodyData->Shape;

      m_DynamicBodyData->FixtureDef.density = m_Density;
      m_DynamicBodyData->FixtureDef.friction = m_Friction;
      m_DynamicBodyData->FixtureDef.restitution = m_Restitution;
      
      m_DynamicBodyData->Body->CreateFixture(&m_DynamicBodyData->FixtureDef);
       
      m_DynamicBodies.push_back(m_DynamicBodyData->Body);
    }

    void DynamicBody::RenderBody(const glm::vec4& color)
    {
      for(auto& dynBody : m_DynamicBodies)
      {
        FZ_INFO("Box2D positions: {}, {}", dynBody->GetPosition().x, dynBody->GetPosition().y);
        FZ_INFO("Rendered positions: {}, {}", dynBody->GetPosition().x, dynBody->GetPosition().y);
        Freeze::Renderer2D::DrawQuad({ dynBody->GetPosition().x, dynBody->GetPosition().y }, { m_DynamicBodyData->Size.x, m_DynamicBodyData->Size.y }, color);
      } 
    }

    void DynamicBody::DeleteBody()
    {
      
    }

    DynamicBody::~DynamicBody()
    {
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