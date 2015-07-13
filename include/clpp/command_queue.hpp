#ifndef CLPP_COMMAND_QUEUE_HPP
#define CLPP_COMMAND_QUEUE_HPP

#include "clpp/detail/command_queue_executor.hpp"

namespace cl {
	namespace detail {
		template<>
		struct ObjectHandler<cl_command_queue> final {
			using cl_type        = cl_command_queue;
			using info_type      = cl_command_queue_info;

			static constexpr auto retain  = clRetainCommandQueue;
			static constexpr auto release = clReleaseCommandQueue;
			static constexpr auto getInfo = clGetCommandQueueInfo;
		};
	}

	class CommandQueue final : public detail::Object<cl_command_queue> {
	public:
		//================================================================================
		// Constructors and Assignment
		//================================================================================

		using detail::Object<cl_type>::Object;

		auto inline operator=(const CommandQueue & rhs) -> CommandQueue &;

		//================================================================================
		// Returns the CommandQueueExecutor for non-delayed execution
		//================================================================================
	private:
		auto inline getExecutor() const -> detail::CommandQueueExecutor;

		//================================================================================
		// Overloads to access clEnqueueReadBuffer
		//================================================================================
	public:

		template<typename OutputIterator, typename T>
		void readBufferBlocked(
			Buffer<T> const& buffer, size_t offset,
			OutputIterator first, OutputIterator last
		) const;

		template<typename OutputIterator, typename T>
		void readBufferBlocked(
			Buffer<T> const& buffer, OutputIterator first, OutputIterator last
		) const;

		template<typename OutputIterator, typename T>
		auto readBuffer(
			Buffer<T> const& buffer, size_t offset,
			OutputIterator first, OutputIterator last
		) const -> Event;

		template<typename OutputIterator, typename T>
		auto readBuffer(
			Buffer<T> const& buffer, OutputIterator first, OutputIterator last
		) const -> Event;

		//================================================================================
		// Overloads to access clEnqueueWriteBuffer
		//================================================================================
	public:

		template<typename InputIterator, typename T>
		void writeBufferBlocked(
			Buffer<T> const& buffer, size_t offset,
			InputIterator first, InputIterator last
		) const;

		template<typename InputIterator, typename T>
		void writeBufferBlocked(
			Buffer<T> const& buffer, InputIterator first, InputIterator last
		) const;

		template<typename InputIterator, typename T>
		auto writeBuffer(
			Buffer<T> const& buffer, size_t offset,
			InputIterator first, InputIterator last
		) const -> Event;

		template<typename InputIterator, typename T>
		auto writeBuffer(
			Buffer<T> const& buffer, InputIterator first, InputIterator last
		) const -> Event;

		//================================================================================
		// Overloads to access clEnqueueReadBufferRect
		//================================================================================
	public:

		template<typename OutIterator, typename T>
		void readBufferRectBlocked(
			Buffer<T> const& buffer,
			std::array<size_t, 3> const& bufferOrigin,
			std::array<size_t, 3> const& hostOrigin,
			std::array<size_t, 3> const& region,
			size_t bufferRowPitch, size_t bufferSlicePitch,
			size_t hostRowPitch, size_t hostSlicePitch,
			OutIterator first
		) const;

		template<typename OutIterator, typename T>
		auto readBufferRect(
			Buffer<T> const& buffer,
			std::array<size_t, 3> const& bufferOrigin,
			std::array<size_t, 3> const& hostOrigin,
			std::array<size_t, 3> const& region,
			size_t bufferRowPitch, size_t bufferSlicePitch,
			size_t hostRowPitch, size_t hostSlicePitch,
			OutIterator first
		) const -> Event;

		//================================================================================
		// Overloads to access clEnqueueWriteBufferRect
		//================================================================================
	public:

		template<typename OutIterator, typename T>
		void writeBufferRectBlocked(
			Buffer<T> const& buffer,
			std::array<size_t, 3> const& bufferOrigin,
			std::array<size_t, 3> const& hostOrigin,
			std::array<size_t, 3> const& region,
			size_t bufferRowPitch, size_t bufferSlicePitch,
			size_t hostRowPitch, size_t hostSlicePitch,
			OutIterator out
		) const;

		template<typename OutIterator, typename T>
		auto writeBufferRect(
			Buffer<T> const& buffer,
			std::array<size_t, 3> const& bufferOrigin,
			std::array<size_t, 3> const& hostOrigin,
			std::array<size_t, 3> const& region,
			size_t bufferRowPitch, size_t bufferSlicePitch,
			size_t hostRowPitch, size_t hostSlicePitch,
			OutIterator out
		) const -> Event;

		//================================================================================
		// Overloads to access clEnqueueCopyBuffer
		//================================================================================
	public:

