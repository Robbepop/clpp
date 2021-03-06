#ifndef CLPP_DETAIL_COMMAND_QUEUE_EXECUTOR_HPP
#define CLPP_DETAIL_COMMAND_QUEUE_EXECUTOR_HPP

#include "clpp/nd_range.hpp"
#include "clpp/buffer.hpp"
#include "clpp/migration.hpp"
#include "clpp/map_access.hpp"
#include "clpp/kernel.hpp"

#include "clpp/utility/concepts.hpp"

#include <vector>

namespace cl {
	template<typename> class MappedMemory;
	class CommandQueue;
	class Event;

	namespace detail {
		class CommandQueueExecutor final {

			//============================================================================
			// Helper methods to access members.
			//============================================================================
		private:

			auto inline getQueueId() const      -> cl_command_queue;
			auto inline getWaitListData() const -> cl_event const*;
			auto inline getWaitListSize() const -> cl_uint;

			// converts element count based arrays into byte based arrays
			template<template<class, size_t> class A, class T, size_t N>
			auto toByteArray(A<T,N> const& values) const -> A<T,N>;

		#if defined(CL_VERSION_1_2)
			static constexpr auto blockingOperation = CL_BLOCKING;
			static constexpr auto asyncOperation    = CL_NON_BLOCKING;
		#else
			static constexpr auto blockingOperation = CL_TRUE;
			static constexpr auto asyncOperation    = CL_FALSE;
		#endif // defined(CL_VERSION_1_2)

			//============================================================================
			// Constructors and Assignment
			//============================================================================
		public:
			inline CommandQueueExecutor(CommandQueue const& queue);

			template<typename EventRange,
				CLPP_REQUIRES(concept::is_range<EventRange>::value)>
			CommandQueueExecutor(CommandQueue const& queue, EventRange const& waitList);

			CommandQueueExecutor(CommandQueueExecutor const& rhs) = delete;
			CommandQueueExecutor(CommandQueueExecutor && rhs)     = delete;

			auto operator=(CommandQueueExecutor const& rhs) = delete;
			auto operator=(CommandQueueExecutor && rhs)     = delete;

			//============================================================================
			// Overloads to access clEnqueueReadBuffer
			//============================================================================
		private:

			template<cl_bool Blocking, typename OutputIterator, typename T>
			auto readBufferImpl(
				Buffer<T> const& buffer, size_t offset,
				OutputIterator first, OutputIterator last
			) const -> Event;

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

			//============================================================================
			// Overloads to access clEnqueueWriteBuffer
			//============================================================================
		private:

			template<cl_bool Blocking, typename InputIterator, typename T>
			auto writeBufferImpl(
				Buffer<T> const& buffer, size_t offset,
				InputIterator first, InputIterator last
			) const -> Event;

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

			//============================================================================
			// Overloads to access clEnqueueReadBufferRect
			//============================================================================
		public:

			template<typename OutputIterator, typename T>
			void readBufferRectBlocked(
				Buffer<T> const& buffer,
				std::array<size_t, 3> const& bufferOrigin,
				std::array<size_t, 3> const& hostOrigin,
				std::array<size_t, 3> const& region,
				size_t bufferRowPitch, size_t bufferSlicePitch,
				size_t hostRowPitch, size_t hostSlicePitch,
				OutputIterator first
			) const;

			template<typename OutputIterator, typename T>
			auto readBufferRect(
				Buffer<T> const& buffer,
				std::array<size_t, 3> const& bufferOrigin,
				std::array<size_t, 3> const& hostOrigin,
				std::array<size_t, 3> const& region,
				size_t bufferRowPitch, size_t bufferSlicePitch,
				size_t hostRowPitch, size_t hostSlicePitch,
				OutputIterator first
			) const -> Event;

			//============================================================================
			// Overloads to access clEnqueueWriteBufferRect
			//============================================================================
		public:

			template<typename InputIterator, typename T>
			void writeBufferRectBlocked(
				Buffer<T> const& buffer,
				std::array<size_t, 3> const& bufferOrigin,
				std::array<size_t, 3> const& hostOrigin,
				std::array<size_t, 3> const& region,
				size_t bufferRowPitch, size_t bufferSlicePitch,
				size_t hostRowPitch, size_t hostSlicePitch,
				InputIterator first
			) const;

			template<typename InputIterator, typename T>
			auto writeBufferRect(
				Buffer<T> const& buffer,
				std::array<size_t, 3> const& bufferOrigin,
				std::array<size_t, 3> const& hostOrigin,
				std::array<size_t, 3> const& region,
				size_t bufferRowPitch, size_t bufferSlicePitch,
				size_t hostRowPitch, size_t hostSlicePitch,
				InputIterator first
			) const -> Event;

			//============================================================================
			// Overloads to access clEnqueueCopyBuffer
			//============================================================================
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
				size_t dstRowPitch, size_t dstSlidePitch
			) const -> Event;

			//============================================================================
			// Overloads to access clEnqueueFillBuffer
			//============================================================================
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

			//============================================================================
			// Overloads to access clEnqueueMapBuffer
			//============================================================================
		private:

			template<cl_bool Blocking, typename T>
			auto mapBufferImpl(
				Buffer<T> const& buffer, MapAccess access,
				size_t offset, size_t size,
				MappedMemory<T> & result
			) const -> Event;

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
				Buffer<T> const& buffer, MapAccess access, MappedMemory<T> & result
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

			//============================================================================
			// ND Range Kernel Execution
			//============================================================================
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

			template<size_t N,
				CLPP_REQUIRES(N >= 1)>
			auto executeNDRange(
				Kernel const& kernel,
				NDRange<N> const& globalWorkOffset,
				NDRange<N> const& globalWorkSize,
				NDRange<N> const& localWorkSize
			) const -> Event;

			template<size_t N,
				CLPP_REQUIRES(N >= 1)>
			auto executeNDRange(
				Kernel const& kernel,
				NDRange<N> const& globalWorkSize,
				NDRange<N> const& localWorkSize
			) const -> Event;

			//============================================================================
			// Wait (for events), Marker & Barrier and When for async calls
			//============================================================================
		#if defined(CL_VERSION_1_2)
		public:

			auto inline marker() const -> Event;

			auto inline barrier() const -> Event;

		#endif // defined(CL_VERSION_1_2)

			//============================================================================
			// Members
			//============================================================================
		private:
			CommandQueue const& m_queue;
			Event const*        m_first_event;
			cl_uint             m_count_events;
		};
	}
}

#endif
