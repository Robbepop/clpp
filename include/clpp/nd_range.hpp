#ifndef CLPP_ND_RANGE_HPP
#define CLPP_ND_RANGE_HPP

#include "utility/concepts.hpp"

#include <cstdint>

namespace cl {
	template<size_t N>
	class NDRange final {
	public:
		using value_type      = size_t;
		using size_type       = size_t;
		using reference       = value_type&;
		using const_reference = value_type const&;
		using pointer         = value_type*;
		using const_pointer   = value_type const*;
		using iterator        = pointer;
		using const_iterator  = const_pointer;

		//============================================================================
		// NDRange<N> constructors.
		//============================================================================

		constexpr NDRange();

		template<typename... T,
			CLPP_REQUIRES(sizeof...(T) == N)>
		constexpr NDRange(T... args);

		//============================================================================
		// Convenient helper operators and methods.
		//============================================================================

		auto operator=(NDRange<N> const& rhs) -> NDRange&;

		auto operator[](size_t index)       -> reference;
		auto operator[](size_t index) const -> const_reference;

		constexpr auto size() const -> size_type;

		auto data()       -> pointer;
		auto data() const -> const_pointer;

		//============================================================================
		// Iterator interface for NDRange mapping to its underlying std::array.
		//============================================================================

		auto  begin()       -> iterator;
		auto  begin() const -> const_iterator;
		auto cbegin() const -> const_iterator;

		auto  end()       -> iterator;
		auto  end() const -> const_iterator;
		auto cend() const -> const_iterator;

		auto  rbegin()       -> std::reverse_iterator<iterator>;
		auto  rbegin() const -> std::reverse_iterator<const_iterator>;
		auto crbegin() const -> std::reverse_iterator<const_iterator>;

		auto  rend()       -> std::reverse_iterator<iterator>;
		auto  rend() const -> std::reverse_iterator<const_iterator>;
		auto crend() const -> std::reverse_iterator<const_iterator>;

		template<size_t M>
		friend bool operator==(NDRange<M> const& lhs, NDRange<M> const& rhs);

		template<size_t M>
		friend bool operator!=(NDRange<M> const& lhs, NDRange<M> const& rhs);

	private:
		std::array<size_t, N> m_data;
	};

	template<size_t N>
	bool operator==(NDRange<N> const& lhs, NDRange<N> const& rhs);

	template<size_t N>
	bool operator!=(NDRange<N> const& lhs, NDRange<N> const& rhs);
}

#endif
