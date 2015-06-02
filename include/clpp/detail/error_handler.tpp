#ifndef CLPP_DETAIL_ERROR_HANDLER_H
	#error "Do not include this file directly!"
#endif

#include "clpp/ret_code.hpp"
#include "clpp/exception.hpp"

#include <type_traits>
#include <map>

namespace cl {
	namespace detail {

		auto error::isError(code_type code) -> cl_bool {
			return code != CL_SUCCESS;
		}

		auto error::isError(RetCode code) -> cl_bool {
			return isError(static_cast<code_type>(code));
		}

		auto error::isSuccess(code_type code) -> cl_bool {
			return code == CL_SUCCESS;
		}

		auto error::isSuccess(RetCode code) -> cl_bool {
			return isSuccess(static_cast<code_type>(code));
		}

		template <typename ExceptionType>
		auto error::handle(
			RetCode code,
			error::info_map const* local_info_map
		)
			-> cl_bool
		{
			using namespace std::literals;
			static const auto global_info_map = info_map{
				{RetCode::outOfResources, "there was a failure to allocate resources required by the OpenCL implementation on the device."},
				{RetCode::outOfHostMemory, "there was a failure to allocate resources required by the OpenCL implementation on the host."}
			};
			if (isSuccess(code)) return CL_SUCCESS;
			if (local_info_map != nullptr) {
				const auto it = local_info_map->find(code);
				throw ExceptionType{code,
					it != local_info_map->end() ? it->second : ""s};
			}
			const auto it = global_info_map.find(code);
			throw ExceptionType{code,
				it != global_info_map.end() ? it->second : ""s};
		}

		template <typename ExceptionType>
		auto error::handle(
			error::code_type code,
			error::info_map const& local_info_map
		)
			-> cl_bool
		{
			return handle<ExceptionType>(
				static_cast<RetCode>(code),
				std::addressof(local_info_map));
		}

		template <typename ExceptionType>
		auto error::handle(error::code_type code) -> cl_bool {
			return handle<ExceptionType>(
				static_cast<RetCode>(code), nullptr);
		}
	}
}
