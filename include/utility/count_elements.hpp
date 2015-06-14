#ifndef UTILITY_COUNT_ELEMENTS_H
#define UTILITY_COUNT_ELEMENTS_H

namespace utility {
	template<typename Iterator>
	auto count_elements(Iterator first, Iterator last) -> size_t {
		return static_cast<size_t>(std::distance(
			std::min(first, last), std::max(first, last)));
	}
}

#endif
