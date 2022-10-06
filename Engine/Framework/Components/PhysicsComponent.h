#pragma once
#include "Component.h"
#include "Math//Vector2.h"

namespace dbf
{
	class PhysicsComponent : public Component
	{
	public:
		PhysicsComponent() = default;

		CLASS_DECLARATION(PhysicsComponent)

		void update() override;
		virtual void applyForce(const Vector2& force) { acceleration += force; }

		// Inherited via Component
		virtual bool write(const rapidjson::Value& value) const override;
		virtual bool read(const rapidjson::Value& value) override;

	public:
		Vector2 velocity;
		Vector2 acceleration;

		float damping = 0.9f;

		
	};
}