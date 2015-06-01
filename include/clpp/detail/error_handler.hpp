#ifndef CLPP_DETAIL_ERROR_HANDLER_H
#define CLPP_DETAIL_ERROR_HANDLER_H

#include "clpp/ret_code.hpp"
#include "clpp/exception.hpp"

#include <type_traits>
#include <map>
#include <experimental/string_view>

namespace cl {
	namespace detail {
		class error final {
		public:
			using info_map = std::map<RetCode, std::experimental::string_view>;

		private:
			//============================================================================
			// Helper methods to check whether a return code is
			// an error or a success return value.
			//============================================================================
			using code_type = std::underlying_type<RetCode>::type;

			static auto isError(code_type code) -> cl_bool;
			static auto isError(RetCode code)   -> cl_bool;

			static auto isSuccess(code_type code) -> cl_bool;
			static auto isSuccess(RetCode code)   -> cl_bool;

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

			template <typename ExceptionType>
			static auto handle(RetCode   code, info_map const* local_info_map) -> cl_bool;

		public:
			template <typename ExceptionType>
			static auto handle(code_type code, info_map const& local_info_map) -> cl_bool;

			template <typename ExceptionType>
			static auto handle(code_type code) -> cl_bool;
		};
	}
}

#include "clpp/detail/error_handler.tpp"
#endif
