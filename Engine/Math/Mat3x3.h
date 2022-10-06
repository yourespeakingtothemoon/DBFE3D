#pragma once
#include "Vector2.h"
#include "Vector3.h"
namespace dbf
{
	struct Mat3x3
	{
		Vector3 rows[3]; // rows/columns

		Mat3x3() = default;
		Mat3x3(const Vector3& row1, const Vector3& row2, const Vector3& row3);

		Vector3 operator[] (size_t index) const { return rows[index]; }
		Vector3& operator[] (size_t index) { return rows[index]; }

		Vector2 operator * (const Vector2& v)const; //m33 x v2
		Mat3x3 operator * (const Mat3x3& mx)const; //m22 x v2

		static const Mat3x3 identity;
		static const Mat3x3 zero;
		static Mat3x3 createScale(const Vector2& scale);
		static Mat3x3 createScale(float scale);
		static Mat3x3 createRotate(float rad);
		static Mat3x3 createTranslation(const Vector2& translate);

		Vector2 GetTranslation() const;
		float GetRotation() const;
		Vector2 GetScale() const;

	};

	inline Mat3x3::Mat3x3(const Vector3& row1, const Vector3& row2, const Vector3& row3)
	{
		rows[0] = row1;
		rows[1] = row2;
		rows[2] = row3;
	}

	inline Vector2 Mat3x3::operator *(const Vector2& v) const
	{
		Vector2 result;

		result.x = v.x * rows[0][0] + v.y * rows[0][1]+ 1.0f * rows[0][2];
		result.x = v.x * rows[1][0] + v.y * rows[1][1]+ 1.0f * rows[1][2];

		return result;
	}

	inline Mat3x3 Mat3x3::operator*(const Mat3x3& mx) const
	{
		Mat3x3 result;

		//row1
		result[0][0] = rows[0][0] * mx[0][0] + rows[0][1] * mx[1][0] + rows[0][2] * mx[2][0];
		result[0][1] = rows[0][0] * mx[0][1] + rows[0][1] * mx[1][1] + rows[0][2] * mx[2][1];
		result[0][2] = rows[0][0] * mx[0][2] + rows[0][1] * mx[1][2] + rows[0][2] * mx[2][2];

		//row2
		result[1][0] = rows[1][0] * mx[1][0] + rows[1][1] * mx[1][0] + rows[1][2] * mx[2][0];
		result[1][1] = rows[1][0] * mx[1][1] + rows[1][1] * mx[1][1] + rows[1][2] * mx[2][1];
		result[1][2] = rows[1][0] * mx[1][2] + rows[1][1] * mx[1][2] + rows[1][2] * mx[2][2];

		//row3
		result[2][0] = rows[2][0] * mx[2][0] + rows[2][1] * mx[2][0] + rows[2][2] * mx[2][0];
		result[2][1] = rows[2][0] * mx[2][1] + rows[2][1] * mx[2][1] + rows[2][2] * mx[2][1];
		result[2][2] = rows[2][0] * mx[2][2] + rows[2][1] * mx[2][2] + rows[2][2] * mx[2][2];

		return result;
	}

	inline Mat3x3 Mat3x3::createScale(const Vector2& scale)
	{
		//Non-Uniform Scale
		Mat3x3 mx = identity;
		//X 0 0
		//0 Y 0
		//0 0 0
		mx[0][0] = scale.x;
			mx[1][1] = scale.y;
		return mx;
		//return Mat3x3();
	}

	inline Mat3x3 Mat3x3::createScale(float scale)
	{
		//Uniform Scale
		Mat3x3 mx = identity;
		//s 0 0
		//0 s 0
		//0 0 0
		mx[0][0] = scale;
		mx[1][1] = scale;
		return mx;
		//return Mat3x3();
	}

	inline Mat3x3 Mat3x3::createRotate(float rad)
	{
		Mat3x3 mx=identity;
		//cR -sR 0.0
		//sR  cR 0.0
		//00  00 1.0

		float c = std::cos(rad);
		float s = std::sin(rad);

		mx[0] = Vector3{ c,    -s, 0.0f };
		mx[1] = Vector3{ s,     c, 0.0f };
		mx[2] = Vector3{ 0.0f,0.0f,1.0f };

		return mx;
	}

	inline Mat3x3 Mat3x3::createTranslation(const Vector2& translate)
	{
		Mat3x3 mx=identity;

		mx[0][2] = translate.x;
		mx[1][2] = translate.y;
		//mx[2][2] = 1;

		return mx;
	}

	inline Vector2 Mat3x3::GetTranslation() const
	{
		//translate diagram
		// 1  0  x 
		// 0  1  y 
		// 0  0  1 

		return { rows[0][2], rows[1][2] };
	}

	inline float Mat3x3::GetRotation() const
	{
		// cos -sin  0 
		// sin  cos  0 
		//  0    0   1 

		// y = sin(angle) = rows[1][0] 
		// x = cos(angle) = rows[0][0] 

		return std::atan2(rows[1][0], rows[0][0]);
	}

	inline Vector2 Mat3x3::GetScale() const
	{
		Vector2 x = { rows[0][0], rows[0][1] };
		Vector2 y = { rows[1][0], rows[1][1] };

		return { x.Length(), y.Length() };
	}


}