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
		set(CL_QUEUE_PROPERTIES, static_cast<cl_list_type>(flags.mask()));
	}

	auto CommandQueueProperties::getCommandQueueFlags() -> CommandQueueFlags {
		return static_cast<CommandQueueFlags>(get(CL_QUEUE_PROPERTIES));
	}

	void CommandQueueProperties::setCommandQueueSize(cl_uint size) {
		set(CL_QUEUE_SIZE, static_cast<cl_list_type>(size));
	}

	auto CommandQueueProperties::getCommandQueueSize() -> cl_uint {
		return static_cast<cl_uint>(get(CL_QUEUE_SIZE));
	}
}

#endif
