#ifndef CLPP_CONTEXT_PROPERTIES_HPP
#define CLPP_CONTEXT_PROPERTIES_HPP

#include "clpp/detail/common.hpp"
#include "clpp/detail/property_list_wrapper.hpp"

namespace cl {
	class Platform;

	class ContextProperties final
		: public detail::PropertyListWrapper<cl_context_properties>
	{
	public:
		using detail::PropertyListWrapper<
			ContextProperties::cl_list_type>::PropertyListWrapper;

		auto inline setPlatform(Platform platform) -> ContextProperties &;
		auto inline getPlatform() const        -> Platform;

	#if defined(CL_VERSION_1_2)
		auto inline setInteropUserSync(cl_bool flag) -> ContextProperties &;
		auto inline getInteropUserSync() const -> bool;
	#endif // defined(CL_VERSION_1_2)
	};
}

#endif
