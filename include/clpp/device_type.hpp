#ifndef CLPP_DEVICE_TYPE_H
#define CLPP_DEVICE_TYPE_H

#include "clpp/detail/common.hpp"

namespace cl {
	enum class DeviceType : cl_device_type {
		#if defined(CL_VERSION_1_2)
			custom  = CL_DEVICE_TYPE_CUSTOM,
		#endif
		defaultType = CL_DEVICE_TYPE_DEFAULT,
		cpu         = CL_DEVICE_TYPE_CPU,
		gpu         = CL_DEVICE_TYPE_GPU,
		accelerator = CL_DEVICE_TYPE_ACCELERATOR,
		all         = CL_DEVICE_TYPE_ALL
	};
}

#endif
