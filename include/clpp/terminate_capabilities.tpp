#ifndef CLPP_TERMINATE_CAPABILITIES_H
	#error "Do not include this file directly."
#endif

namespace cl {
	auto TerminateCapabilities::supportsContextTermination() const -> cl_bool {
		return readMask<CL_DEVICE_TERMINATE_CAPABILITY_CONTEXT_KHR>();
	}
}
