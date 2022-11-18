
#include "LightComponent.h"
#include "Engine.h"


namespace dbf
{
	void LightComponent::update()
	{
		// transform the light position by the view, puts light in model view space
		glm::vec4 position = g_renderer.getView() * glm::vec4(m_owner->m_transform.position, 1);

		// get all programs in the resource system
		auto programs = g_resourceManager.Get<Program>();
		// set programs light properties
		for (auto& program : programs)
		{
			program->SetUniform("light.ambient", ambient);
			program->SetUniform("light.diffuse", diffuse);
			program->SetUniform("light.specular", specular);
			program->SetUniform("light.position", position);
		}
	}

	bool LightComponent::write(const rapidjson::Value& value) const
	{
		return true;
	}

	bool LightComponent::read(const rapidjson::Value& value)
	{
		READ_DATA(value, ambient);
		READ_DATA(value, diffuse);
		READ_DATA(value, specular);
		READ_DATA(value, cutoff);
		READ_DATA(value, exponent);


		std::string type_name;
		READ_DATA(value, type_name);
		if (compareIgnoreCase(type_name, "directional"))
		{
			type = Type::Directional;
		}
		else if (compareIgnoreCase(type_name, "spot"))
		{
			type = Type::Spot;
		}
		else
		{
			type = Type::Point;
		}

		return true;
	}

}