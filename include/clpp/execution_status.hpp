#ifndef CLPP_EXECUTION_STATUS_HPP
#define CLPP_EXECUTION_STATUS_HPP

#include "clpp/detail/common.hpp"

namespace cl {
	enum class ExecutionStatus : cl_int {
		queued    = CL_QUEUED,
		submitted = CL_SUBMITTED,
		running   = CL_RUNNING,
		complete  = CL_COMPLETE
	};
}

#endif
