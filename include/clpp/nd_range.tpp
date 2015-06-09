#ifndef CLPP_ND_RANGE_H
	#error "Do not include this file directly."
#endif

#include "utility/make_array.hpp"

#include <algorithm>
#include <type_traits>

namespace cl {
	template<size_t N>
	NDRange::NDRange() {}

	// generic constructor which checks T+Args length against N
	template<size_t N>
	template<typename T, typename... Args>
	NDRange::NDRange(T&& head, Args&& tail) {
		static_assert(N == 1 + sizeof...(tail),
			"NDRange element count does not fit");
		m_data = utility::make_array<size_t>(T, tail);
	}

	template<size_t N>
	NDRange::NDRange(NDRange<N> const& rhs):
		m_data{std::move(rhs.m_data)}
	{}

	// singleton for the NullRange
	template<size_t N>
	auto NDRange::null() -> NDRange<N> const& {
		static const auto nullRange = NDRange{};
		return nullRange;
	}

	template<size_t N>
	auto NDRange::operator=(NDRange<N> const& rhs) -> NDRange& {
		m_data = rhs.m_data;
	}

	template<size_t N>
	auto NDRange::size() const -> size_t {
		m_data.size();
	}

	template<size_t N>
	auto NDRange::data() -> size_t* {
		m_data.data();
	}

	template<size_t N>
	auto NDRange::data() const -> const size_t* {
		m_data.data();
	}
}
