#ifndef CLPP_MAP_ACCESS_H
#define CLPP_MAP_ACCESS_H

#include "clpp/detail/common.hpp"

namespace cl {
	enum class MapAccess : cl_map_flags {
		read                  = CL_MAP_READ,
		write                 = CL_MAP_WRITE,
		readWrite             = CL_MAP_READ | CL_MAP_WRITE,
		writeInvalidateRegion = CL_MAP_WRITE_INVALIDATE_REGION
	};
}

#endif
