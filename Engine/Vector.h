#pragma once

namespace Engine
{
	template<typename T>
	struct Vector2D
	{
		Vector2D() : x(0), y(0)
		{ }
		Vector2D(T newX, T newY) : x(newX), y(newY)
		{ }
		T x = (T)0;
		T y = (T)0;

		float GetLength()
		{
			return sqrtf(x * x + y * y);
		}

		T Dot(Vector2D& otherVector)
		{
			return x * otherVector.x + y * otherVector.y;
		}
	};

	using Vector2Df = Vector2D<float>;
	using Vector2Di = Vector2D<int>;
	using Position = Vector2Df;

	template<typename T>
	Vector2D<T> operator+(const Vector2D<T>& lhs, const Vector2D<T>& rhs)
	{
		return { lhs.x + rhs.x, lhs.y + rhs.y };
	}

	template<typename T>
	Vector2D<T> operator-(const Vector2D<T>& lhs, const Vector2D<T>& rhs)
	{
		return { lhs.x - rhs.x, lhs.y - rhs.y };
	}

	template<typename T>
	Vector2D<T> operator-(const Vector2D<T>& lhs)
	{
		return { -lhs.x, -lhs.y };
	}

	template<typename T>
	Vector2D<float> operator*(const Vector2D<T>& lhs, const float rhs)
	{
		return { lhs.x * rhs, lhs.y * rhs };
	}

	template<typename T>
	Vector2D<float> operator*(const float lhs, const Vector2D<T>& rhs)
	{
		return { lhs * rhs.x, lhs * rhs.y };
	}

	template<typename T>
	bool operator==(const Vector2D<T>& lhs, const Vector2D<T>& rhs)
	{
		return lhs.x == rhs.x && lhs.y == rhs.y;
	}

	template<typename T>
	bool operator!=(const Vector2D<T>& lhs, const Vector2D<T>& rhs)
	{
		return lhs.x != rhs.x || lhs.y != rhs.y;
	}


	// This complex template allows us to convert any vector type to any other vector type (like our Vector2D to SFML's Vector and vice versa)
	template<typename U, typename V>
	U Convert(const V& v)
	{
		// decltype deduces type from expression
		return { static_cast<decltype(U::x)>(v.x), static_cast<decltype(U::y)>(v.y) };
	}
}