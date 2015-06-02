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

		auto supportsCoarseGrainBuffer() const -> cl_bool;
		auto supportsFineGrainBuffer() const   -> cl_bool;
		auto supportsFineGrainSystem() const   -> cl_bool;
		auto supportsAtomics() const            -> cl_bool;
	};
}

#include "clpp/svm_capabilities.tpp"
#endif
