#pragma once
#include "Component.h"
#include "Physics/Collision.h"
#include "Physics/PhysicsSystem.H"
#include <functional>

namespace dbf
{
	class CollisionComponent : public Component, public ICollision
	{
	public:
		using functionPtr = std::function<void(Actor*)>;

	public:
		virtual void init() override;
		virtual void update() override;

		CLASS_DECLARATION(CollisionComponent)

		// Inherited via ICollision
		virtual void enterCollide(Actor* other) override;
		virtual void exitCollide(Actor* other) override;

		void setCollideEnter(functionPtr function) { m_enterFunction = function; }
		void setCollideExit(functionPtr function) { m_exitFunction = function; }

		// Inherited via Component
		virtual bool write(const rapidjson::Value& value) const override;
		virtual bool read(const rapidjson::Value& value) override;

		Vector2 scale_offset = { 1, 1 };
	private:
		PhysicsSystem::CollisionData data;
		functionPtr m_enterFunction;
		functionPtr m_exitFunction;
		

	};
}