#pragma once
#include "Vector2.h"
#include "Mat3x3.h"
#include "MathUtils.h"
#include "Serialization/Serializable.h"

namespace dbf
{
	struct Transform : public ISerializable
	{
		glm::vec3 position{ 0 };
		glm::vec3 rotation{ 1 };
		glm::vec3 scale{ 1 };

		glm::mat4 matrix;

		Transform() = default;
		Transform(const glm::vec3& position, const glm::vec3& rotation = glm::vec3{ 0 }, const glm::vec3& scale = glm::vec3{ 1 }) :
			position{ position },
			rotation{ rotation },
			scale{ scale }
		{}


		virtual bool write(const rapidjson::Value& value) const override;
		virtual bool read(const rapidjson::Value& value) override;

		void update()
		{
			matrix = *this;
		}

		void update(const glm::mat4& parent)
		{
			matrix = parent * (glm::mat4)*this;
		}

		operator glm::mat4() const
		{
			glm::mat4 mxScale = glm::scale(scale);
			glm::mat4 mxRotation = glm::eulerAngleXYZ(glm::radians(rotation.x), glm::radians(rotation.y), glm::radians(rotation.z));
			glm::mat4 mxTranslation = glm::translate(position);

			return { mxTranslation * mxRotation * mxScale };
		}

		glm::vec3 getRight() { return ((glm::mat4)(*this))[0]; }
		glm::vec3 getUp() { return ((glm::mat4)(*this))[1]; }
		glm::vec3 getForward() { return ((glm::mat4)(*this))[2]; }
	};
}
