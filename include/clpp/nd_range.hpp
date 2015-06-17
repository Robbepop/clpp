#ifndef CLPP_ND_RANGE_HPP
#define CLPP_ND_RANGE_HPP

#include "utility/concepts.hpp"

#include <cstdint>

namespace cl {
	template<size_t N>
	class NDRange final {
	public:
		NDRange();

		// generic constructor which checks Args length against N
		template<typename... Args,
			CLPP_REQUIRES(sizeof...(Args) == N)>
		NDRange(Args&&... tail);

		// singleton for the NullRange
		static auto null() -> NDRange<N> const&;

		auto operator=(NDRange<N> const& rhs) -> NDRange&;

		auto size() const -> size_t;

		auto data()       -> size_t*;
		auto data() const -> size_t const*;

	private:
		std::array<size_t, N> m_data;
	};
}

#endif
