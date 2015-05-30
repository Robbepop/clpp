#ifndef CLPP_TERMINATE_CAPABILITIES_H
#define CLPP_TERMINATE_CAPABILITIES_H

#include "clpp/detail/common.hpp"
#include "clpp/detail/mask_wrapper.hpp"

namespace cl {
	class TerminateCapabilities final :
		public detail::MaskWrapper<cl_device_terminate_capability_khr>
	{
	public:
		using detail::MaskWrapper<TerminateCapabilities::cl_mask_type>::MaskWrapper;

		auto supportsContextTermination() const -> cl_bool;
	};
}

#include "clpp/terminate_capabilities.tpp"
#endif
