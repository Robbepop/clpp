#ifdef  CLPP_DETAIL_INFORMATION_ACCESSOR_IPP
	#error "multiple inclusions of the same implementation file"
#else
#define CLPP_DETAIL_INFORMATION_ACCESSOR_IPP

#ifndef CLPP_DETAIL_INFORMATION_ACCESSOR_HPP
	#error "header file has not been included; maybe it isn't required anymore?"
	#include "clpp/detail/information_accessor.hpp"
#endif

#include "clpp/detail/common.hpp"
#include "clpp/detail/error_handler.hpp"

#include <vector>

namespace cl {
	namespace detail {
		namespace utility {
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

			template<typename T, typename ObjectIdType, typename InfoIdType, typename InfoFunc>
			auto getInfoVector(
				ObjectIdType objId,
				InfoIdType infoId,
				InfoFunc getInfo
			)
				-> std::vector<T>
			{
				auto error      = cl_int{CL_INVALID_VALUE};
				auto bufferSize = size_t{0};
				error           = getInfo(objId, infoId, 0, nullptr, std::addressof(bufferSize));
				error::handle(error);
				if (bufferSize == 0) { return {}; }
				auto countElems = bufferSize / sizeof(T);
				auto info = std::vector<T>(countElems);
				error = getInfo(objId, infoId, bufferSize, info.data(), nullptr);
				error::handle(error);
				return info;
			}

			template<typename ObjectIdType, typename InfoIdType, typename InfoFunc>
			auto getInfoString(
				ObjectIdType objId,
				InfoIdType infoId,
				InfoFunc getInfo
			)
				-> std::string
			{
				const auto info = getInfoVector<char>(objId, infoId, getInfo);
				return {info.begin(), info.end()};
			}
		}
	}
}

#endif
