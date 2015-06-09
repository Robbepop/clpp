#ifndef CLPP_BUFFER_H
	#error "Do not include this file directly."
#endif

namespace cl {
	template<typename T>
	auto Buffer<T>::operator=(Buffer<T> const& rhs) -> Buffer & {
		if (this != &rhs) {
		    MemObject::operator=(rhs);
		}
		return *this;
	}

	template<typename T>
	auto Buffer<T>::createSubBuffer(
		size_t origin, size_t size,
		DeviceAccess deviceAccess,
		HostAccess hostAccess
	) const -> Buffer<T> {
		using namespace utility;
		auto error = cl_int{CL_INVALID_VALUE};
		auto flags = to_underlying(deviceAccess)
		           | to_underlying(hostAccess);
		auto region   = cl_buffer_region{origin, size};
		auto bufferId = clCreateSubBuffer(get(), flags,
			CL_BUFFER_CREATE_TYPE_REGION, std::addressof(region), std::addressof(error));
		detail::error::handle(error);
		return {bufId};
	}

	template<typename T>
	auto Buffer<T>::size() const -> size_t {
		return getSize();
	}

	template<typename T>
	auto Buffer<T>::getSize() const -> size_t {
		return MemObject::getSize() / sizeof(T);
	}

	template<typename T>
	auto Buffer<T>::getOffset() const -> size_t {
		return MemObject::size() / sizeof(T);
	}

	template<typename T>
	auto Buffer<T>::getHostPtr() const -> T* {
		return reinterpret_cast<T*>(MemObject::getHostPtr());
	}

	template<typename T>
	auto Buffer<T>::getAssociatedBuffer() const -> boost::optional<Buffer<T>> {
		return static_cast<boost::optional<Buffer<T>>>(MemObject::getAssociatedMemObject());
	}
}
