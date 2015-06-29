#ifdef  CLPP_LOCAL_MEMORY_IPP
	#error "multiple inclusions of the same implementation file"
#else
#define CLPP_LOCAL_MEMORY_IPP

#ifndef CLPP_LOCAL_MEMORY_HPP
	#error "header file has not been included; maybe it isn't required anymore?"
	#include "clpp/local_memory.hpp"
#endif

namespace cl {
	template<typename T>
	LocalMemory<T>::LocalMemory(size_t size):
		m_size{size}
	{}

	template<typename T>
	auto LocalMemory<T>::size() const -> size_t {
		return m_size;
	}

	template<typename T>
	auto LocalMemory<T>::getSize() const -> size_t {
		return m_size;
	}

	template<typename T>
	auto LocalMemory<T>::getSizeInBytes() const -> size_t {
		return m_size * sizeof(T);
	}
}

#endif
