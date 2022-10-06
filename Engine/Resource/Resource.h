#pragma once
#include <string>

namespace dbf 
{
	class Resource
	{
	public:
		virtual bool Create(std::string name, ...) = 0;
	};
}