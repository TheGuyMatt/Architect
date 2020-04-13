#ifndef VECTOR2I_HPP
#define VECTOR2I_HPP

namespace Math
{
	class Vector2i
	{
	public:
		Vector2i()
			: x(0), y(0)
		{}

		Vector2i(int x, int y)
			: x(x), y(y)
		{}

		Vector2i operator+(Vector2i const& v)
		{
			return Vector2i(
				x + v.x,
				y + v.y);
		}

		Vector2i operator+=(Vector2i const& v)
		{
			x += v.x;
			y += v.y;

			return *this;
		}

		Vector2i operator-(Vector2i const& v)
		{
			return Vector2i(
				x - v.x,
				y - v.y);
		}

		Vector2i operator-=(Vector2i const& v)
		{
			x -= v.x;
			y -= v.y;

			return *this;
		}


		int x, y;
	};
}

#endif