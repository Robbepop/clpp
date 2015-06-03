#ifndef CLPP_EXECUTION_CAPABILITIES_H
	#error "Do not include this file directly."
#endif

namespace cl {
	auto ExecutionCapabilities::canExecuteKernel() const -> bool {
		return readMask<CL_EXEC_KERNEL>();
	}

	auto ExecutionCapabilities::canExecuteNativeKernel() const -> bool {
		return readMask<CL_EXEC_NATIVE_KERNEL>();
	}
}
