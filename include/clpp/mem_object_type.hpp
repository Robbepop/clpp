#ifndef CLPP_MEM_OBJECT_TYPE_HPP
#define CLPP_MEM_OBJECT_TYPE_HPP

#include "clpp/detail/common.hpp"

namespace cl {
	enum class MemObjectType {
		buffer        = CL_MEM_OBJECT_BUFFER,
		pipe          = CL_MEM_OBJECT_PIPE,
		image2D       = CL_MEM_OBJECT_IMAGE2D,
		image3D       = CL_MEM_OBJECT_IMAGE3D,
		image2DArray  = CL_MEM_OBJECT_IMAGE2D_ARRAY,
		image1D       = CL_MEM_OBJECT_IMAGE1D,
		image1DArray  = CL_MEM_OBJECT_IMAGE1D_ARRAY,
		image1DBuffer = CL_MEM_OBJECT_IMAGE1D_BUFFER
	};
}

#endif
