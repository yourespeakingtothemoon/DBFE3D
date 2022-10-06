#pragma once
#include "RenderComponent.h"
#include "Math/Rectangle.h"

namespace dbf
{
	class Texture;

	class SpriteComponent : public RenderComponent
	{
	public:
		CLASS_DECLARATION(SpriteComponent)

		// Inherited via RenderComponent
		virtual void update() override;
		virtual void draw(Renderer& renderer) override;

		// Inherited via RenderComponent
		virtual bool write(const rapidjson::Value& value) const override;
		virtual bool read(const rapidjson::Value& value) override;

	public:
		//Rectangle source;
		std::shared_ptr<Texture> m_texture;
	};
}