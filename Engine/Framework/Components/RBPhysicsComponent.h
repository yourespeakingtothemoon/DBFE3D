#pragma once
#include "PhysicsComponent.h"
#include "Physics/PhysicsSystem.h"

namespace dbf
{
	class RBPhysicsComponent : public PhysicsComponent
	{
	public:
		RBPhysicsComponent() = default;
		~RBPhysicsComponent();

		CLASS_DECLARATION(RBPhysicsComponent)

		void init() override;
		void update() override;
		virtual void applyForce(const Vector2& force);

		// Inherited via PhysicsComponent
		virtual bool write(const rapidjson::Value& value) const override;
		virtual bool read(const rapidjson::Value& value) override;

		friend class CollisionComponent;
	private:
		PhysicsSystem::RigidBodyData data;
		b2Body* m_body = nullptr;

	};
}