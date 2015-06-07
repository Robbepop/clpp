#ifndef CLPP_EXECUTION_STATUS_H
#define CLPP_EXECUTION_STATUS_H

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
