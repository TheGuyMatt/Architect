#ifndef VECTOR4_HPP
#define VECTOR4_HPP

namespace Math
{
	class Vector4
	{
	public:
		Vector4()
			: x(0.0f), y(0.0f), z(0.0f), w(0.0f)
		{}

		Vector4(float x, float y, float z)
			: x(x), y(y), z(z), w(0.0f)
		{}

		Vector4(float x, float y, float z, float w)
			: x(x), y(y), z(z), w(w)
		{}

		Vector4 operator+(Vector4 const& v) const
		{
			return Vector4(
				x + v.x,
				y + v.y,
				z + v.z,
				w + v.w);
		}

		Vector4 operator+=(Vector4 const& v)
		{
			x += v.x;
			y += v.y;
			z += v.z;
			w += v.w;

			return *this;
		}

		Vector4 operator-(Vector4 const& v) const
		{
			return Vector4(
				x - v.x,
				y - v.y,
				z - v.z,
				w - v.w);
		}

		Vector4 operator-=(Vector4 const& v)
		{
			x -= v.x;
			y -= v.y;
			z -= v.z;
			w -= v.w;

			return *this;
		}


		float x, y, z, w;
	};
}

#endif