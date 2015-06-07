#ifndef CLPP_MEM_OBJECT_FLAGS_H
	#error "Do not include this file directly."
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

	auto MemoryFlags::allowsHostReadOnly() -> bool {
		return readMask<CL_MEM_HOST_WRITE_ONLY>();
	}

	auto MemoryFlags::allowsHostWriteOnly() -> bool {
		return readMask<CL_MEM_HOST_READ_ONLY>();
	}

	auto MemoryFlags::allowsHostNoAccess() -> bool {
		return readMask<CL_MEM_HOST_NO_ACCESS>();
	}
}
