#ifndef EVENDEPENDENCIES_HPP
#define EVENDEPENDENCIES_HPP

#include <cstdint>
#include <bitset>

// Source: https://gist.github.com/Lee-R/3839813
constexpr std::uint32_t fnv1a_32(char const* s, std::size_t count)
{
	return ((count ? fnv1a_32(s, count - 1) : 2166136261u) ^ s[count]) * 16777619u; // NOLINT (hicpp-signed-bitwise)
}

constexpr std::uint32_t operator "" _hash(char const* s, std::size_t count)
{
	return fnv1a_32(s, count);
}

using EventId = std::uint32_t;
using ParamId = std::uint32_t;

#define METHOD_LISTENER(EventType, Listener) EventType, std::bind(&Listener, this, std::placeholders::_1)
#define FUNCTION_LISTENER(EventType, Listener) EventType, std::bind(&Listener, std::placeholders::_1)

//Integral constant overflow (warning C4307) is being ignored here
#ifdef _MSC_VER
#   pragma warning( push )
#   pragma warning( disable: 4307 )
namespace Events
{
	namespace Window
	{
		const EventId QUIT = "Events::Window::QUIT"_hash;
		const EventId INPUT = "Events::Window::INPUT"_hash;

		namespace Input
		{
			const ParamId INPUT = "Events::Window::Input::INPUT"_hash;
		}
	}
}
#   pragma warning( pop )
#else
namespace Events
{
	namespace Window
	{
		const EventId QUIT = "Events::Window::QUIT"_hash;
		const EventId INPUT = "Events::Window::INPUT"_hash;

		namespace Input
		{
			const ParamId INPUT = "Events::Window::Input::INPUT"_hash;
		}
	}
}
#endif

#endif