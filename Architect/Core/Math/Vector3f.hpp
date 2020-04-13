#ifndef VECTOR3F_HPP
#define VECTOR3F_HPP

namespace Math
{
	class Vector3f
	{
	public:
		Vector3f()
			: x(0.0f), y(0.0f), z(0.0f)
		{}

		Vector3f(float x, float y, float z)
			: x(x), y(y), z(z)
		{}

		Vector3f operator+(Vector3f const& rhs) const
		{
			return Vector3f(
				x + rhs.x,
				y + rhs.y,
				z + rhs.z);
		}

		Vector3f operator+=(Vector3f const& rhs)
		{
			x += rhs.x;
			y += rhs.y;
			z += rhs.z;

			return *this;
		}

		Vector3f operator-(Vector3f const& rhs) const
		{
			return Vector3f(
				x - rhs.x,
				y - rhs.y,
				z - rhs.z);
		}

		Vector3f operator-=(Vector3f const& rhs)
		{
			x -= rhs.x;
			y -= rhs.y;
			z -= rhs.z;

			return *this;
		}

		Vector3f operator*(Vector3f const& rhs) const
		{
			return Vector3f(
				x * rhs.x,
				y * rhs.y,
				z * rhs.z);
		}

		Vector3f operator*=(Vector3f const& rhs)
		{
			x *= rhs.x;
			y *= rhs.y;
			z *= rhs.z;

			return *this;
		}

		Vector3f operator*(float rhs) const
		{
			return Vector3f(
				x * rhs,
				y * rhs,
				z * rhs);
		}

		Vector3f operator*=(float rhs)
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