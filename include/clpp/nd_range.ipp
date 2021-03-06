#ifdef  CLPP_ND_RANGE_IPP
	#error "multiple inclusions of the same implementation file"
#else
#define CLPP_ND_RANGE_IPP

#ifndef CLPP_ND_RANGE_HPP
	#error "header file has not been included; maybe it isn't required anymore?"
	#include "clpp/nd_range.hpp"
#endif

#include "utility/make_array.hpp"

#include <algorithm>
#include <type_traits>
#include <iterator>

namespace cl {
	template<size_t N>
	constexpr NDRange<N>::NDRange() {}

	// generic constructor which checks T+Args length against N
	template<size_t N>
	template<typename... T, typename>
	constexpr NDRange<N>::NDRange(T... args): m_data{{args...}} {}

	template<size_t N>
	auto NDRange<N>::operator=(NDRange<N> const& rhs) -> NDRange& {
		m_data = rhs.m_data;
		return *this;
	}

	template<size_t N>
	auto NDRange<N>::operator[](size_t index) -> size_t& {
		assert(index <= N);
		return m_data[index];
	}

	template<size_t N>
	auto NDRange<N>::operator[](size_t index) const -> size_t const& {
		assert(index <= N);
		return m_data[index];
	}

	template<size_t N>
	constexpr auto NDRange<N>::size() const -> size_type {
		return m_data.size();
	}

	template<size_t N>
	auto NDRange<N>::data() -> pointer {
		return m_data.data();
	}

	template<size_t N>
	auto NDRange<N>::data() const -> const_pointer {
		return m_data.data();
	}

	//============================================================================
	// Iterator interface for NDRange mapping to its underlying std::array.
	//============================================================================

	template<size_t N>
	auto NDRange<N>::begin() -> iterator {
		return m_data.begin();
	}

	template<size_t N>
	auto NDRange<N>::begin() const -> const_iterator {
		return m_data.begin();
	}

	template<size_t N>
	auto NDRange<N>::cbegin() const -> const_iterator {
		return m_data.cbegin();
	}

	template<size_t N>
	auto NDRange<N>::end() -> iterator {
		return m_data.end();
	}

	template<size_t N>
	auto NDRange<N>::end() const -> const_iterator {
		return m_data.end();
	}

	template<size_t N>
	auto NDRange<N>::cend() const -> const_iterator {
		return m_data.cend();
	}

	template<size_t N>
	auto NDRange<N>::rbegin() -> std::reverse_iterator<iterator> {
		return m_data.rbegin();
	}

	template<size_t N>
	auto NDRange<N>::rbegin() const -> std::reverse_iterator<const_iterator> {
		return m_data.rbegin();
	}

	template<size_t N>
	auto NDRange<N>::crbegin() const -> std::reverse_iterator<const_iterator> {
		return m_data.crbegin();
	}

	template<size_t N>
	auto NDRange<N>::rend() -> std::reverse_iterator<iterator> {
		return m_data.rend();
	}

	template<size_t N>
	auto NDRange<N>::rend() const -> std::reverse_iterator<const_iterator> {
		return m_data.rend();
	}

	template<size_t N>
	auto NDRange<N>::crend() const -> std::reverse_iterator<const_iterator> {
		return m_data.crend();
	}

	template<size_t N>
	bool operator==(NDRange<N> const& lhs, NDRange<N> const& rhs) {
		return lhs.m_data == rhs.m_data;
	}

	template<size_t N>
	bool operator!=(NDRange<N> const& lhs, NDRange<N> const& rhs) {
		return !(lhs == rhs);
	}
}

#endif
