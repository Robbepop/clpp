#ifndef CLPP_UTILITY_TO_UNDERLYING_HPP
#define CLPP_UTILITY_TO_UNDERLYING_HPP

#include <type_traits>

namespace utility {
	template<typename E>
	constexpr auto to_underlying(E e) -> typename std::underlying_type<E>::type {
		return static_cast<typename std::underlying_type<E>::type>(e);
	}
}

#endif
