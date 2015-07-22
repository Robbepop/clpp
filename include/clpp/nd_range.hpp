#ifndef CLPP_ND_RANGE_HPP
#define CLPP_ND_RANGE_HPP

#include "utility/concepts.hpp"

#include <cstdint>

namespace cl {
	template<size_t N>
	class NDRange final {
	public:
		//============================================================================
		// Singleton for the NullRange
		//============================================================================

		static auto null() -> NDRange<N> const&;

		//============================================================================
		// NDRange<N> constructors.
		//============================================================================

		NDRange();

		template<typename... Args,
			CLPP_REQUIRES(sizeof...(Args) == N)>
		NDRange(Args&&... tail);

		//============================================================================
		// Convenient helper operators and methods.
		//============================================================================

		auto operator=(NDRange<N> const& rhs) -> NDRange&;

		auto operator[](size_t index)       -> size_t &;
		auto operator[](size_t index) const -> size_t const&;

		auto size() const -> size_t;

		auto data()       -> size_t*;
		auto data() const -> size_t const*;

	private:
		std::array<size_t, N> m_data;
	};
}

#endif
