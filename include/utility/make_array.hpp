#include <array>
#include <utility>
#include <algorithm>
#include <iostream>

namespace utility {
	template<class T, class... Tail>
	auto make_array(T&& head, Tail&&... values) {
		return std::array<T, 1 + sizeof...(Tail)>{
			std::forward<T>(head), std::forward<Tail>(values)...};
	}
}
