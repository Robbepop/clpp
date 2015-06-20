#ifndef CLPP_MEM_OBJECT_FLAGS_HPP
#define CLPP_MEM_OBJECT_FLAGS_HPP

#include "clpp/detail/mask_wrapper.hpp"

namespace cl {
	class MemoryFlags : public detail::MaskWrapper<cl_mem_flags> {
	public:
		using detail::MaskWrapper<MemoryFlags::cl_mask_type>::MaskWrapper;

		auto inline allowsReadWrite() -> bool;
		auto inline allowsReadOnly()  -> bool;
		auto inline allowsWriteOnly() -> bool;

		auto inline useHostPtr()   -> bool;
		auto inline allocHostPtr() -> bool;
		auto inline copyHostPtr()  -> bool;

		auto inline allowsHostReadOnly()  -> bool;
		auto inline allowsHostWriteOnly() -> bool;
		auto inline allowsHostNoAccess()  -> bool;
	};
}

#endif
