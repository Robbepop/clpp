#ifndef CLPP_SVM_CAPABILITIES_H
#define CLPP_SVM_CAPABILITIES_H

#include "clpp/detail/common.hpp"
#include "clpp/detail/mask_wrapper.hpp"

namespace cl {
	class SvmCapabilities final :
		public detail::MaskWrapper<cl_device_svm_capabilities>
	{
	public:
		using detail::MaskWrapper<SvmCapabilities::cl_mask_type>::MaskWrapper;

		auto supportsCoarseGrainBuffer() const -> bool;
		auto supportsFineGrainBuffer() const   -> bool;
		auto supportsFineGrainSystem() const   -> bool;
		auto supportsAtomics() const           -> bool;
	};
}

#endif
