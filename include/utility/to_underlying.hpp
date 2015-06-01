#ifndef CLPP_DETAIL_TO_UNDERLYING_H
#define CLPP_DETAIL_TO_UNDERLYING_H

#include <type_traits>

namespace utility {
	template<typename E>
	constexpr auto to_underlying(E e) -> typename std::underlying_type<E>::type {
		return static_cast<typename std::underlying_type<E>::type>(e);
	}
}

#endif
