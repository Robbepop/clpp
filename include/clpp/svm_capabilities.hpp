#if defined(CL_VERSION_2_0)

#ifndef CLPP_SVM_CAPABILITIES_HPP
#define CLPP_SVM_CAPABILITIES_HPP

#include "clpp/detail/common.hpp"
#include "clpp/detail/mask_wrapper.hpp"

namespace cl {
	class SvmCapabilities final :
		public detail::MaskWrapper<cl_device_svm_capabilities>
	{
	public:
		using detail::MaskWrapper<SvmCapabilities::cl_mask_type>::MaskWrapper;

		auto inline supportsCoarseGrainBuffer() const -> bool;
		auto inline supportsFineGrainBuffer() const   -> bool;
		auto inline supportsFineGrainSystem() const   -> bool;
		auto inline supportsAtomics() const           -> bool;
	};
}

#endif // CLPP_SVM_CAPABILITIES_HPP
#endif // defined(CL_VERSION_2_0)
