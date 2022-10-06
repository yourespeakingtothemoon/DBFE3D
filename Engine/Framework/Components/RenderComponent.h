#pragma once
#include "Component.h"
#include "Math/Rectangle.h"
#include "Math/Vector2.h"


namespace dbf
{
	class Renderer;

	class RenderComponent : public Component
	{
	public:
		virtual void draw(Renderer& renderer) = 0;

		virtual Rectangle& GetSource() { return source; }

		void setFlipHoriz(bool flip = true) { flipHoriz = flip; }
		bool getFlipHoriz() { return flipHoriz; }

	protected:
		Rectangle source;
		bool flipHoriz = false;
		Vector2 regi= Vector2{.5f,.5f};
	};
}