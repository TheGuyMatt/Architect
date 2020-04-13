#ifndef VECTOR4I_HPP
#define VECTOR4I_HPP

namespace Math
{
	class Vector4i
	{
	public:
		Vector4i()
			: x(0), y(0), z(0), w(0)
		{}

		Vector4i(int x, int y, int z, int w)
			: x(x), y(y), z(z), w(w)
		{}

		Vector4i operator+(Vector4i const& rhs) const
		{
			return Vector4i(
				x + rhs.x,
				y + rhs.y,
				z + rhs.z,
				w + rhs.w);
		}

		Vector4i operator+=(Vector4i const& rhs)
		{
			x += rhs.x;
			y += rhs.y;
			z += rhs.z;
			w += rhs.w;

			return *this;
		}

		Vector4i operator-(Vector4i const& rhs) const
		{
			return Vector4i(
				x - rhs.x,
				y - rhs.y,
				z - rhs.z,
				w - rhs.w);
		}

		Vector4i operator-=(Vector4i const& rhs)
		{
			x -= rhs.x;
			y -= rhs.y;
			z -= rhs.z;
			w -= rhs.w;

			return *this;
		}

		Vector4i operator*(Vector4i const& rhs) const
		{
			return Vector4i(
				x * rhs.x,
				y * rhs.y,
				z * rhs.z,
				w * rhs.z);
		}

		Vector4i operator*=(Vector4i const& rhs)
		{
			x *= rhs.x;
			y *= rhs.y;
			z *= rhs.z;
			w *= rhs.w;

			return *this;
		}

		Vector4i operator*(int rhs) const
		{
			return Vector4i(
				x * rhs,
				y * rhs,
				z * rhs,
				w * rhs);
		}

		Vector4i operator*=(int rhs)
		{
			x *= rhs;
			y *= rhs;
			z *= rhs;
			w *= rhs;

			return *this;
		}


		int x, y, z, w;
	};
}

#endif