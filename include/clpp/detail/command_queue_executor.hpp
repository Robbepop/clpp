#ifndef CLPP_COMMAND_QUEUE_EXECUTOR_H
#define CLPP_COMMAND_QUEUE_EXECUTOR_H

#include "clpp/nd_range.hpp"

#include <vector>

namespace cl {
	class CommandQueue;
	class Event;

	namespace detail {
		class CommandQueueExecutor final {
			friend class CommandQueue;

			//============================================================================
			// Helper methods to access members.
			//============================================================================
		private:

			auto getQueueId() const      -> cl_command_queue;
			auto getWaitListData() const -> cl_event const*;
			auto getWaitListSize() const -> cl_uint;

			// converts element count based arrays into byte based arrays
			template<typename T, size_t N>
			auto toByteArray(std::array<T,N> const& array) const -> std::array<T,N>;

			//============================================================================
			// Constructors and Assignment
			//============================================================================
		private:
			CommandQueueExecutor(CommandQueue const& queue);

			template<typename EventRange>
			CommandQueueExecutor(CommandQueue const& queue, EventRange const& waitList);

			CommandQueueExecutor(CommandQueueExecutor const& rhs) = delete;
			CommandQueueExecutor(CommandQueueExecutor && rhs)     = delete;

			auto operator=(CommandQueueExecutor const& rhs) = delete;
			auto operator=(CommandQueueExecutor && rhs)     = delete;

			//============================================================================
			// Overloads to access clEnqueueReadBuffer
			//============================================================================
		public:

			template<typename OutputIterator, typename T>
			void readBufferBlocked(Buffer<T> const& buffer, size_t offset,
				OutputIterator first, OutputIterator last) const;

			template<typename OutputIterator, typename T>
			void readBufferBlocked(Buffer<T> const& buffer, OutputIterator first) const;

			template<typename OutputIterator, typename T>
			auto readBuffer(Buffer<T> const& buffer, size_t offset,
				OutputIterator first, OutputIterator last) const -> Event;

			template<typename OutputIterator, typename T>
			auto readBuffer(Buffer<T> const& buffer, OutputIterator first) const -> Event;

			//============================================================================
			// Overloads to access clEnqueueWriteBuffer
			//============================================================================
		public:

			template<typename InputIterator, typename T>
			void writeBufferBlocked(Buffer<T> const& buffer, size_t offset,
				InputIterator first, InputIterator last) const;

			template<typename InputIterator, typename T>
			void writeBufferBlocked(Buffer<T> const& buffer, InputIterator first) const;

			template<typename InputIterator, typename T>
			auto writeBuffer(Buffer<T> const& buffer, size_t offset,
				InputIterator first, InputIterator last) const -> Event;

			template<typename InputIterator, typename T>
			auto writeBuffer(Buffer<T> const& buffer, InputIterator first) const -> Event;

			//============================================================================
			// Overloads to access clEnqueueReadBufferRect
			//============================================================================
		public:

			template<typename OutIterator, typename T>
			void readBufferRectBlocked(
				Buffer<T> const& buffer,
				std::array<size_t, 3> const& bufferOrigin,
				std::array<size_t, 3> const& hostOrigin,
				std::array<size_t, 3> const& region,
				size_t bufferRowPitch, size_t bufferSlicePitch,
				size_t hostRowPitch, size_t hostSlicePitch,
				OutIterator first) const;

			template<typename OutIterator, typename T>
			auto readBufferRect(
				Buffer<T> const& buffer,
				std::array<size_t, 3> const& bufferOrigin,
				std::array<size_t, 3> const& hostOrigin,
				std::array<size_t, 3> const& region,
				size_t bufferRowPitch, size_t bufferSlicePitch,
				size_t hostRowPitch, size_t hostSlicePitch,
				OutIterator first) const -> Event;

			//============================================================================
			// Overloads to access clEnqueueWriteBufferRect
			//============================================================================
		public:

