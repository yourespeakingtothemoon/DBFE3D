#pragma once
#include "Actor.h"
#include "Factory.h"

#include <list>
#include <memory>

namespace dbf 
{
	//forward declarations
	//class Actor;
	class Renderer;
	class Game;

	class Scene : public GameObject, public ISerializable
	{
	public:
		Scene() = default;
		Scene(Game* game) : m_game{ game } {}
		Scene(const Scene& other);
		~Scene() = default;

		CLASS_DECLARATION(Scene)

		void init() override;
		void update() override;
		void draw(Renderer& renderer);

		virtual bool write(const rapidjson::Value& value) const override;
		virtual bool read(const rapidjson::Value& value) override;

		void Add(std::unique_ptr<Actor> actor);
		void RemoveAll();

		template<typename T>
		T* GetActor();

		template<typename T = Actor>
		T* getActorByName(const std::string& name);

		template<typename T = Actor>
		std::vector<T*> getActorsByTag(const std::string& tag);

		Game* GetGame() { return m_game; }

	private:
		Game* m_game;
		std::list<std::unique_ptr<Actor>> m_actors;

	};


	template<typename T>
	inline T* Scene::GetActor()
	{
		for (auto& actor : m_actors)
		{
			T* result = dynamic_cast<T*>(actor.get());
			if (result) return result;
		}

		return nullptr;
	}
	template<typename T>
	inline T* Scene::getActorByName(const std::string& name)
	{
		for(auto& actor : m_actors)
		{
			if (actor->getName() == name)
				{
				return dynamic_cast<T*>(actor.get());
					 }
		}

		return nullptr;
	}
	template<typename T>
	inline std::vector<T*> Scene::getActorsByTag(const std::string& tag)
	{
		std::vector<T*> result;

		for (auto& actor : m_actors)
		{
			if (actor->getTag == tag)
			{
				T* tagActor = dynamic_cast<T*>(actor.get());
				if (tagActor) result.push_back(tagActor);
			}
		}

		return result;
	}
}