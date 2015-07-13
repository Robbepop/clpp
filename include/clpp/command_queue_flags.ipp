#ifdef  CLPP_COMMAND_QUEUE_FLAGS_IPP
	#error "multiple inclusions of the same implementation file"
#else
#define CLPP_COMMAND_QUEUE_FLAGS_IPP

#ifndef CLPP_COMMAND_QUEUE_FLAGS_HPP
	#error "header file has not been included; maybe it isn't required anymore?"
	#include "clpp/command_queue_flags.hpp"
#endif

namespace cl {
	auto CommandQueueFlags::isOutOfOrderExecModeEnabled() const -> bool {
		return readMask<CL_QUEUE_OUT_OF_ORDER_EXEC_MODE_ENABLE>();
	}

	auto CommandQueueFlags::isProfilingEnabled() const -> bool {		
		return readMask<CL_QUEUE_PROFILING_ENABLE>();
	}


	auto CommandQueueFlags::enableOutOfOrderExecMode() -> CommandQueueFlags & {
		modifyMask<CL_QUEUE_OUT_OF_ORDER_EXEC_MODE_ENABLE>(true);
		return *this;
	}

	auto CommandQueueFlags::enableProfiling() -> CommandQueueFlags & {
		modifyMask<CL_QUEUE_PROFILING_ENABLE>(true);
		return *this;
	}


	auto CommandQueueFlags::disableOutOfOrderExecMode() -> CommandQueueFlags & {
		modifyMask<CL_QUEUE_OUT_OF_ORDER_EXEC_MODE_ENABLE>(false);
		return *this;
	}

	auto CommandQueueFlags::disableProfiling() -> CommandQueueFlags & {
		modifyMask<CL_QUEUE_PROFILING_ENABLE>(false);
		return *this;
	}

}

#endif
