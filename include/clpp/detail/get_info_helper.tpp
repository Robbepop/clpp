#ifndef CLPP_DETAIL_GET_INFO_HELPER_H
	#error "Do not include this file directly!"
#endif

#include "clpp/detail/common.hpp"
#include "clpp/detail/error_handler.hpp"

#include <vector>

namespace cl {
	namespace detail {
		template<typename ReturnType, typename ObjectIdType, typename InfoIdType, typename InfoFunc>
		auto getInfo(
			ObjectIdType p_id,
			InfoIdType info_id,
			InfoFunc get_info
		)
			-> ReturnType
		{
			static const auto errors = error::info_map{
				{RetCode::invalidValue, "invalid use of getInfo function; OR invalid information queried."}
			};
			auto error = cl_int{CL_INVALID_VALUE};
			auto info  = ReturnType{};
			error      = get_info(p_id, info_id, sizeof(ReturnType), std::addressof(info), nullptr);
			error::handle<typename ObjectHandler<ObjectIdType>::exception_type>(error, errors);
			return info;
		}

		template<typename ReturnType, typename ObjectIdType, typename InfoIdType, typename InfoFunc>
		auto getInfoVector(
			ObjectIdType m_id,
			InfoIdType info_id,
			InfoFunc get_info,
			bool count_element_wise
		)
			-> std::vector<ReturnType>
		{
			static const auto errors = error::info_map{
				{RetCode::invalidValue, "invalid use of getInfo function; OR invalid information queried."}
			};
			auto error       = cl_int{CL_INVALID_VALUE};
			auto buffer_size = cl_uint{0};
			error            = get_info(m_id, info_id, 0, nullptr, std::addressof(buffer_size));
			error::handle<typename ObjectHandler<ObjectIdType>::exception_type>(error, errors);
			auto count_elems = count_element_wise ? buffer_size : buffer_size / sizeof(ReturnType);
			auto info = std::vector<ReturnType>(count_elems);
			error = get_info(m_id, info_id, buffer_size, info.data(), nullptr);
			error::handle<typename ObjectHandler<ObjectIdType>::exception_type>(error, errors);
			return info;
		}

		template<typename ObjectIdType, typename InfoIdType, typename InfoFunc>
		auto getInfoString(
			ObjectIdType m_id,
			InfoIdType info_id,
			InfoFunc get_info,
			bool count_element_wise
		)
			-> std::string
		{
			auto info = getInfoVector<char, ObjectIdType, InfoIdType, InfoFunc>(
				m_id, info_id, get_info, count_element_wise);
			return {info.begin(), info.end()};
		}
	}
}
