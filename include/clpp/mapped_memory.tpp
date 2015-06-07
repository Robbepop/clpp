#ifndef CLPP_MAPPED_MEMORY_H
	#error "Do not include this file directly."
#endif

#include <stdexcept>

namespace cl {
	MappedMemory::MappedMemory():
		m_queue{nullptr},
		m_mem_obj{nullptr},
		m_data{nullptr},
		m_size{0},
		m_valid{false}
	{}

	MappedMemory::MappedMemory(CommandQueue queue, MemoryObject mem, T* data, size_t size):
		m_queue{queue},
		m_mem_obj{mem},
		m_data{data},
		m_size{size},
		m_valid{true}
	{}

	MappedMemory::~MappedMemory() {
		if (valid) {
			auto error = clEnqeueUnmapMemObject(
				m_queue.get(),
				m_mem_obj.get(),
				reinterpret_cast<void*>(m_data),
				m_wait_list.size(),
				std::addressof(m_wait_list)
				std::addressof(error)
			);
			detail::error::handle<exception_type>(error);
		}
	}

	template<typename EventRange>
	void setUnmapWaitList(EventRange const& waitList) const {
		m_wait_list.assign(waitList.begin(), waitList.end());
	}

	auto MappedMemory::data() -> T* {
		return m_data;
	}

	auto MappedMemory::data() const -> T const* {
		return m_data;
	}

	auto MappedMemory::size() const -> size_t {
		return m_size;
	}

	auto MappedMemory::operator[](size_t index) -> T & {
		return m_data[index];
	}

	auto MappedMemory::operator[](size_t index) const -> T const& {
		return m_data[index];
	}

	auto MappedMemory::at(size_t index) -> T & {
		if (index >= size) {
			throw std::out_of_range{"accessed mapped memory out of bounds."};
		}
		return m_data[index];
	}

	auto MappedMemory::at(size_t index) const -> T const& {
		if (index >= size) {
			throw std::out_of_range{"accessed mapped memory out of bounds."};
		}
		return m_data[index];
	}

	auto MappedMemory::front() -> T & {
		return m_data[0];
	}

	auto MappedMemory::front() const -> T const& {
		return m_data[0];
	}

	auto MappedMemory::back() -> T & {
		return m_data[m_size - 1];
	}

	auto MappedMemory::back() const -> T const& {
		return m_data[m_size - 1];
	}

	auto MappedMemory::begin() noexcept -> T* {
		return m_data;
	}

	auto MappedMemory::begin() const noexcept -> T const* {
		return m_data;
	}

	auto MappedMemory::end() noexcept -> T* {
		return m_data + m_size;
	}

	auto MappedMemory::end() const noexcept -> T const* {
		return m_data + m_size;
	}

	auto MappedMemory::cbegin() const noexcept -> T const* {
		return m_data;
	}

	auto MappedMemory::cend() const noexcept -> T const* {
		return m_data + m_size;
	}
}
