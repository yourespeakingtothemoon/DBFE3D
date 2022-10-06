#pragma once
#include "Vector2.h"
#include "Mat3x3.h"
#include "MathUtils.h"
#include "Serialization/Serializable.h"

namespace dbf
{
	struct Transform : public ISerializable
	{
		Vector2 position;
		float rotation;
		Vector2 scale{ 1, 1 };

		Mat3x3 matrix;


		// Inherited via ISerializable
		virtual bool write(const rapidjson::Value& value) const override;
		virtual bool read(const rapidjson::Value& value) override;

		void update()
		{
			Mat3x3 mxScale = Mat3x3::createScale(scale);
			Mat3x3 mxRotation = Mat3x3::createRotate(math::DegToRad(rotation));
			Mat3x3 mxTranslation = Mat3x3::createTranslation(position);

			matrix = { mxTranslation * mxRotation * mxScale };
		}

		void update(const Mat3x3& parent)
		{
			Mat3x3 mxScale = Mat3x3::createScale(scale);
			Mat3x3 mxRotation = Mat3x3::createRotate(math::DegToRad(rotation));
			Mat3x3 mxTranslation = Mat3x3::createTranslation(position);

			matrix = { mxTranslation * mxRotation * mxScale };
			matrix = parent * matrix;
		}

		operator Mat3x3 () const
		{
			Mat3x3 mxScale = Mat3x3::createScale(scale);
			Mat3x3 mxRotation = Mat3x3::createRotate(math::DegToRad(rotation));
			Mat3x3 mxTranslation = Mat3x3::createTranslation(position);

			return { mxTranslation * mxRotation * mxScale };
		}

	};
}
