#ifndef CLPP_RET_CODE2_HPP
#define CLPP_RET_CODE2_HPP

#include "clpp/detail/common.hpp"

#include <experimental/string_view>

namespace cl {
	class RetCode2 final {
	public:
		using id_type = cl_int;

	private:
		static constexpr id_type c_presetId = 1;
	public:
		static inline auto getPreset() -> RetCode2 const&;

		inline RetCode2(id_type id);
		inline RetCode2(RetCode2 const& other);
		inline RetCode2(RetCode2 && other) = default;

		inline auto operator=(RetCode2 const& rhs) -> RetCode2 &;
		inline auto operator=(RetCode2 && rhs)     -> RetCode2 & = default;
		inline auto operator=(id_type const& rhs)  -> RetCode2 &;

		inline constexpr auto operator==(RetCode2 const& rhs) -> bool;
		inline constexpr auto operator!=(RetCode2 const& rhs) -> bool;

		inline auto data() -> id_type*;

		inline constexpr auto isError() const   -> bool;
		inline constexpr auto isSuccess() const -> bool;

		inline constexpr auto getCLId() const   -> id_type;
		inline constexpr auto getCLName() const -> std::experimental::string_view;

	private:
		id_type m_id;
	};

	inline constexpr auto operator==(RetCode2 const& lhs, RetCode2::id_type const& rhs) -> bool;
	inline constexpr auto operator!=(RetCode2 const& lhs, RetCode2::id_type const& rhs) -> bool;

	inline constexpr auto operator==(RetCode2::id_type const& lhs, RetCode2 const& rhs) -> bool;
	inline constexpr auto operator!=(RetCode2::id_type const& lhs, RetCode2 const& rhs) -> bool;
}

#endif
