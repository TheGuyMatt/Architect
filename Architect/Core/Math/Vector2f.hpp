#ifndef VECTOR2F_HPP
#define VECTOR2F_HPP

namespace Math
{
	class Vector2f
	{
	public:
		Vector2f()
			: x(0.0f), y(0.0f)
		{}

		Vector2f(float x, float y)
			: x(x), y(y)
		{}

		Vector2f operator+(Vector2f const& v)
		{
			return Vector2f(
				x + v.x,
				y + v.y);
		}

		Vector2f operator+=(Vector2f const& v)
		{
			x += v.x;
			y += v.y;

			return *this;
		}

		Vector2f operator-(Vector2f const& v)
		{
			return Vector2f(
				x - v.x,
				y - v.y);
		}

		Vector2f operator-=(Vector2f const& v)
		{
			x -= v.x;
			y -= v.y;

			return *this;
		}


		float x, y;
	};
}

#endif