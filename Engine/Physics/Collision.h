#pragma once

namespace dbf
{
	class Actor;

	class ICollision
	{
	public:
		virtual void enterCollide(Actor* other) = 0;
		virtual void exitCollide(Actor* other) = 0;
	};
}