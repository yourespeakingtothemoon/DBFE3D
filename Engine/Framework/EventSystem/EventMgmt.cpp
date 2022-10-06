#include "EventMgmt.h"

namespace dbf {

	void EventMgmt::init()
	{
	}

	void EventMgmt::shutdown()
	{
	}

	void EventMgmt::update()
	{
	}

	void dbf::EventMgmt::subscribe(const std::string& name, Event::functionPtr function, GameObject* receiver)
	{
		Observer observer;
		observer.receiver = receiver;
		observer.function = function;
		m_events[name].push_back(observer);
	}

	void dbf::EventMgmt::unsubscribe(const std::string& name, GameObject* receiver)
	{
	}

	void dbf::EventMgmt::notify(const Event& _event)
	{
		auto& observers = m_events[_event.name];
		for (auto& observer : observers)
		{
			if (_event.receiver == nullptr || _event.receiver == observer.receiver)
			{
				observer.function(_event);
			}
		}
	}
}