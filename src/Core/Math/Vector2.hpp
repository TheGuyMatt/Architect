#ifndef VECTOR2_HPP
#define VECTOR2_HPP

#include <utility>

namespace Math
{
	template<typename T>
  class Vector2
	{
	public:
		Vector2() : x(0), y(0) {}

		Vector2(T x, T y) : x(x), y(y) {}

		Vector2(const Vector2<T>& v) : x(v.x), y(v.y) {}

		Vector2<T> operator +(const Vector2<T>& v)
		{
			return Vector2<T>(
				x + v.x,
				y + v.y
				);
		}

    Vector2<T> operator +=(const Vector2<T>& v)
		{
			x += v.x;
			y += v.y;

			return *this;
		}

    Vector2<T> operator -(const Vector2<T>& v)
		{
			return Vector2<T>(
				x - v.x,
				y - v.y
				);
		}
    
    Vector2<T> operator -=(const Vector2<T>& v)
		{
			x -= v.x;
			y -= v.y;

			return *this;
		}

    Vector2<T> operator *(const Vector2<T>& v)
		{
			return Vector2<T>(
				x * v.x,
				y * v.y
				);
		}

    Vector2<T> operator *=(const Vector2<T>& v)
		{
			x *= v.x;
			y *= v.y;

			return *this;
		}

    Vector2<T> operator /(const Vector2<T>& v)
		{
			return Vector2<T>(
				x / v.x,
				y / v.y
				);
		}

    Vector2<T> operator /=(const Vector2<T>& v)
		{
			x /= v.x;
			y /= v.y;

			return *this;
		}

		T x, y;
	};

	typedef Vector2<float> Vector2f;
	typedef Vector2<int> Vector2i;
	typedef Vector2<unsigned int> Vector2u;
}

#endif
