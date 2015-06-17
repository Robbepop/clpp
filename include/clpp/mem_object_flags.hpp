#ifndef CLPP_MEM_OBJECT_FLAGS_HPP
#define CLPP_MEM_OBJECT_FLAGS_HPP

#include "clpp/detail/mask_wrapper.hpp"

namespace cl {
	class MemoryFlags : public detail::MaskWrapper<cl_mem_flags> {
	public:
		using detail::MaskWrapper<MemoryFlags::cl_mask_type>::MaskWrapper;

		auto allowsReadWrite() -> bool;
		auto allowsReadOnly()  -> bool;
		auto allowsWriteOnly() -> bool;

		auto useHostPtr()   -> bool;
		auto allocHostPtr() -> bool;
		auto copyHostPtr()  -> bool;

		auto allowsHostReadOnly()  -> bool;
		auto allowsHostWriteOnly() -> bool;
		auto allowsHostNoAccess()  -> bool;
	};
}

#endif
