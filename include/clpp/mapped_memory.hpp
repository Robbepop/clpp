#ifndef CLPP_MAPPED_MEMORY_H
#define CLPP_MAPPED_MEMORY_H

namespace cl {
	template<typename T>
	class MappedMemory final {
	public:
		MappedMemory();
		MappedMemory(CommandQueue const& queue, MemoryObject const& mem, T* data, size_t size);

		~MappedMemory();

		template<typename EventRange>
		void setUnmapWaitList(EventRange const& waitList) const;

		auto data() -> T*;
		auto data() const -> T const*;

		auto size() const -> size_t;

		auto operator[](size_t index)       -> T &;
		auto operator[](size_t index) const -> T const&;

		auto at(size_t index)       -> T &;
		auto at(size_t index) const -> T const&;

		auto front()       -> T &;
		auto front() const -> T const&;

		auto back()       -> T &;
		auto back() const -> T const&;

		auto begin()        noexcept -> T*;
		auto begin()  const noexcept -> T const*;
		auto end()          noexcept -> T*;
		auto end()    const noexcept -> T const*;
		auto cbegin() const noexcept -> T const*;
		auto cend()   const noexcept -> T const*;

	private:
		CommandQueue       m_queue;
		MemoryObject       m_mem_obj;
		T*                 m_data;
		size_t             m_size;
		bool               m_valid;
		std::vector<Event> m_wait_list;
	};
}

#endif
