#pragma once 
#include "Component.h"  

namespace dbf
{

	class Program;
	class CameraComponent : public Component
	{
	public:
		CLASS_DECLARATION(CameraComponent)

			//virtual void init() override;
		virtual void update() override;

		void SetPerspective(float fov, float aspectRatio, float near, float far);
		void SetProgram(std::shared_ptr<Program> prog);
		const glm::mat4& GetProjection() { return m_projection; }
		const glm::mat4& GetView() { return m_view; }
		virtual bool write(const rapidjson::Value& value) const override;
		virtual bool read(const rapidjson::Value& value) override;

	public:
		glm::mat4 m_projection{ 1 };
		glm::mat4 m_view{ 1 };
		int speed = 60;
	};
}