			template<typename OutIterator, typename T>
			void writeBufferRectBlocked(
				Buffer<T> const& buffer,
				std::array<size_t, 3> const& bufferOrigin,
				std::array<size_t, 3> const& hostOrigin,
				std::array<size_t, 3> const& region,
				size_t bufferRowPitch, size_t bufferSlicePitch,
				size_t hostRowPitch, size_t hostSlicePitch,
				OutIterator out) const;

			template<typename OutIterator, typename T>
			auto writeBufferRect(
				Buffer<T> const& buffer,
				std::array<size_t, 3> const& bufferOrigin,
				std::array<size_t, 3> const& hostOrigin,
				std::array<size_t, 3> const& region,
				size_t bufferRowPitch, size_t bufferSlicePitch,
				size_t hostRowPitch, size_t hostSlicePitch,
				OutIterator out) const -> Event;

			//============================================================================
			// Overloads to access clEnqueueCopyBuffer
			//============================================================================
		public:

			template<typename T, typename V>
			auto copyBuffer(Buffer<T> const& src, Buffer<V> const& dst,
				size_t srcOffset, size_t dstOffset, size_t size) const -> Event;

			template<typename T, typename V>
			auto copyBuffer(Buffer<T> const& src, Buffer<V> const& dst) const -> Event;

			//============================================================================
			// Overloads to access clEnqueueCopyBufferRect
			//============================================================================
		public:

			template<typename T, typename V>
			auto copyBufferRect(
				Buffer<T> const& src, Buffer<V> const& dest,
				std::array<size_t, 3> const& srcOrigin,
				std::array<size_t, 3> const& dstOrigin,
				std::array<size_t, 3> const& region,
				size_t srcRowPitch, size_t srcSlicePitch,
				size_t dstRowPitch, size_t dstSlidePitch) const -> Event;

			//============================================================================
			// Overloads to access clEnqueueFillBuffer
			//============================================================================
		public:

			template<typename T>
			auto fillBuffer(Buffer<T> const& buffer, T const& value, size_t offset, size_t size) const
				-> Event;

			template<typename T>
			auto fillBuffer(Buffer<T> const& buffer, T const& value) const -> Event;

			//============================================================================
			// Overloads to access clEnqueueMapBuffer
			//============================================================================
		public:

			template<typename T>
			void mapBufferBlocked(Buffer<T> const& buffer, MapAccess access,
				size_t offset, size_t size, MappedMemory<T> & result) const;

			template<typename T>
			void mapBufferBlocked(
				Buffer<T> const& buffer, MapAccess access, MappedMemory<T> & result) const;

			template<typename T>
			auto mapBuffer(Buffer<T> const& buffer, MapAccess access,
				size_t offset, size_t size, MappedMemory<T> & result) const -> Event;

			template<typename T>
			auto mapBuffer(
				Buffer<T> const& buffer, MapAccess access, MappedMemory<T> & result
			) const -> Event;

			//============================================================================
			// ND Range Kernel Execution
			//============================================================================
		public:

			auto execute1DRange(
				Kernel const& kernel,
				size_t globalWorkOffset,
				size_t globalWorkSize,
				size_t localWorkSize
			) const -> Event;

			template<size_t N>
			auto executeNDRange(
				Kernel const& kernel,
				NDRange<N> const& globalWorkOffset,
				NDRange<N> const& globalWorkSize,
				NDRange<N> const& localWorkSize
			) const -> Event;

			//============================================================================
			// Wait (for events), Marker & Barrier and When for async calls
			//============================================================================
		public:

			template<typename EventRange>
			auto marker() const -> Event;

			template<typename EventRange>
			auto barrier() const -> Event;

			//============================================================================
			// Members
			//============================================================================
		private:
			CommandQueue const& m_queue;
			std::vector<Event>  m_wait_list;
		};
	}
}

#endif
