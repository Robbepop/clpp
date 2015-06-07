#ifndef CLPP_TRANSFER_MODE_H
#define CLPP_TRANSFER_MODE_H

#include "clpp/detail/common.hpp"

namespace cl {
	enum class TransferMode : cl_mem_flags {
		copy      = CL_MEM_COPY_HOST_PTR,
		alloc     = CL_MEM_ALLOC_HOST_PTR,
		use       = CL_MEM_USE_HOST_PTR,
		allocCopy = CL_MEM_COPY_HOST_PTR | CL_MEM_ALLOC_HOST_PTR
	};
}

#endif
