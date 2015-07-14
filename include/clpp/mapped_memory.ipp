#ifdef  CLPP_MAPPED_MEMORY_IPP
	#error "multiple inclusions of the same implementation file"
#else
#define CLPP_MAPPED_MEMORY_IPP

#ifndef CLPP_MAPPED_MEMORY_HPP
	#error "header file has not been included; maybe it isn't required anymore?"
	#include "clpp/mapped_memory.hpp"
#endif

#include <stdexcept>

namespace cl {
	template<typename T>
	MappedMemory<T>::MappedMemory():
		m_queue{nullptr},
		m_mem_obj{nullptr},
		m_data{nullptr},
		m_size{0},
		m_valid{false}
	{}

	template<typename T>
	MappedMemory<T>::MappedMemory(CommandQueue const& queue, MemObject const& mem, T* data, size_t size):
		m_queue{queue},
		m_mem_obj{mem},
		m_data{data},
		m_size{size},
		m_valid{true}
	{}

	template<typename T>
	MappedMemory<T>::~MappedMemory() {
		if (m_valid) {
			auto error = clEnqueueUnmapMemObject(
				getQueueId(),
				getMemObjectId(),
				getDataAsVoidPtr(),
				getWaitListSize(),
				getWaitListData(),
				nullptr
			);
			detail::handleError(detail::CLFunction::clEnqueueUnmapMemObject(), error);
		}
	}

	template<typename T>
	template<typename EventRange>
	void MappedMemory<T>::setUnmapWaitList(EventRange const& waitList) const {
		m_wait_list.assign(waitList.begin(), waitList.end());
	}

	//================================================================================
	// General getter for size and data information.
	//================================================================================

	template<typename T>
	auto MappedMemory<T>::MappedMemory::data() -> T* {
		return m_data;
	}

	template<typename T>
	auto MappedMemory<T>::data() const -> T const* {
		return m_data;
	}

	template<typename T>
	auto MappedMemory<T>::size() const -> size_t {
		return m_size;
	}

	//================================================================================
	// Data getters checked and unchecked for MappedMemory objects.
	//================================================================================

	template<typename T>
	auto MappedMemory<T>::operator[](size_t index) -> T & {
		return m_data[index];
	}

	template<typename T>
	auto MappedMemory<T>::operator[](size_t index) const -> T const& {
		return m_data[index];
	}

	template<typename T>
	auto MappedMemory<T>::at(size_t index) -> T & {
		if (index >= m_size) {
			throw std::out_of_range{"accessed mapped memory out of bounds."};
		}
		return m_data[index];
	}

	template<typename T>
	auto MappedMemory<T>::at(size_t index) const -> T const& {
		if (index >= m_size) {
			throw std::out_of_range{"accessed mapped memory out of bounds."};
		}
		return m_data[index];
	}

	template<typename T>
	auto MappedMemory<T>::front() -> T & {
		return m_data[0];
	}

	template<typename T>
	auto MappedMemory<T>::front() const -> T const& {
		return m_data[0];
	}

	template<typename T>
	auto MappedMemory<T>::back() -> T & {
		return m_data[m_size - 1];
	}

	template<typename T>
	auto MappedMemory<T>::back() const -> T const& {
		return m_data[m_size - 1];
	}

	//================================================================================
	// Methods for iterator based access of the mapped memory.
	//================================================================================

	template<typename T>
	auto MappedMemory<T>::begin() noexcept -> T* {
		return m_data;
	}

	template<typename T>
	auto MappedMemory<T>::begin() const noexcept -> T const* {
		return m_data;
	}

	template<typename T>
	auto MappedMemory<T>::end() noexcept -> T* {
		return m_data + m_size;
	}

	template<typename T>
	auto MappedMemory<T>::end() const noexcept -> T const* {
		return m_data + m_size;
	}

	template<typename T>
	auto MappedMemory<T>::cbegin() const noexcept -> T const* {
		return m_data;
	}

	template<typename T>
	auto MappedMemory<T>::cend() const noexcept -> T const* {
		return m_data + m_size;
	}

	//================================================================================
	// Helper methods for access to underlaying data.
	//================================================================================

	template<typename T>
	auto MappedMemory<T>::getQueueId() const -> cl_command_queue {
		return reinterpret_cast<cl_command_queue>(m_queue);
	}

	template<typename T>
	auto MappedMemory<T>::getMemObjectId() const -> cl_mem {
		return reinterpret_cast<cl_mem>(m_mem_obj);
	}

	template<typename T>
	auto MappedMemory<T>::getDataAsVoidPtr() const -> void* {
		return reinterpret_cast<void*>(m_data);
	}

	template<typename T>
	auto MappedMemory<T>::getWaitListData() const -> cl_event const* {
		return reinterpret_cast<cl_event const*>(m_wait_list.data());
	}

	template<typename T>
	auto MappedMemory<T>::getWaitListSize() const -> cl_uint {
		return static_cast<cl_uint>(m_wait_list.size());
	}
}

#endif
