#include "PhysicsBody.h"

namespace Freeze {

  namespace Physics {
    
   // Static members initialisation
   std::vector<DynamicBody::DynamicBodyData*> DynamicBody::m_DynamicBodies;
   std::vector<StaticBody::StaticBodyData*> StaticBody::m_StaticBodies;

    ////////////////////// DYNAMIC BODY ///////////////////////
    DynamicBody::DynamicBody()
      :m_Friction(0.0f), m_Density(0.0f), m_Restitution(0.0f)
    {
      m_BodyData = new DynamicBodyData();
    }

    void DynamicBody::CreateBody(const b2Vec2& size, const b2Vec2& positions)
    {
      m_BodyData->Size = b2Vec2(size.x, size.y);
      b2Vec2 halfBodySize = b2Vec2(m_BodyData->Size.x * 0.5f, m_BodyData->Size.y * 0.5f);
      m_BodyData->Positions = b2Vec2(positions.x, positions.y);
      
      m_BodyData->BodyDef.type = b2_dynamicBody;
      m_BodyData->BodyDef.position = PixelToMeter(m_BodyData->Positions);
      
      m_BodyData->Body = PhysicsModule::GetPhysicsWorld()->CreateBody(&m_BodyData->BodyDef);
      
      m_BodyData->Shape.SetAsBox(PixelToMeter(halfBodySize.x), PixelToMeter(halfBodySize.y));

      m_BodyData->FixtureDef.shape = &m_BodyData->Shape;

      m_BodyData->FixtureDef.density = m_Density;
      m_BodyData->FixtureDef.friction = m_Friction;
      m_BodyData->FixtureDef.restitution = m_Restitution;
      
      m_BodyData->Body->CreateFixture(&m_BodyData->FixtureDef);
       
      m_DynamicBodies.push_back(m_BodyData);
    }

    void DynamicBody::RenderBody(const glm::vec4& color)
    {
      for(auto& dynBody : m_DynamicBodies)
      {
        Renderer2D::DrawQuad({ dynBody->Body->GetPosition().x, dynBody->Body->GetPosition().y }, { 0.2f, 0.2f }, color);
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
      :m_BodyData(new StaticBodyData())
    {
    }

    void StaticBody::CreateBody(const b2Vec2& size, const b2Vec2& positions)
    {
      
       m_Size = b2Vec2(size.x, size.y);
       b2Vec2 halfBodySize = b2Vec2(m_Size.x * 0.5f, m_Size.y * 0.5f);
       m_Positions = b2Vec2(positions.x, positions.y);
       
      //  m_BodyData->m_Quad = std::make_shared<FreezeQuad>();  
      //  m_BodyData->m_Quad->CreateQuad(size.x, size.y, "", "");

       m_BodyData->BodyDef.type = b2_staticBody;
       m_BodyData->BodyDef.position = PixelToMeter(m_Positions);
      
       m_BodyData->Body = PhysicsModule::GetPhysicsWorld()->CreateBody(&m_BodyData->BodyDef);
       m_BodyData->Shape.SetAsBox(PixelToMeter(halfBodySize.x), PixelToMeter(halfBodySize.y), PixelToMeter(b2Vec2(0.0f, 0.0f)), 0.0f);

       m_BodyData->Body->CreateFixture(&m_BodyData->Shape, 0.0f);

       m_StaticBodies.push_back(m_BodyData);
    }

    void StaticBody::RenderBody(const glm::vec4& color)
    {
    }

    void StaticBody::DeleteBody()
    {
    }

    StaticBody::~StaticBody()
    {
      delete m_BodyData;
      m_StaticBodies.clear();
    }


  }

}
