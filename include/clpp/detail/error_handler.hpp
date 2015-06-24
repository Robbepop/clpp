#ifndef CLPP_DETAIL_ERROR_HANDLER_HPP
#define CLPP_DETAIL_ERROR_HANDLER_HPP

#include "clpp/ret_code.hpp"
#include "clpp/ret_code2.hpp"
#include "clpp/exception.hpp"

#include <type_traits>
#include <map>
#include <experimental/string_view>

namespace cl {
	namespace detail {
		namespace impl { // strange errors occur when naming this namespace 'detail'
			inline void throwException(CLFunction const& func, RetCode2 const& code);
		}
		inline auto handleError(CLFunction const& func, RetCode2 const& code) -> bool;

		class error final {
		public:
			using info_map = std::map<RetCode, std::string>;

		private:
			//============================================================================
			// Helper methods to check whether a return code is
			// an error or a success return value.
			//============================================================================
			using code_type = std::underlying_type<RetCode>::type;

			static inline auto isError(code_type code) -> bool;
			static inline auto isError(RetCode code)   -> bool;

			static inline auto isSuccess(code_type code) -> bool;
			static inline auto isSuccess(RetCode code)   -> bool;

			static inline void throwException(cl::RetCode code);

			//============================================================================
			// Error handler functions and their overloads in order
			// to centralize the error handling mechanism and throwing
			// of exceptions.
			//
			// There are the following handler overloads:
			//     - handle(code_type code)
			//     - handle(code_type code, const info_map & error_info)
			//     - handle(RetCode code, const info_map * error_info)
			//
			// Whereas the first two helper methods forward their
			// arguments to the third handle function.
			//============================================================================

			static inline auto handle(RetCode   code, info_map const* local_info_map) -> bool;

		public:
			static inline auto handle(code_type code, info_map const& local_info_map) -> bool;

			static inline auto handle(code_type code) -> bool;
		};
	}
}

#endif
