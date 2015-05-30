#ifndef CLPP_LOCAL_MEMORY_TYPE_H
#define CLPP_LOCAL_MEMORY_TYPE_H

#include "clpp/detail/common.hpp"

namespace cl {
	enum class LocalMemoryType : cl_device_local_mem_type {
		global = CL_GLOBAL,
		local = CL_LOCAL
	};
}
#endif
