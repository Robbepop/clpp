#ifndef CLPP_DETAIL_ERROR_HANDLER_HPP
#define CLPP_DETAIL_ERROR_HANDLER_HPP

#include "clpp/ret_code.hpp"
#include "clpp/exception.hpp"

#include <type_traits>
#include <map>
#include <experimental/string_view>

namespace cl {
	namespace detail {
		namespace impl { // strange errors occur when naming this namespace 'detail'
			inline void throwException(CLFunction const& func, RetCode const& code);
		}

		template<typename CLFunctionPtr>
		auto handleError(CLFunctionPtr funcPtr, RetCode const& code) -> bool;

		inline auto handleError(CLFunction const& func, RetCode const& code) -> bool;

		inline auto handleError(RetCode const& code) -> bool;
	}
}

#endif
