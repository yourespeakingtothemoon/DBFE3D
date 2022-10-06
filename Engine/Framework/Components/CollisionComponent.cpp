#include "CollisionComponent.h"
#include"Engine.h"
#include <iostream>

namespace dbf
{
    void CollisionComponent::init()
    {
      
        auto component = m_owner->getComponent<RBPhysicsComponent>();
        if (component)
        {
            if (data.size.x == 0 && data.size.y == 0)
            {
                auto renderComponent = m_owner->getComponent<RenderComponent>();
                if (renderComponent)
                {
                    data.size = { renderComponent->GetSource().w, renderComponent->GetSource().h };
                }
            }

            data.size = data.size * scale_offset * m_owner->m_transform.scale; // <-----

            if (component->m_body->GetType() == b2_staticBody)
            {
                g_physicsSystem.setCollisionBoxStatic(component->m_body, data, m_owner);
            }
            else
            {
                g_physicsSystem.setCollisionBox(component->m_body, data, m_owner);
            }
        }
    }

    void CollisionComponent::update()
    {
      
    }

    void CollisionComponent::enterCollide(Actor* other)
    {
        std::cout << other->getName() << std::endl;
        if (m_enterFunction) m_enterFunction(other);
    }

    void CollisionComponent::exitCollide(Actor* other)
    {
        std::cout << other->getName() << std::endl;
        if(m_exitFunction) m_exitFunction(other);
    }

    bool CollisionComponent::write(const rapidjson::Value& value) const
    {
        return true;
    }

    bool CollisionComponent::read(const rapidjson::Value& value)
    {
        READ_DATA(value, data.size);
        READ_DATA(value, data.density);
        READ_DATA(value, data.friction);
        READ_DATA(value, data.restitution);
        READ_DATA(value, data.is_trigger);
        READ_DATA(value, scale_offset);

        return true;
    }
}
