#ifndef VECTOR4_HPP
#define VECTOR4_HPP

namespace Math
{
	template<typename T>
	class Vector4
	{
	public:
		Vector4() : x(0), y(0), z(0), w(0) {}

		Vector4(T x, T y, T z, T w) : x(x), y(y), z(z), w(w) {}

		Vector4(const Vector4<T>& v) : x(v.x), y(v.y), z(v.z), w(v.w) {}

		Vector4<T> operator +(const Vector4<T>& v)
		{
			return Vector4<T>(
				x + v.x,
				y + v.y,
				z + v.z,
				w + v.w
				);
		}

		Vector4<T> operator +=(const Vector4<T>& v)
		{
			x += v.x;
			y += v.y;
			z += v.z;
			w += v.w;

			return *this;
		}

		Vector4<T> operator -(const Vector4<T>& v)
		{
			return Vector4<T>(
				x - v.x,
				y - v.y,
				z - v.z,
				w - v.w
				);
		}

		Vector4<T> operator -=(const Vector4<T>& v)
		{
			x -= v.x;
			y -= v.y;
			z -= v.z;
			w -= v.w;

			return *this;
		}

		Vector4<T> operator *(const Vector4<T>& v)
		{
			return Vector4<T>(
				x * v.x,
				y * v.y,
				z * v.z,
				w * v.w
				);
		}

		Vector4<T> operator *=(const Vector4<T>& v)
		{
			x *= v.x;
			y *= v.y;
			z *= v.z;
			w *= v.w;

			return *this;
		}

		Vector4<T> operator /(const Vector4<T>& v)
		{
			return Vector4<T>(
				x / v.x,
				y / v.y,
				z / v.z,
				w / v.w
				);
		}

		Vector4<T> operator /=(const Vector4<T>& v)
		{
			x /= v.x;
			y /= v.y;
			z /= v.z;
			w /= v.w;

			return *this;
		}

		T x, y, z, w;
	};

	typedef Vector4<float> Vector4f;
	typedef Vector4<int> Vector4i;
	typedef Vector4<unsigned int> Vector4u;
}

#endif
