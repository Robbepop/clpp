#ifndef CLPP_HOST_ACCESS_HPP
#define CLPP_HOST_ACCESS_HPP

#include "clpp/detail/common.hpp"

namespace cl {
	enum class HostAccess : cl_mem_flags {
		  readWrite = 0
	#if defined(CL_VERSION_1_2)
		, readOnly  = CL_MEM_HOST_READ_ONLY
		, writeOnly = CL_MEM_HOST_WRITE_ONLY
		, noAccess  = CL_MEM_HOST_NO_ACCESS
	#endif // defined(CL_VERSION_1_2)
	};
}

#endif
