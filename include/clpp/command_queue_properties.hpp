#if defined(CL_VERSION_2_0)

#ifndef CLPP_COMMAND_QUEUE_PROPERTIES_HPP
#define CLPP_COMMAND_QUEUE_PROPERTIES_HPP

#include "clpp/detail/common.hpp"
#include "clpp/detail/property_list_wrapper.hpp"
#include "clpp/command_queue_flags.hpp"

namespace cl {
	class CommandQueueProperties final :
		public detail::PropertyListWrapper<cl_queue_properties>
	{
	public:
		using detail::PropertyListWrapper<
			CommandQueueProperties::cl_list_type>::PropertyListWrapper;

		void setCommandQueueFlags(CommandQueueFlags flags);
		auto getCommandQueueFlags() -> CommandQueueFlags;

		void setCommandQueueSize(cl_uint size);
		auto getCommandQueueSize() -> cl_uint;
	};
}

#endif // CLPP_COMMAND_QUEUE_PROPERTIES_HPP
#endif // defined(CL_VERSION_2_0)
