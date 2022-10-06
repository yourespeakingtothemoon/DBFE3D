#pragma once
#include "Serialization/Serializable.h"
#include <memory>

#define CLASS_DECLARATION(class) \
	std::unique_ptr<GameObject> Clone() override { return std::make_unique<class>(*this); }

#define REGISTER_CLASS(class) Factory::instance().reg<class>(#class)
namespace dbf
{
	class GameObject
	{
	public:
		GameObject() = default;
		
		virtual std::unique_ptr <GameObject> Clone()=0;
		virtual void init() = 0;
		virtual void update() = 0;
	};
}


