#if defined(CL_VERSION_1_2)

#ifndef CLPP_ACCESS_QUALIFIER_HPP
#define CLPP_ACCESS_QUALIFIER_HPP

#include "clpp/detail/common.hpp"

namespace cl {
	enum class AccessQualifier : cl_kernel_arg_access_qualifier {
		  none      = CL_KERNEL_ARG_ACCESS_NONE
		, readOnly  = CL_KERNEL_ARG_ACCESS_READ_ONLY
		, writeOnly = CL_KERNEL_ARG_ACCESS_WRITE_ONLY
		, readWrite = CL_KERNEL_ARG_ACCESS_READ_WRITE
	};
}

#endif // CLPP_ACCESS_QUALIFIER_HPP
#endif // defined(CL_VERSION_1_2)
