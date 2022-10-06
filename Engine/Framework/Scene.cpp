#include "Scene.h"
#include <algorithm>

namespace dbf 
{
	Scene::Scene(const Scene& other)
	{

	}
	void Scene::init()
	{
		for (auto& actor : m_actors)
		{
			actor->init();
		}
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

	void Scene::draw(Renderer& renderer)
	{
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
	bool Scene::write(const rapidjson::Value& value) const
	{
		return true;
	}
	bool Scene::read(const rapidjson::Value& value)
	{
		if (!value.HasMember("actors") || !value["actors"].IsArray())
		{
			return false;
		}

		//get actors
		for (auto& actorValue : value["actors"].GetArray())
		{
			std::string type;
			READ_DATA(actorValue, type); //macro
			//dbf::json::Get(actorValue, "type", type); //No macro

			auto actor = Factory::instance().Create<dbf::Actor>(type);
			
			if (actor)
			{
				//read actor
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

	void Scene::RemoveAll()
	{
		m_actors.clear();
	}
}
