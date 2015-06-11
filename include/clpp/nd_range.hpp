#ifndef CLPP_ND_RANGE_H
#define CLPP_ND_RANGE_H

#include <cstdint>

namespace cl {
	template<size_t N>
	class NDRange final {
	public:

		// generic constructor which checks T+Args length against N
		template<typename T, typename... Args>
		NDRange(T head, Args tail);

		NDRange(NDRange<N> const& rhs);

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

#include "clpp/nd_range.tpp"
#endif
