#ifdef  CLPP_MEM_OBJECT_FLAGS_IPP
	#error "multiple inclusions of the same implementation file"
#else
#define CLPP_MEM_OBJECT_FLAGS_IPP

#ifndef CLPP_MEM_OBJECT_FLAGS_HPP
	#error "header file has not been included; maybe it isn't required anymore?"
	#include "clpp/mem_object_flags.hpp"
#endif

namespace cl {
	auto MemoryFlags::allowsReadWrite() -> bool {
		return readMask<CL_MEM_READ_WRITE>();
	}

	auto MemoryFlags::allowsReadOnly() -> bool {
		return readMask<CL_MEM_READ_ONLY>();
	}

	auto MemoryFlags::allowsWriteOnly() -> bool {
		return readMask<CL_MEM_WRITE_ONLY>();
	}

	auto MemoryFlags::useHostPtr() -> bool {
		return readMask<CL_MEM_USE_HOST_PTR>();
	}

	auto MemoryFlags::allocHostPtr() -> bool {
		return readMask<CL_MEM_ALLOC_HOST_PTR>();
	}

	auto MemoryFlags::copyHostPtr() -> bool {
		return readMask<CL_MEM_COPY_HOST_PTR>();
	}

	auto MemoryFlags::allowsHostReadWrite() -> bool {
	#if defined(CL_VERSION_1_2)
		return !allowsHostReadOnly() && !allowsHostWriteOnly() && !allowsHostNoAccess();
	#else
		return true;
	#endif
	}

#if defined(CL_VERSION_1_2)
	auto MemoryFlags::allowsHostReadOnly() -> bool {
		return readMask<CL_MEM_HOST_WRITE_ONLY>();
	}

	auto MemoryFlags::allowsHostWriteOnly() -> bool {
		return readMask<CL_MEM_HOST_READ_ONLY>();
	}

	auto MemoryFlags::allowsHostNoAccess() -> bool {
		return readMask<CL_MEM_HOST_NO_ACCESS>();
	}
#endif // defined(CL_VERSION_1_2)
}

#endif
