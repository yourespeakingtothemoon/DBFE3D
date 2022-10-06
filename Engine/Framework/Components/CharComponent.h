#pragma once
#pragma once
#include "Component.h"
#include "Physics/Collision.h"
#include "Framework/EventSystem/Event.h"

namespace dbf
{
	class CharComponent : public Component, public ICollision, public INotify
	{
	public:
		CharComponent() = default;
		virtual ~CharComponent();

		virtual void init() override;

		

		virtual bool write(const rapidjson::Value& value) const override;
		virtual bool read(const rapidjson::Value& value) override;

	public:
		float health = 100;
		float damage = 10;
		float speed = 70;
	};
}