#ifdef  CLPP_COMMAND_QUEUE_PROPERTIES_IPP
	#error "multiple inclusions of the same implementation file"
#else
#define CLPP_COMMAND_QUEUE_PROPERTIES_IPP

#ifndef CLPP_COMMAND_QUEUE_PROPERTIES_HPP
	#error "header file has not been included; maybe it isn't required anymore?"
	#include "clpp/command_queue_properties.hpp"
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

#endif
