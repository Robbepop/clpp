#ifndef CLPP_DETAIL_GET_INFO_HELPER_H
	#error "Do not include this file directly!"
#endif

#include "clpp/detail/common.hpp"
#include "clpp/detail/error_handler.hpp"

#include <vector>

namespace cl {
	namespace detail {
		template<typename T, typename ObjectIdType, typename InfoIdType, typename InfoFunc>
		auto getInfo(
			ObjectIdType objId,
			InfoIdType infoId,
			InfoFunc getInfo
		)
			-> T
		{
			auto error = cl_int{CL_INVALID_VALUE};
			auto info  = T{};
			error      = getInfo(objId, infoId, sizeof(T), std::addressof(info), nullptr);
			error::handle(error);
			return info;
		}

		template<typename T, typename ObjectIdType, typename InfoIdType,
			typename InfoFunc, typename BufferSizeType = size_t>
		auto getInfoVector(
			ObjectIdType objId,
			InfoIdType infoId,
			InfoFunc getInfo,
			bool countElementWise
		)
			-> std::vector<T>
		{
			auto error      = cl_int{CL_INVALID_VALUE};
			auto bufferSize = BufferSizeType{0};
			error           = getInfo(objId, infoId, 0, nullptr, std::addressof(bufferSize));
			error::handle(error);
			auto countElems = countElementWise ? bufferSize : bufferSize / sizeof(T);
			auto info = std::vector<T>(countElems);
			error = getInfo(objId, infoId, bufferSize, info.data(), nullptr);
			error::handle(error);
			return info;
		}

		template<typename InfoFunc, typename ObjectIdType, typename InfoIdType>
		auto getInfoString(
			ObjectIdType objId,
			InfoIdType infoId,
			InfoFunc getInfo,
			bool countElementWise
		)
			-> std::string
		{
			const auto info = getInfoVector<char>(
				objId, infoId, getInfo, countElementWise);
			return {info.begin(), info.end()};
		}
	}
}
