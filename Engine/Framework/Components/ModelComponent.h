#pragma once
#include "RenderComponent.h"

namespace dbf
{
	class Model;

	class ModelComponent : public RenderComponent
	{
	public:
		ModelComponent() = default;

		CLASS_DECLARATION(ModelComponent)

		// Inherited via RenderComponent
		virtual void update() override;
		virtual void draw(Renderer& renderer) override;

		// Inherited via RenderComponent
		virtual bool write(const rapidjson::Value& value) const override;
		virtual bool read(const rapidjson::Value& value) override;
		//to model for modelComponent
	public:
		std::shared_ptr<Model> m_model;
		
	};
}
