#pragma once
#include "Framework/GameObject.h"


namespace dbf 
{
	class Actor;
	class Component : public GameObject, public ISerializable
	{
	public:
		Component() = default;

		virtual void init() override {}
		virtual void update() = 0;

		friend class Actor;

	protected:
		Actor* m_owner = nullptr;

	};
}