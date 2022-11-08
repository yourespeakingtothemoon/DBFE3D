#pragma once 
#include "Component.h" 

namespace dbf
{
	class CameraControl : public Component
	{
	public:
		CLASS_DECLARATION(CameraControl)

			void update() override;

		virtual bool write(const rapidjson::Value& value) const override;
		virtual bool read(const rapidjson::Value& value) override;

	private:
		float speed = 0;
	};
}