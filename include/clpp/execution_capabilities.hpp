#ifndef CLPP_EXECUTION_CAPABILITIES_HPP
#define CLPP_EXECUTION_CAPABILITIES_HPP

#include "clpp/detail/common.hpp"
#include "clpp/detail/mask_wrapper.hpp"

namespace cl {
	class ExecutionCapabilities final :
		public detail::MaskWrapper<cl_device_exec_capabilities>
	{
	public:
		using detail::MaskWrapper<ExecutionCapabilities::cl_mask_type>::MaskWrapper;

		auto inline canExecuteKernel() const       -> bool;
		auto inline canExecuteNativeKernel() const -> bool;
	};
}

#endif
