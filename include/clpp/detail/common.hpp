#ifndef CLPP_DETAIL_COMMON_HPP
#define CLPP_DETAIL_COMMON_HPP

#if defined(__APPLE__)
	#include <OpenCL/opencl.h>
#else
	#include <CL/cl.h>
#endif

#undef CL_VERSION_2_0
#undef CL_VERSION_1_2

#endif
