#ifndef VECTOR3_HPP
#define VECTOR3_HPP

namespace Math
{
	template<typename T>
	class Vector3
	{
	public:
		Vector3() : x(0), y(0), z(0) {}

		Vector3(T x, T y, T z) : x(x), y(y), z(z) {}

		Vector3(const Vector3<T>& v) : x(v.x), y(v.y), z(v.z) {}

		template<typename T>
		Vector3<T> operator +(const Vector3<T>& v)
		{
			return Vector3<T>(
				x + v.x,
				y + v.y,
				z + v.z
				);
		}

		template<typename T>
		Vector3<T> operator +=(const Vector3<T>& v)
		{
			x += v.x;
			y += v.y;
			z += v.z;

			return *this;
		}

		template<typename T>
		Vector3<T> operator -(const Vector3<T>& v)
		{
			return Vector3<T>(
				x - v.x,
				y - v.y,
				z - v.z
				);
		}

		template<typename T>
		Vector3<T> operator -=(const Vector3<T>& v)
		{
			x -= v.x;
			y -= v.y;
			z -= v.z;

			return *this;
		}

		template<typename T>
		Vector3<T> operator *(const Vector3<T>& v)
		{
			return Vector3<T>(
				x * v.x,
				y * v.y,
				z * v.z
				);
		}

		template<typename T>
		Vector3<T> operator *=(const Vector3<T>& v)
		{
			x *= v.x;
			y *= v.y;
			z *= v.z;

			return *this;
		}

		template<typename T>
		Vector3<T> operator /(const Vector3<T>& v)
		{
			return Vector3<T>(
				x / v.x,
				y / v.y,
				z / v.z
				);
		}

		template<typename T>
		Vector3<T> operator /=(const Vector3<T>& v)
		{
			x /= v.x;
			y /= v.y;
			z /= v.z;

			return *this;
		}

		T x, y, z;
	};

	typedef Vector3<float> Vector3f;
	typedef Vector3<int> Vector3i;
	typedef Vector3<unsigned int> Vector3u;
}

#endif