#pragma once
#include "Component.h"
#include "Physics/Collision.h"
#include "CharComponent.h"

namespace dbf
{
	class PlayComponent : public CharComponent
	{
	public:
		PlayComponent() = default;

		CLASS_DECLARATION(PlayComponent)

		void init() override;
		void update() override;
		//event
		virtual void OnNotify(const Event& event);
		//collision
		virtual void enterCollide(Actor* other) override;
		virtual void exitCollide(Actor* other) override;
		float queryHealth() { return health; }
		void attack(bool form=0);
		//serialization
		virtual bool write(const rapidjson::Value& value) const override;
		virtual bool read(const rapidjson::Value& value) override;

	public:
		float jump = 0;
		int m_groundCount = 0;
		int m_jumpCount = 0;
		int pyMagicka = 0;
		int atkOutput=0;


	};
}