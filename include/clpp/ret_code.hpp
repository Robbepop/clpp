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

		inline RetCode(id_type id);
		inline RetCode(RetCode const& other);
		inline RetCode(RetCode && other) = default;

		inline auto operator=(RetCode const& rhs) -> RetCode &;
		inline auto operator=(RetCode && rhs)     -> RetCode & = default;
		inline auto operator=(id_type const& rhs)  -> RetCode &;

		inline constexpr auto operator==(RetCode const& rhs) -> bool;
		inline constexpr auto operator!=(RetCode const& rhs) -> bool;

		inline auto data() -> id_type*;

		inline constexpr auto isError() const   -> bool;
		inline constexpr auto isSuccess() const -> bool;

		inline constexpr auto getCLId() const   -> id_type;
		inline constexpr auto getCLName() const -> std::experimental::string_view;

	private:
		id_type m_id;
	};

	inline constexpr auto operator==(RetCode const& lhs, RetCode::id_type const& rhs) -> bool;
	inline constexpr auto operator!=(RetCode const& lhs, RetCode::id_type const& rhs) -> bool;

	inline constexpr auto operator==(RetCode::id_type const& lhs, RetCode const& rhs) -> bool;
	inline constexpr auto operator!=(RetCode::id_type const& lhs, RetCode const& rhs) -> bool;
}

#endif
