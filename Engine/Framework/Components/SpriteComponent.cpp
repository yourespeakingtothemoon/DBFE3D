#include "SpriteComponent.h"
#include "Renderer/Renderer.h"
#include "Framework/Actor.h"
#include "Engine.h"
namespace dbf
{
	void SpriteComponent::update()
	{
	}
	void SpriteComponent::draw(Renderer& renderer)
	{
		renderer.draw(m_texture, GetSource(), m_owner->m_transform, regi, flipHoriz);
	}

	bool SpriteComponent::write(const rapidjson::Value& value) const
	{
		return true;
	}
	
	bool SpriteComponent::read(const rapidjson::Value& value)
	{
		std::string texture_name;
		READ_DATA(value, texture_name);

		m_texture = g_resourceManager.Get<Texture>(texture_name, g_renderer);

		if (!READ_DATA(value, source))
		{
			source.x = 0;
			source.y = 0;
			source.w = (int)m_texture->GetSize().x;
			source.h = (int)m_texture->GetSize().y;
		}

		return true;
	}
}