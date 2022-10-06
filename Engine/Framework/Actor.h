#pragma once
#include "GameObject.h"
#include "Math/Transform.h"
#include "Components/Component.h"
#include <vector>
#include <memory>

namespace dbf
{
	class Scene; //forward declartion
	class Renderer;
	class Actor : public GameObject, public ISerializable
	{
	public:
		Actor() = default;
		Actor(const Actor& other);
		Actor(const Transform& transform) : m_transform{ transform } {}

		CLASS_DECLARATION(Actor)

		// Inherited via GameObject
		virtual void init() override;
		virtual void update() override;
		virtual void draw(Renderer& renderer);

		// Inherited via ISerializable
		virtual bool write(const rapidjson::Value& value) const override;
		virtual bool read(const rapidjson::Value& value) override;

		void addChild(std::unique_ptr<Actor> child);

		void addComponent(std::unique_ptr<Component> component);

		template<typename T>
		T* getComponent();

		virtual void OnCollision(Actor* other) {}
		float GetRadius() { return 0; }
		
		const std::string& getTag() { return tag; }
		void setTag(const std::string& tag) { this->tag = tag; }
		const std::string& getName() { return name; }
		void setName(const std::string& name) { this->name = name; }

		//destroy
		void flipDestroy() { m_destroy = true; }
		bool queryDestroy() { return m_destroy; }

		void setActive(bool active = true) { this->active = active; }
		bool queryActive() { return active; }

		Scene* getScene() { return m_scene; }

		friend class Scene;
		friend class Component;
		
		Transform m_transform;

	protected:
		std::string name;
		std::string tag;
		bool active = true;
		bool m_destroy = false;

		float lifespan = 0;

		Scene* m_scene = nullptr;
		Actor* m_parent = nullptr;

		std::vector<std::unique_ptr<Component>> m_components;
		std::vector<std::unique_ptr<Actor>> m_children;

	};

	template<typename T>
	inline T* Actor::getComponent()
	{
		for (auto& component : m_components)
		{
			T* result = dynamic_cast<T*>(component.get());
			if (result) return result;
		}

		return nullptr;
	}
}