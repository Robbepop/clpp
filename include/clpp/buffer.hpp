#ifndef CLPP_BUFFER_H
#define CLPP_BUFFER_H

#include "clpp/mem_object.hpp"

namespace cl {
	template<typename T>
	class Buffer final : public MemObject {
	public:
		using MemObject::MemObject;

		auto operator=(Buffer const& rhs) -> Buffer &;

		auto createSubBuffer(
			size_t origin, size_t size,
			DeviceAccess deviceAccess = DeviceAccess::readWrite,
			HostAccess hostAccess     = HostAccess::readWrite
		) const -> Buffer<T>;

		auto size() const           -> size_t;
		auto getSizeInBytes() const -> size_t;

		auto getSize() const    -> size_t;
		auto getOffset() const  -> size_t;

		auto getHostPtr() const -> T*;
		auto getAssociatedBuffer() const -> boost::optional<Buffer<T>>;
	};
}

#include "clpp/buffer.tpp"
#endif
