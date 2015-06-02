#ifndef CLPP_SVM_CAPABILITIES_H
	#error "Do not include this file directly."
#endif

namespace cl {
	auto SvmCapabilities::supportsCoarseGrainBuffer() const -> cl_bool {
		return readMask<CL_DEVICE_SVM_COARSE_GRAIN_BUFFER>();
	}

	auto SvmCapabilities::supportsFineGrainBuffer() const -> cl_bool {
		return readMask<CL_DEVICE_SVM_FINE_GRAIN_BUFFER>();
	}

	auto SvmCapabilities::supportsFineGrainSystem() const -> cl_bool {
		return readMask<CL_DEVICE_SVM_FINE_GRAIN_SYSTEM>();
	}

	auto SvmCapabilities::supportsAtomics() const -> cl_bool {
		return readMask<CL_DEVICE_SVM_ATOMICS>();
	}
}
