#ifndef CLPP_LOCAL_MEMORY_TYPE_HPP
#define CLPP_LOCAL_MEMORY_TYPE_HPP

#include "clpp/detail/common.hpp"

namespace cl {
	enum class LocalMemoryType : cl_device_local_mem_type {
		none   = CL_NONE,
		global = CL_GLOBAL,
		local  = CL_LOCAL
	};
}
#endif
