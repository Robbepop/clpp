#ifndef CLPP_UTILITY_COUNT_ELEMENTS_HPP
#define CLPP_UTILITY_COUNT_ELEMENTS_HPP

#include <algorithm>
#include <iterator>

namespace utility {
	template<typename Iterator>
	auto count_elements(Iterator first, Iterator last) -> size_t {
		const auto minmax = std::minmax(first, last);
		return static_cast<size_t>(std::distance(minmax.first, minmax.second));
	}
}

#endif
