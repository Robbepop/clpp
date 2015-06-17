#ifndef CLPP_DETAIL_INFORMATION_ACCESSOR_HPP
#define CLPP_DETAIL_INFORMATION_ACCESSOR_HPP

#include <vector>

namespace cl {
	namespace detail {
		namespace utility {
			template<typename T, typename ObjectIdType, typename InfoIdType, typename InfoFunc>
			auto getInfo(
				ObjectIdType objId,
				InfoIdType infoId,
				InfoFunc getInfo
			) -> T;

			template<typename T, typename ObjectIdType, typename InfoIdType, typename InfoFunc>
			auto getInfoVector(
				ObjectIdType objId,
				InfoIdType infoId,
				InfoFunc getInfo
			) -> std::vector<T>;

			template<typename ObjectIdType, typename InfoIdType, typename InfoFunc>
			auto getInfoString(
				ObjectIdType objId,
				InfoIdType infoId,
				InfoFunc getInfo
			) -> std::string;
		}
	}
}

#endif
