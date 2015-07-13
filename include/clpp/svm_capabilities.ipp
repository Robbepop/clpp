#if defined(CL_VERSION_2_0)

#ifdef  CLPP_SVM_CAPABILITIES_IPP
	#error "multiple inclusions of the same implementation file"
#else
#define CLPP_SVM_CAPABILITIES_IPP

#ifndef CLPP_SVM_CAPABILITIES_HPP
	#error "header file has not been included; maybe it isn't required anymore?"
	#include "clpp/svm_capabilities.hpp"
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

#endif // CLPP_SVM_CAPABILITIES_IPP
#endif // defined(CL_VERSION_2_0)
