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

		auto isOutOfOrderExecModeEnabled() const -> bool;
		auto isProfilingEnabled() const          -> bool;

		auto enableOutOfOrderExecMode() -> CommandQueueProperties &;
		auto enableProfiling()          -> CommandQueueProperties &;

		auto disableOutOfOrderExecMode() -> CommandQueueProperties &;
		auto disableProfiling()          -> CommandQueueProperties &;
	};
}

#endif
