#ifndef CLPP_COMMAND_QUEUE_PROPERTIES_HPP
#define CLPP_COMMAND_QUEUE_PROPERTIES_HPP

#include "clpp/detail/common.hpp"
#include "clpp/detail/mask_wrapper.hpp"

namespace cl {
	class CommandQueueProperties final :
		public detail::MaskWrapper<cl_command_queue_properties>
	{
	public:
		using detail::MaskWrapper<CommandQueueProperties::cl_mask_type>::MaskWrapper;

		auto inline isOutOfOrderExecModeEnabled() const -> bool;
		auto inline isProfilingEnabled() const          -> bool;

		auto inline enableOutOfOrderExecMode() -> CommandQueueProperties &;
		auto inline enableProfiling()          -> CommandQueueProperties &;

		auto inline disableOutOfOrderExecMode() -> CommandQueueProperties &;
		auto inline disableProfiling()          -> CommandQueueProperties &;
	};
}

#endif
