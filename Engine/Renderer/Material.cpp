#include "Material.h" 
#include "Engine.h" 

namespace dbf
{
	bool Material::Create(std::string filename, ...)
	{
		// load program json document 
		rapidjson::Document document;
		bool success = dbf::json::Load(filename, document);
		if (!success)
		{

			LOG("Could not load program file (%s).", filename.c_str());
			return false;
		}

		// read the program name 
		std::string program;
		READ_DATA(document, program);
		// get program resource 
		m_program = dbf::g_resourceManager.Get<dbf::Program>(program);

		// read cube map
		std::string cubemap;
		READ_DATA(document, cubemap);
		if (!cubemap.empty())
		{
			std::string cubemap_extension;
			READ_DATA(document, cubemap_extension);
			m_textures.push_back(dbf::g_resourceManager.Get<dbf::CubemapTexture>(cubemap, cubemap_extension));
		}

		// read the texture name 
		std::string texture;
		READ_DATA(document, texture);
		if (!texture.empty())
		{
			// get texture resource 

			m_textures.push_back(dbf::g_resourceManager.Get<dbf::Texture>(texture));
		}

		// read colors 
		READ_DATA(document, color);
		READ_DATA(document, shininess);
		READ_DATA(document, uv_tiling);
		READ_DATA(document, uv_offset);

		return true;
	}

	void Material::Bind()
	{
		m_program->Use();
		m_program->SetUniform("material.color", color);
		m_program->SetUniform("material.shininess", shininess);
		m_program->SetUniform("material.uv_tiling", uv_tiling);
		m_program->SetUniform("material.uv_offset", uv_offset);

		for (size_t i = 0; i < m_textures.size(); i++)
		{
			m_textures[i]->setActive(GL_TEXTURE0 + (int)i);
			m_textures[i]->bind();
		}
	}
}
