#ifndef CLPP_BUFFER_H
	#error "Do not include this file directly."
#endif

namespace cl {
	template<typename T>
	Buffer & Buffer<T>::operator=(Buffer<T> const& rhs) {
		if (this != &rhs) {
		    MemObject::operator=(rhs);
		}
		return *this;
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
