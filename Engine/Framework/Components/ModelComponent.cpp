#include "ModelComponent.h"
#include "Renderer/Material.h"
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
		m_material->Bind();
		// set model view projection matrix for model 
		m_material->GetProgram()->SetUniform("model", (glm::mat4)m_owner->m_transform);
		//m_material->GetProgram()->SetUniform("view", renderer.getView());
		//m_material->GetProgram()->SetUniform("projection", renderer.getProjection());
		glDepthMask(depth_test);
		m_model->m_vertexBuffer.Draw();
	}
	bool ModelComponent::write(const rapidjson::Value& value) const
	{
		return true;
	}
	bool ModelComponent::read(const rapidjson::Value& value)
	{
		std::string model_name;
		READ_DATA(value, model_name);

		std::string material_name;
		READ_DATA(value, material_name);

		m_model = g_resourceManager.Get<Model>(model_name);
		m_material = g_resourceManager.Get<Material>(material_name);

		return true;
	}
}
