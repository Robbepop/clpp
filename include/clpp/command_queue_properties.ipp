#if defined(CL_VERSION_2_0)

#ifdef  CLPP_COMMAND_QUEUE_PROPERTIES_IPP
	#error "multiple inclusions of the same implementation file"
#else
#define CLPP_COMMAND_QUEUE_PROPERTIES_IPP

#ifndef CLPP_COMMAND_QUEUE_PROPERTIES_HPP
	#error "header file has not been included; maybe it isn't required anymore?"
	#include "clpp/command_queue_properties.hpp"
#endif

namespace cl {
	void CommandQueueProperties::setCommandQueueFlags(CommandQueueFlags flags) {
		set(CL_QUEUE_PROPERTIES, flags.mask());
	}

	auto CommandQueueProperties::getCommandQueueFlags() -> CommandQueueFlags {
		return get<CommandQueueFlags>(CL_QUEUE_PROPERTIES).
			value_or(CommandQueueFlags::null);
	}

	void CommandQueueProperties::setCommandQueueSize(cl_uint size) {
		set(CL_QUEUE_SIZE, size);
	}

	auto CommandQueueProperties::getCommandQueueSize() -> cl_uint {
		return get<cl_uint>(CL_QUEUE_SIZE).value_or(0);
	}
}

#endif // CLPP_COMMAND_QUEUE_PROPERTIES_IPP
#endif // defined(CL_VERSION_2_0)
