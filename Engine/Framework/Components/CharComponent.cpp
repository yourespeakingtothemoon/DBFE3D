#include "CharComponent.h"
#include "Engine.h"

namespace dbf
{
	CharComponent::~CharComponent()
	{
		g_eventManager.unsubscribe("EVENT_DAMAGE", m_owner);
	}

	void CharComponent::init()
	{
		// bind events
		g_eventManager.subscribe("EVENT_DAMAGE", std::bind(&CharComponent::OnNotify, this, std::placeholders::_1), m_owner);

		// bind collision events
		auto component = m_owner->getComponent<CollisionComponent>();
		if (component)
		{
			component->setCollideEnter(std::bind(&CharComponent::enterCollide, this, std::placeholders::_1));
			component->setCollideExit(std::bind(&CharComponent::exitCollide, this, std::placeholders::_1));
		}
	}

	bool CharComponent::write(const rapidjson::Value& value) const
	{
		return true;
	}

	bool CharComponent::read(const rapidjson::Value& value)
	{
		READ_DATA(value, health);
		READ_DATA(value, damage);
		READ_DATA(value, speed);

		return true;
	}
}