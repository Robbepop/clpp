#ifndef CLPP_BUILD_STATUS_HPP
#define CLPP_BUILD_STATUS_HPP

#include "clpp/detail/common.hpp"

namespace cl {
	enum class BuildStatus : cl_build_status {
		success    = CL_BUILD_SUCCESS,
		none       = CL_BUILD_NONE,
		error      = CL_BUILD_ERROR,
		inProgress = CL_BUILD_IN_PROGRESS
	};
}

#endif