		template<typename T, typename V>
		auto copyBuffer(
			Buffer<T> const& src, Buffer<V> const& dst,
			size_t srcOffset, size_t dstOffset, size_t size
		) const -> Event;

		template<typename T, typename V>
		auto copyBuffer(
			Buffer<T> const& src, Buffer<V> const& dst
		) const -> Event;

		//================================================================================
		// Overloads to access clEnqueueCopyBufferRect
		//================================================================================
	public:

		template<typename T, typename V>
		auto copyBufferRect(
			Buffer<T> const& src, Buffer<V> const& dest,
			std::array<size_t, 3> const& srcOrigin,
			std::array<size_t, 3> const& dstOrigin,
			std::array<size_t, 3> const& region,
			size_t srcRowPitch, size_t srcSlicePitch,
			size_t dstRowPitch, size_t dstSlidePitch
		) const -> Event;

		//================================================================================
		// Overloads to access clEnqueueFillBuffer
		//================================================================================
	#if defined(CL_VERSION_1_2)
	public:

		template<typename T>
		auto fillBuffer(
			Buffer<T> const& buffer, T const& value, size_t offset, size_t size
		) const -> Event;

		template<typename T>
		auto fillBuffer(
			Buffer<T> const& buffer, T const& value
		) const -> Event;

	#endif // defined(CL_VERSION_1_2)

		//================================================================================
		// Overloads to access clEnqueueMapBuffer
		//================================================================================
	public:

		template<typename T>
		void mapBufferBlocked(
			Buffer<T> const& buffer, MapAccess access,
			size_t offset, size_t size, MappedMemory<T> & result
		) const;

		template<typename T>
		void mapBufferBlocked(
			Buffer<T> const& buffer, MapAccess access, MappedMemory<T> & result
		) const;

		template<typename T>
		auto mapBuffer(
			Buffer<T> const& buffer, MapAccess access,
			size_t offset, size_t size, MappedMemory<T> & result
		) const -> Event;

		template<typename T>
		auto mapBuffer(
			Buffer<T> const& buffer, MapAccess access,
			MappedMemory<T> & result
		) const -> Event;

		//============================================================================
		// Migration of Memory Objects
		//============================================================================
	#if defined(CL_VERSION_1_2)

		template<typename MemObjectsIterator>
		auto migrateMemObjectsToDevice(
			MemObjectsIterator first,
			MemObjectsIterator last,
			Migration flags = Migration::contents
		) const -> Event;

		template<typename MemObjectsIterator>
		auto migrateMemObjectsToHost(
			MemObjectsIterator first,
			MemObjectsIterator last,
			Migration flags = Migration::contents
		) const -> Event;

	#endif // defined(CL_VERSION_1_2)

		//================================================================================
		// ND Range Kernel Execution
		//================================================================================
	public:

		auto inline execute1DRange(
			Kernel const& kernel,
			size_t globalWorkOffset,
			size_t globalWorkSize,
			size_t localWorkSize
		) const -> Event;

		auto inline execute1DRange(
			Kernel const& kernel,
			size_t globalWorkSize,
			size_t localWorkSize
		) const -> Event;

		auto inline execute1DRange(
			Kernel const& kernel,
			size_t globalWorkSize
		) const -> Event;

		template<size_t N>
		auto executeNDRange(
			Kernel const& kernel,
			NDRange<N> const& globalWorkOffset,
			NDRange<N> const& globalWorkSize,
			NDRange<N> const& localWorkSize
		) const -> Event;

		//================================================================================
		// When API for async calls
		//================================================================================
	public:

		template<typename EventRange>
		auto when(EventRange const& waitList) const -> detail::CommandQueueExecutor;

		template<typename...Events>
		auto when(Events... events) const -> detail::CommandQueueExecutor;

		//================================================================================
		// Wait (for events), Marker & Barrier
		//================================================================================
	public:

	#if defined(CL_VERSION_1_2)
		auto inline marker() const -> Event;

		auto inline barrier() const -> Event;

	#else
		auto inline marker() const -> Event;

		void inline barrier() const;

		template<typename EventRange>
		void inline wait(EventRange const& waitList) const;

		template<typename... Events>
		void inline wait(Events... events) const;
	#endif

		//================================================================================
		// Flush & Finish
		//================================================================================
	public:

		void inline flush() const;
		void inline finish() const;

		//================================================================================
		// Information Getters
		//================================================================================
	public:

		auto inline getContext() const        -> Context;
		auto inline getDevice() const         -> Device;
		auto inline getReferenceCount() const -> cl_uint;
		auto inline getProperties() const     -> CommandQueueProperties;
		auto inline getSize() const           -> cl_uint; // the same as 'size()'
		auto inline size() const              -> cl_uint; // the same as 'getSize()'
	};
}

#endif
