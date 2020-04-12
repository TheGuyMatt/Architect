#ifndef VECTOR3_HPP
#define VECTOR3_HPP

namespace Math
{
	class Vector3
	{
	public:
		Vector3()
			: x(0.0f), y(0.0f), z(0.0f)
		{}

		Vector3(float x, float y, float z)
			: x(x), y(y), z(z)
		{}

		Vector3 operator+(Vector3 const& rhs) const
		{
			return Vector3(
				x + rhs.x,
				y + rhs.y,
				z + rhs.z);
		}

		Vector3 operator+=(Vector3 const& rhs)
		{
			x += rhs.x;
			y += rhs.y;
			z += rhs.z;

			return *this;
		}

		Vector3 operator-(Vector3 const& rhs) const
		{
			return Vector3(
				x - rhs.x,
				y - rhs.y,
				z - rhs.z);
		}

		Vector3 operator-=(Vector3 const& rhs)
		{
			x -= rhs.x;
			y -= rhs.y;
			z -= rhs.z;

			return *this;
		}

		Vector3 operator*(Vector3 const& rhs) const
		{
			return Vector3(
				x * rhs.x,
				y * rhs.y,
				z * rhs.z);
		}

		Vector3 operator*=(Vector3 const& rhs)
		{
			x *= rhs.x;
			y *= rhs.y;
			z *= rhs.z;

			return *this;
		}

		Vector3 operator*(float rhs) const
		{
			return Vector3(
				x * rhs,
				y * rhs,
				z * rhs);
		}

		Vector3 operator*=(float rhs)
		{
			x *= rhs;
			y *= rhs;
			z *= rhs;

			return *this;
		}


		float x, y, z;
	};
}

#endif