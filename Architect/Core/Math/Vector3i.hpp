#ifndef VECTOR3I_HPP
#define VECTOR3I_HPP

namespace Math
{
	class Vector3i
	{
	public:
		Vector3i()
			: x(0), y(0), z(0)
		{}

		Vector3i(int x, int y, int z)
			: x(x), y(y), z(z)
		{}

		Vector3i operator+(Vector3i const& rhs) const
		{
			return Vector3i(
				x + rhs.x,
				y + rhs.y,
				z + rhs.z);
		}

		Vector3i operator+=(Vector3i const& rhs)
		{
			x += rhs.x;
			y += rhs.y;
			z += rhs.z;

			return *this;
		}

		Vector3i operator-(Vector3i const& rhs) const
		{
			return Vector3i(
				x - rhs.x,
				y - rhs.y,
				z - rhs.z);
		}

		Vector3i operator-=(Vector3i const& rhs)
		{
			x -= rhs.x;
			y -= rhs.y;
			z -= rhs.z;

			return *this;
		}

		Vector3i operator*(Vector3i const& rhs) const
		{
			return Vector3i(
				x * rhs.x,
				y * rhs.y,
				z * rhs.z);
		}

		Vector3i operator*=(Vector3i const& rhs)
		{
			x *= rhs.x;
			y *= rhs.y;
			z *= rhs.z;

			return *this;
		}

		Vector3i operator*(int rhs) const
		{
			return Vector3i(
				x * rhs,
				y * rhs,
				z * rhs);
		}

		Vector3i operator*=(int rhs)
		{
			x *= rhs;
			y *= rhs;
			z *= rhs;

			return *this;
		}


		int x, y, z;
	};
}

#endif