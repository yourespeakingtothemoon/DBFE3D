#pragma once
#include "Event.h"
#include <map>
#include <list>

namespace dbf
{
	class EventMgmt
	{
	public:
		struct Observer
		{
			GameObject* receiver=nullptr;
			Event::functionPtr function;

		};
	public:
		//baseline
		void init();
		void shutdown();
		void update();
		//allow subscription and unsubscription from events
		void subscribe(const std::string& name, Event::functionPtr function, GameObject* receiver = nullptr);
		void unsubscribe(const std::string& name, GameObject* receiver);
		//notify subscribing objects
		void notify(const Event& _event);

	private:
		std::map<std::string, std::list<Observer>> m_events;

	};
}