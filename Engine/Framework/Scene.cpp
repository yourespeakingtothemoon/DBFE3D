#include "Scene.h"
#include "Factory.h"
#include "Engine.h"
#include <algorithm>
#include <iostream>

namespace dbf
{
	void Scene::init()
	{
		for (auto& actor : m_actors) { actor->init(); }
	}

	void Scene::update()
	{
		auto iter = m_actors.begin();
		while (iter != m_actors.end())
		{
			(*iter)->update();
			if ((*iter)->m_destroy)
			{
				iter = m_actors.erase(iter);
			}
			else
			{
				iter++;
			}
		}
	}

	void Scene::preRender(Renderer& renderer)
	{
		// get active camera component 
		CameraComponent* camera = nullptr;
		for (auto& actor : m_actors)
		{
			//< if actor is active is false, continue; (skips rest of for code) >
			if (!actor->queryActive())
			{
				continue;
			}
			auto component = actor->getComponent<CameraComponent>();
			if (component != nullptr)
			{
				camera = component; //<set camera to component>
				break; //<break out of for loop>
			}
		}

		// get light components 
		std::vector<LightComponent*> lights;
		for (auto& actor : m_actors)
		{
			//< if actor is active is false, continue; (skips rest of for code) >
			if (!actor->queryActive()) continue;

			auto component = actor->getComponent<LightComponent>();
			if (component != nullptr)//<component not null>
			{
				lights.push_back(component); //<add(push back) component to lights vector>
			}
		}

		// get all shader programs in the resource system 
		auto programs = g_resourceManager.Get<Program>();
		// set all shader programs camera and lights uniforms 
		for (auto& program : programs)
		{
			// set camera in shader program 
			camera->SetProgram(program);

			// set lights in shader program 
			int index = 0;
			for (auto light : lights)
			{
				light->setProgram(program, index++);
			}

			program->SetUniform("light_count", index);
			program->SetUniform("ambient_color", g_renderer.ambient_color);
		}
	}

	void Scene::render(Renderer& renderer)
	{
		// get camera / set renderer view/projection 
		auto camera = getActorByName("Camera");
		if (camera)
		{
			g_renderer.setView(camera->getComponent<CameraComponent>()->GetView());
			g_renderer.setProjection(camera->getComponent<CameraComponent>()->GetProjection());
		}

		// draw actors 
		for (auto& actor : m_actors)
		{
			actor->draw(renderer);
		}
	}

	void Scene::Add(std::unique_ptr<Actor> actor)
	{
		actor->m_scene = this;
		m_actors.push_back(std::move(actor));
	}

	void Scene::RemoveAll()
	{
		for (auto& actor : m_actors) { actor->flipDestroy(); }

		m_actors.clear();
	}

	bool Scene::Create(std::string name, ...)
	{
		rapidjson::Document document;
		bool success = dbf::json::Load(name, document);
		if (!success)
		{
			LOG("error loading scene file %s.", name.c_str());
		}

		read(document);
		init();
		LOG("Scene Initialized...");
		return true;
	}

	bool Scene::write(const rapidjson::Value& value) const
	{
		return true;
	}

	bool Scene::read(const rapidjson::Value& value)
	{
		// read clear color 
		READ_NAME_DATA(value, "clear_color", g_renderer.clear_color);
		READ_NAME_DATA(value, "ambient_color", g_renderer.ambient_color);

		if (!value.HasMember("actors") || !value["actors"].IsArray())
		{
			return false;
		}

		// read actors
		for (auto& actorValue : value["actors"].GetArray())
		{
			std::string type;
			READ_DATA(actorValue, type);

			auto actor = Factory::instance().Create<Actor>(type);
			if (actor)
			{
				// read actor
				actor->read(actorValue);

				bool prefab = false;
				READ_DATA(actorValue, prefab);

				if (prefab)
				{
					std::string name = actor->getName();
					Factory::instance().regPrefab(name, std::move(actor));
				}
				else
				{
					Add(std::move(actor));
				}
			}
		}

		return true;

	}
}
