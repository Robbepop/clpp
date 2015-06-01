#ifndef CLPP_MEMORY_CACHE_TYPE_H
#define CLPP_MEMORY_CACHE_TYPE_H

#include "clpp/detail/common.hpp"

namespace cl {
	enum class MemoryCacheType : cl_device_mem_cache_type {
		none           = CL_NONE,
		readOnlyCache  = CL_READ_ONLY_CACHE,
		readWriteCache = CL_READ_WRITE_CACHE
	};
}
#endif
