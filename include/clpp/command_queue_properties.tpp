#ifndef CLPP_COMMAND_QUEUE_PROPERTIES_H
	#error "Do not include this file directly."
#endif

namespace cl {
	auto CommandQueueProperties::isOutOfOrderExecModeEnabled() const -> bool {
		return readMask<CL_QUEUE_OUT_OF_ORDER_EXEC_MODE_ENABLE>();
	}

	auto CommandQueueProperties::isProfilingEnabled() const -> bool {		
		return readMask<CL_QUEUE_PROFILING_ENABLE>();
	}


	auto CommandQueueProperties::enableOutOfOrderExecMode() -> CommandQueueProperties & {
		modifyMask<CL_QUEUE_OUT_OF_ORDER_EXEC_MODE_ENABLE>(true);
		return *this;
	}

	auto CommandQueueProperties::enableProfiling() -> CommandQueueProperties & {
		modifyMask<CL_QUEUE_PROFILING_ENABLE>(true);
		return *this;
	}


	auto CommandQueueProperties::disableOutOfOrderExecMode() -> CommandQueueProperties & {
		modifyMask<CL_QUEUE_OUT_OF_ORDER_EXEC_MODE_ENABLE>(false);
		return *this;
	}

	auto CommandQueueProperties::disableProfiling() -> CommandQueueProperties & {
		modifyMask<CL_QUEUE_PROFILING_ENABLE>(false);
		return *this;
	}

}
