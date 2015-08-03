#ifndef CLPP_RET_CODE_HPP
#define CLPP_RET_CODE_HPP

#include "clpp/detail/common.hpp"

#include <experimental/string_view>

namespace cl {
	class RetCode final {
	public:
		using id_type = cl_int;

	private:
		static constexpr id_type c_presetId = 1;
	public:
		static inline auto getPreset() -> RetCode const&;

		constexpr inline RetCode();
		constexpr inline RetCode(id_type id);
		constexpr inline RetCode(RetCode const& other);
		constexpr inline RetCode(RetCode && other) = default;

		constexpr inline auto operator=(RetCode const& rhs) -> RetCode &;
		constexpr inline auto operator=(id_type const& rhs)  -> RetCode &;

		constexpr inline auto operator==(RetCode const& rhs) -> bool;
		constexpr inline auto operator!=(RetCode const& rhs) -> bool;

		inline auto data() -> id_type*;

		constexpr inline auto isError() const   -> bool;
		constexpr inline auto isSuccess() const -> bool;

		constexpr inline auto getCLId() const   -> id_type;
		constexpr inline auto getCLName() const -> std::experimental::string_view;

	private:
		id_type m_id;
	};

	inline constexpr auto operator==(RetCode const& lhs, RetCode::id_type const& rhs) -> bool;
	inline constexpr auto operator!=(RetCode const& lhs, RetCode::id_type const& rhs) -> bool;

	inline constexpr auto operator==(RetCode::id_type const& lhs, RetCode const& rhs) -> bool;
	inline constexpr auto operator!=(RetCode::id_type const& lhs, RetCode const& rhs) -> bool;
}

#endif
