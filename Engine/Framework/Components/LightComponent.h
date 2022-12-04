#pragma once
#include "Component.h"

namespace dbf
{
	class Program;
	class LightComponent : public Component
	{
	public:
		CLASS_DECLARATION(LightComponent)

		void update() override;

		virtual bool write(const rapidjson::Value& value) const override;
		virtual bool read(const rapidjson::Value& value) override;

		void setProgram(std::shared_ptr<Program> program, int index);
	public:

		enum class Type
		{
			Point, Directional, Spot
		};

	public:
		glm::vec3 color{ 0 };
		Type type = Type::Point;
		float cutoff=45.0f;
		float exponent = 50.0f;
	};
}