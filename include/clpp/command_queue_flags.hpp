#ifndef CLPP_COMMAND_QUEUE_FLAGS_HPP
#define CLPP_COMMAND_QUEUE_FLAGS_HPP

#include "clpp/detail/common.hpp"
#include "clpp/detail/mask_wrapper.hpp"

namespace cl {
	class CommandQueueFlags final :
		public detail::MaskWrapper<cl_command_queue_properties>
	{
	public:
		using detail::MaskWrapper<CommandQueueFlags::cl_mask_type>::MaskWrapper;

		auto inline isOutOfOrderExecModeEnabled() const -> bool;
		auto inline isProfilingEnabled() const          -> bool;

		auto inline enableOutOfOrderExecMode() -> CommandQueueFlags &;
		auto inline enableProfiling()          -> CommandQueueFlags &;

		auto inline disableOutOfOrderExecMode() -> CommandQueueFlags &;
		auto inline disableProfiling()          -> CommandQueueFlags &;
	};
}

#endif // CLPP_COMMAND_QUEUE_FLAGS_HPP
