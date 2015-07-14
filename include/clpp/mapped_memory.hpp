#ifndef CLPP_MAPPED_MEMORY_HPP
#define CLPP_MAPPED_MEMORY_HPP

namespace cl {
	template<typename T>
	class MappedMemory final {
	public:
		MappedMemory();
		MappedMemory(CommandQueue const& queue, MemObject const& mem, T* data, size_t size);

		~MappedMemory();

		template<typename EventRange>
		void setUnmapWaitList(EventRange const& waitList) const;

	//================================================================================
	// General getter for size and data information.
	//================================================================================
	public:

		auto data() -> T*;
		auto data() const -> T const*;

		auto size() const -> size_t;

	//================================================================================
	// Data getters checked and unchecked for MappedMemory objects.
	//================================================================================
	public:

		auto operator[](size_t index)       -> T &;
		auto operator[](size_t index) const -> T const&;

		auto at(size_t index)       -> T &;
		auto at(size_t index) const -> T const&;

		auto front()       -> T &;
		auto front() const -> T const&;

		auto back()       -> T &;
		auto back() const -> T const&;

	//================================================================================
	// Methods for iterator based access of the mapped memory.
	//================================================================================
	public:

		auto begin()        noexcept -> T*;
		auto begin()  const noexcept -> T const*;
		auto end()          noexcept -> T*;
		auto end()    const noexcept -> T const*;
		auto cbegin() const noexcept -> T const*;
		auto cend()   const noexcept -> T const*;

	//================================================================================
	// Helper methods for access to underlaying data.
	//================================================================================
	private:

		auto inline getQueueId() const -> cl_command_queue;
		auto inline getMemObjectId() const -> cl_mem;
		auto inline getDataAsVoidPtr() const -> void*;
		auto inline getWaitListData() const -> cl_event const*;
		auto inline getWaitListSize() const -> cl_uint;

	//================================================================================
	// Struct Members
	//================================================================================
	private:
		CommandQueue       m_queue;
		MemObject          m_mem_obj;
		T*                 m_data;
		size_t             m_size;
		bool               m_valid;
		std::vector<Event> m_wait_list;
	};
}

#endif
