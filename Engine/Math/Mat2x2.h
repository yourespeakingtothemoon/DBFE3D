#pragma once
#include "Vector2.h"
namespace dbf
{
	struct Mat2x2
	{
		Vector2 rows[2];

		Mat2x2() = default;
		Mat2x2(const Vector2& row1, const Vector2& row2);
	
		Vector2 operator[] (size_t index) const { return rows[index]; }
		Vector2& operator[] (size_t index) { return rows[index]; }
	
		Vector2 operator * (const Vector2& v); //m22 x v2
		Mat2x2 operator * (const Mat2x2& mx); //m22 x v2
		
		static const Mat2x2 identity;
		static const Mat2x2 zero;
		static Mat2x2 createScale(const Vector2& scale);
		static Mat2x2 createScale(float scale);
		static Mat2x2 createRotate(float rad);
	
	};

	inline Mat2x2::Mat2x2(const Vector2& row1, const Vector2& row2)
	{
		rows[0] = row1;
		rows[1] = row2;
	}

	inline Vector2 Mat2x2::operator *(const Vector2& v)
	{
		Vector2 result;

		result.x=v.x* rows[0][0] + v.y * rows[0][1];
		result.x=v.x* rows[1][0] + v.y * rows[1][1];

		return result;
	}

	inline Mat2x2 Mat2x2::operator*(const Mat2x2& mx)
	{
		Mat2x2 result;

		result[0][0] = mx.rows[0][0]*rows[0][0]+ mx.rows[1][0] * rows[0][1];
		result[0][1] = mx.rows[0][1] * rows[0][1]+ mx.rows[1][1] * rows[0][1];
		result[1][0] = mx.rows[0][0] * rows[1][0] + mx.rows[1][0] * rows[1][1]; ;
		result[1][1] = mx.rows[0][1] * rows[1][0] + mx.rows[1][1] * rows[1][1];;

		return result;
	}

	inline Mat2x2 Mat2x2::createScale(const Vector2& scale)
	{
		//Non-Uniform Scale
		Mat2x2 mx;
		//scaleX 0
		//0 scaleY
		mx[0] = Vector2{ scale.x,0.0f };
		mx[1] = Vector2{ 0.0f,scale.y };
		return mx;
		//return Mat2x2();
	}

	inline Mat2x2 Mat2x2::createScale(float scale)
	{
		//Uniform Scale
		Mat2x2 mx;
		//scaleX 0
		//0 scaleY
		mx[0] = Vector2{ scale,0.0f };
		mx[1] = Vector2{ 0.0f,scale };
		return mx;
	}

	inline Mat2x2 Mat2x2::createRotate(float rad)
	{
		Mat2x2 mx;

		float c = std::cos(rad);
		float s = std::sin(rad);

		mx[0] = Vector2{c,-s};
		mx[1] = Vector2{s,c};

		return mx;
	}


}