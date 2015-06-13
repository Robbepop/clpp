#ifndef CLPP_ND_RANGE_H
	#error "Do not include this file directly."
#endif

#include "utility/make_array.hpp"

#include <algorithm>
#include <type_traits>

namespace cl {
	template<size_t N>
	NDRange<N>::NDRange() {}

	// generic constructor which checks T+Args length against N
	template<size_t N>
	template<typename... Args, typename>
	NDRange<N>::NDRange(Args&&... tail) {
		static_assert(N == sizeof...(tail),
			"NDRange element count does not fit");
		m_data = utility::make_array<size_t>(std::forward<Args>(tail)...);
	}

//	template<size_t N>
//	NDRange<N>::NDRange(NDRange<N> const& rhs):
//		m_data{std::move(rhs.m_data)}
//	{}

	// singleton for the NullRange
	template<size_t N>
	auto NDRange<N>::null() -> NDRange<N> const& {
		static const auto nullRange = NDRange{};
		return nullRange;
	}

	template<size_t N>
	auto NDRange<N>::operator=(NDRange<N> const& rhs) -> NDRange& {
		m_data = rhs.m_data;
	}

	template<size_t N>
	auto NDRange<N>::size() const -> size_t {
		m_data.size();
	}

	template<size_t N>
	auto NDRange<N>::data() -> size_t* {
		m_data.data();
	}

	template<size_t N>
	auto NDRange<N>::data() const -> const size_t* {
		m_data.data();
	}
}
