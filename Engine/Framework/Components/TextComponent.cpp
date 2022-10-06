#include "TextComponent.h" 
#include "Engine.h" 

namespace dbf
{
	void TextComponent::update()
	{
	}

	void TextComponent::draw(Renderer& renderer)
	{
		g_renderer.draw(m_texture, m_owner->m_transform, registration);
	}

	void TextComponent::setText(const std::string& text)
	{
		
		m_texture->CreateFromSurface(m_font->CreateSurface(text, color), g_renderer);

		
	}

	bool TextComponent::write(const rapidjson::Value& value) const
	{
		return true;
	}

	bool TextComponent::read(const rapidjson::Value& value)
	{
		READ_DATA(value, text);
		READ_DATA(value, fontName);
		READ_DATA(value, size);
		READ_DATA(value, registration);
		READ_DATA(value, color);

		m_font = g_resourceManager.Get<Font>(fontName, size);
		m_texture = std::make_unique<Texture>();

		setText(text);

		return true;
	}
}