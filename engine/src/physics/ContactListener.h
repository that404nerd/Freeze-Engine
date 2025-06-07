#pragma once

#include "box2d/box2d.h"
#include "core/Entity.h"

#include "core/Core.h"

namespace Freeze {
  
  class ContactListener : public b2ContactListener {
  public:
    
    void BeginContact(b2Contact* contact) override
    {
      auto* bodyA = contact->GetFixtureA()->GetBody();
      auto* bodyB = contact->GetFixtureB()->GetBody();

      PhysicsBodyData* dataA;
      PhysicsBodyData* dataB;
    
      if(bodyA != nullptr && bodyB != nullptr)
      {
        dataA = reinterpret_cast<PhysicsBodyData*>(bodyA->GetUserData().pointer);
        dataB = reinterpret_cast<PhysicsBodyData*>(bodyB->GetUserData().pointer);
      } else { assert(false && "Invalid body data!"); }

      if (dataA)
      {
        dataA->isCollided = true;
        dataA->CollidedWith = dataB->Body;
      }

      if (dataB)
      {
        dataB->isCollided = true;
        dataB->CollidedWith = dataA->Body;
      }

      // FZ_INFO("Contact begin");
      
    }

    void EndContact(b2Contact* contact) override
    {
      auto* bodyA = contact->GetFixtureA()->GetBody();
      auto* bodyB = contact->GetFixtureB()->GetBody();

      PhysicsBodyData* dataA;
      PhysicsBodyData* dataB;
    
      if(bodyA != nullptr && bodyB != nullptr)
      {
        dataA = reinterpret_cast<PhysicsBodyData*>(bodyA->GetUserData().pointer);
        dataB = reinterpret_cast<PhysicsBodyData*>(bodyB->GetUserData().pointer);
      } else { assert(false && "Invalid body data!"); }

      if (dataA)
      {
        dataA->isCollided = false;
        dataA->CollidedWith = nullptr;
      }

      if (dataB)
      {
        dataB->isCollided = false;
        dataB->CollidedWith = nullptr;
      }

      // FZ_INFO("Contact end");
    }

    
  };

};
