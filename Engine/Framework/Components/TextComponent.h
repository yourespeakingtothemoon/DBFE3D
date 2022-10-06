#pragma once 
#include "RenderComponent.h" 
#include "Math/Color.h" 
#include "Math/Vector2.h" 
#include <memory> 

namespace dbf
{
	class Font;
	class Texture;

	class TextComponent : public RenderComponent
	{
	public:
		CLASS_DECLARATION(TextComponent)

		virtual void update() override;
		virtual void draw(Renderer& renderer) override;

		void setText(const std::string& text);

		virtual bool write(const rapidjson::Value& value) const override;
		virtual bool read(const rapidjson::Value& value) override;

	public:
		std::string text;
		std::string fontName;
		int size;
		Vector2 registration;
		Color color;

		std::shared_ptr<Font> m_font;
		std::shared_ptr<Texture> m_texture;
	};
}