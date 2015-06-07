#ifndef CLPP_DEVICE_ACCESS_H
#define CLPP_DEVICE_ACCESS_H

#include "clpp/detail/common.hpp"

namespace cl {
	enum class DeviceAccess : cl_mem_flags {
		readWrite = CL_MEM_READ_WRITE,
		readOnly  = CL_MEM_READ_ONLY,
		writeOnly = CL_MEM_WRITE_ONLY
	};
}

#endif
