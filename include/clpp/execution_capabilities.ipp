#ifdef  CLPP_EXECUTION_CAPABILITIES_IPP
	#error "multiple inclusions of the same implementation file"
#else
#define CLPP_EXECUTION_CAPABILITIES_IPP

#ifndef CLPP_EXECUTION_CAPABILITIES_HPP
	#error "header file has not been included; maybe it isn't required anymore?"
	#include "clpp/execution_capabilities.hpp"
#endif

namespace cl {
	auto ExecutionCapabilities::canExecuteKernel() const -> bool {
		return readMask<CL_EXEC_KERNEL>();
	}

	auto ExecutionCapabilities::canExecuteNativeKernel() const -> bool {
		return readMask<CL_EXEC_NATIVE_KERNEL>();
	}
}

#endif
