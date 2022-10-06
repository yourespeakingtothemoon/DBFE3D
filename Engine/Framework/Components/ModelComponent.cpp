#include "ModelComponent.h"
#include "Renderer/Model.h"
#include "Framework/Actor.h"
#include "Engine.h"

namespace dbf 
{
	void ModelComponent::update()
	{
		//
	}
	void ModelComponent::draw(Renderer& renderer)
	{
		m_model->draw(renderer, m_owner->m_transform);
	}
	bool ModelComponent::write(const rapidjson::Value& value) const
	{
		return true;
	}
	bool ModelComponent::read(const rapidjson::Value& value)
	{
		std::string model_name;
		READ_DATA(value, model_name);

		m_model = g_resourceManager.Get<Model>(model_name);

		return true;
	}
}
