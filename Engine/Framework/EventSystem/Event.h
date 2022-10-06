#pragma once
#include <string>
#include <variant>
#include <functional>

namespace dbf
{
	class GameObject;

	class Event
	{
	public:
		using functionPtr = std::function<void(const Event&)>;
	public:
		std::string name;
		GameObject* receiver = nullptr;
		std::variant <int, bool, float, std::string> eventData;

	};

	class INotify
	{
	public:
		virtual void OnNotify(const Event& event) = 0;
	};
}