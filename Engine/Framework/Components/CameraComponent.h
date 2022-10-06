#pragma once 
#include "Component.h" 
#include "Math/Mat3x3.h" 

namespace dbf
{
	class CameraComponent : public Component
	{
	public:
		CLASS_DECLARATION(CameraComponent)

			virtual void init() override;
		virtual void update() override;

		const Mat3x3& GetView() { return m_view; }

		void setViewport(const Vector2& size);
		const Mat3x3& GetViewport() { return m_viewport; }

		virtual bool write(const rapidjson::Value& value) const override;
		virtual bool read(const rapidjson::Value& value) override;

	public:
		Vector2 viewport_size;

		Mat3x3 m_view;
		Mat3x3 m_viewport;
	};
}