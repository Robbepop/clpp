#ifndef CLPP_SVM_CAPABILITIES_H
	#error "Do not include this file directly."
#endif

namespace cl {
	auto SvmCapabilities::supportsCoarseGrainBuffer() const -> bool {
		return readMask<CL_DEVICE_SVM_COARSE_GRAIN_BUFFER>();
	}

	auto SvmCapabilities::supportsFineGrainBuffer() const -> bool {
		return readMask<CL_DEVICE_SVM_FINE_GRAIN_BUFFER>();
	}

	auto SvmCapabilities::supportsFineGrainSystem() const -> bool {
		return readMask<CL_DEVICE_SVM_FINE_GRAIN_SYSTEM>();
	}

	auto SvmCapabilities::supportsAtomics() const -> bool {
		return readMask<CL_DEVICE_SVM_ATOMICS>();
	}
}
