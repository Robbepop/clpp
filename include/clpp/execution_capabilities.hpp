#ifndef CLPP_EXECUTION_CAPABILITIES_H
#define CLPP_EXECUTION_CAPABILITIES_H

#include "clpp/detail/common.hpp"
#include "clpp/detail/mask_wrapper.hpp"

namespace cl {
	class ExecutionCapabilities final :
		public detail::MaskWrapper<cl_device_exec_capabilities>
	{
	public:
		using detail::MaskWrapper<ExecutionCapabilities::cl_mask_type>::MaskWrapper;

		auto canExecuteKernel() const       -> cl_bool;
		auto canExecuteNativeKernel() const -> cl_bool;
	};
}

#include "clpp/execution_capabilities.tpp"
#endif
