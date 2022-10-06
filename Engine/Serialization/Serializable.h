#pragma once
#include "JSON.h"

namespace dbf 
{
	class ISerializable
	{
	public:
		virtual ~ISerializable() {};

		virtual bool write(const rapidjson::Value& value) const = 0;
		virtual bool read(const rapidjson::Value& value) = 0;
	};

}