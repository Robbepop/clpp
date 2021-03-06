#ifndef CLPP_MAP_ACCESS_HPP
#define CLPP_MAP_ACCESS_HPP

#include "clpp/detail/common.hpp"

namespace cl {
	enum class MapAccess : cl_map_flags {
		  read                  = CL_MAP_READ
		, write                 = CL_MAP_WRITE
		, readWrite             = CL_MAP_READ | CL_MAP_WRITE
	#if defined(CL_VERSION_1_2)
		, writeInvalidateRegion = CL_MAP_WRITE_INVALIDATE_REGION
	#endif
	};
}

#endif
