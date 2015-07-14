#ifndef CLPP_MEM_OBJECT_TYPE_HPP
#define CLPP_MEM_OBJECT_TYPE_HPP

#include "clpp/detail/common.hpp"

namespace cl {
	enum class MemObjectType {
		  buffer        = CL_MEM_OBJECT_BUFFER
	#if defined(CL_VERSION_2_0)
		, pipe          = CL_MEM_OBJECT_PIPE
	#endif // defined(CL_VERSION_2_0)
		, image2D       = CL_MEM_OBJECT_IMAGE2D
		, image3D       = CL_MEM_OBJECT_IMAGE3D
	#if defined(CL_VERSION_1_2)
		, image2DArray  = CL_MEM_OBJECT_IMAGE2D_ARRAY
		, image1D       = CL_MEM_OBJECT_IMAGE1D
		, image1DArray  = CL_MEM_OBJECT_IMAGE1D_ARRAY
		, image1DBuffer = CL_MEM_OBJECT_IMAGE1D_BUFFER
	#endif // defined(CL_VERSION_1_2)
	};
}

#endif
