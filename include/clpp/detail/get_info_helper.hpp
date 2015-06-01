#ifndef CLPP_DETAIL_GET_INFO_HELPER_H
#define CLPP_DETAIL_GET_INFO_HELPER_H

#include <vector>

namespace cl {
	namespace detail {
		template<typename ReturnType, typename ObjectIdType, typename InfoIdType, typename InfoFunc>
		auto getInfo(
			ObjectIdType p_id,
			InfoIdType info_id,
			InfoFunc get_info
		) -> ReturnType;

		template<typename ReturnType, typename ObjectIdType, typename InfoIdType, typename InfoFunc>
		auto getInfoVector(
			ObjectIdType m_id,
			InfoIdType info_id,
			InfoFunc get_info,
			bool count_element_wise = true
		) -> std::vector<ReturnType>;

		template<typename ObjectIdType, typename InfoIdType, typename InfoFunc>
		auto getInfoString(
			ObjectIdType m_id,
			InfoIdType info_id,
			InfoFunc get_info,
			bool count_element_wise = false
		) -> std::string;
	}
}

#include "clpp/detail/get_info_helper.tpp"
#endif
