#ifndef CLPP_BUFFER_H
#define CLPP_BUFFER_H

#include "clpp/mem_object.hpp"
#include "clpp/device_access.hpp"
#include "clpp/host_access.hpp"

namespace cl {
	template<typename T>
	class Buffer final : public MemObject {
	public:
		using MemObject::MemObject;

		using value_type = T;

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
		auto getAssociatedBuffer() const -> boost::optional<std::unique_ptr<Buffer<T>>>;
	};
}

#endif
