#ifdef  CLPP_CONTEXT_PROPERTIES_IPP
	#error "multiple inclusions of the same implementation file"
#else
#define CLPP_CONTEXT_PROPERTIES_IPP

#ifndef CLPP_CONTEXT_PROPERTIES_HPP
	#error "header file has not been included; maybe it isn't required anymore?"
	#include "clpp/context_properties.hpp"
#endif

namespace cl {
	auto ContextProperties::setPlatform(Platform platform) -> ContextProperties & {
		set(CL_CONTEXT_PLATFORM, platform.get());
		return *this;
	}

	auto ContextProperties::setInteropUserSync(cl_bool flag) -> ContextProperties & {
		set(CL_CONTEXT_INTEROP_USER_SYNC, flag);
		return *this;
	}

	auto ContextProperties::getPlatform() const -> Platform {
		return {get<cl_platform_id>(CL_CONTEXT_PLATFORM).value_or(nullptr)};
	}

	auto ContextProperties::getInteropUserSync() const -> bool {
		return get<cl_bool>(CL_CONTEXT_INTEROP_USER_SYNC).value_or(false);
	}
}

#endif
