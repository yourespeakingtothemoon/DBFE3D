#include "PhysicsComponent.h"
#include "Engine.h"

namespace dbf 
{
	void PhysicsComponent::update()
	{
		velocity += acceleration * dbf::g_time.deltaTime;
		m_owner->m_transform.position += velocity * dbf::g_time.deltaTime;
		velocity *= damping;

		acceleration = Vector2::zero;
	}

	bool PhysicsComponent::write(const rapidjson::Value& value) const
	{
		return false;
	}

	bool PhysicsComponent::read(const rapidjson::Value& value)
	{
		READ_DATA(value, damping);
		READ_DATA(value, velocity);
		READ_DATA(value, acceleration);

		return true;
	}

}
