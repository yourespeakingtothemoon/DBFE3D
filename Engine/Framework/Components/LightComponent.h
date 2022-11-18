#pragma once
#include "Component.h"

namespace dbf
{
	class LightComponent : public Component
	{
	public:
		CLASS_DECLARATION(LightComponent)

		void update() override;

		virtual bool write(const rapidjson::Value& value) const override;
		virtual bool read(const rapidjson::Value& value) override;

		enum class Type
		{
			Point, Directional, Spot
		};

	public:
		glm::vec3 ambient{ 0 };
		glm::vec3 diffuse{ 1 };
		glm::vec3 specular{ 1 };
		Type type = Type::Point;
		float cutoff=45.0f;
		float exponent = 50.0f;
	};
}