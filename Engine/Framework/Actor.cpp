#include "Actor.h"
#include "Factory.h"
#include "Components/RenderComponent.h"
#include "Core/Logger.h"
#include "Engine.h"

namespace dbf 
{
	Actor::Actor(const Actor& other)
	{
		name = other.name;
		tag = other.tag;
		m_transform = other.m_transform;
		lifespan = other.lifespan;
		m_scene = other.m_scene;

		for (auto& component : other.m_components)
		{
			auto clone = std::unique_ptr<Component>((Component*)component->Clone().release());
			addComponent(std::move(clone));
		}
	}

	void Actor::init()
	{
		for (auto& component : m_components)
		{
			component->init();
		}
		for (auto& child : m_children)
		{
			child->init();
		}
	}

	void Actor::update()
	{
		if (!active) return;

		// update lifespan if lifespan is not 0 
		if (lifespan != 0)
		{
			lifespan -= g_time.deltaTime;
			if (lifespan <= 0)
			{
				flipDestroy();
			}
		}

		for (auto& component : m_components)
		{
			component->update();
		}
		for (auto& child : m_children)
		{
			child->update();
		}

		if (m_parent) m_transform.update(m_parent->m_transform.matrix);
		else m_transform.update();
	}

	void Actor::draw(Renderer& renderer)
	{
		if (!active) return;

		for (auto& component : m_components)
		{
			auto renderComponent = dynamic_cast<RenderComponent*>(component.get());
			if (renderComponent)
			{
				renderComponent->draw(renderer);
			}
		}
		for (auto& child : m_children)
		{
			child->draw(renderer);
		}
	}

	void Actor::addChild(std::unique_ptr<Actor> child)
	{
		child->m_parent = this;
		child->m_scene = m_scene;
		m_children.push_back(std::move(child));
	}

	void Actor::addComponent(std::unique_ptr<Component> component)
	{
		component->m_owner = this;
		m_components.push_back(std::move(component));
	}

	bool Actor::write(const rapidjson::Value& value) const
	{
		return true;
	}

	bool Actor::read(const rapidjson::Value& value)
	{
		READ_DATA(value, tag);
		READ_DATA(value, name);
		READ_DATA(value, active);
		READ_DATA(value, lifespan);

		if (value.HasMember("transform")) m_transform.read(value["transform"]);
		//m_transform.Read(value["transform"]);

		if (value.HasMember("components") && value["components"].IsArray())
		{
			for (auto& componentValue : value["components"].GetArray())
			{
				std::string type;
				READ_DATA(componentValue, type);

				auto component = Factory::instance().Create<Component>(type);
				if (component)
				{
					component->read(componentValue);
					addComponent(std::move(component));
				}
			}
		}
		else 
		{
			LOG("Error reading Actor");
		}

		return true;
	}
}
