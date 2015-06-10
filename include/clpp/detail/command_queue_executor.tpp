#ifndef CLPP_COMMAND_QUEUE_EXECUTOR_H
	#error "Do not include this file directly."
#endif

#include <algorithm>

namespace cl {
	namespace detail {
		//============================================================================
		// Helper methods to access members.
		//============================================================================

		auto CommandQueueExecutor::getQueueId() const -> cl_command_queue {
			return m_queue.get();
		}

		auto CommandQueueExecutor::getWaitListData() const -> cl_event const* {
			return const_cast<const cl_event*>(
				reinterpret_cast<cl_event*>(m_wait_list.data()));
		}

		auto CommandQueueExecutor::getWaitListSize() const -> cl_uint {
			m_wait_list.size();
		}

		template<typename T, size_t N>
		auto CommandQueueExecutor::toByteArray(std::array<T,N> const& values) const -> std::array<T,N> {
			auto byteArray = std::array<T,N>{};
			for (auto i = 0u; i < N; ++i) {
				byteArray[i] = values[i] * sizeof(T);
			}
			return byteArray;
		}

		//============================================================================
		// Constructors and Assignment
		//============================================================================

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

		template<typename OutputIterator, typename T>
		void readBuffer(Buffer<T> buffer, size_t offset,
			OutputIterator first, OutputIterator last) const;

		template<typename OutputIterator, typename T>
		void readBuffer(Buffer<T> buffer, OutputIterator first) const;

		template<typename OutputIterator, typename T>
		auto readBufferAsync(Buffer<T> buffer, size_t offset,
			OutputIterator first, OutputIterator last) const -> Event;

		template<typename OutputIterator, typename T>
		auto readBufferAsync(Buffer<T> buffer, OutputIterator first) const -> Event;

		//============================================================================
		// Overloads to access clEnqueueWriteBuffer
		//============================================================================

		template<typename InputIterator, typename T>
		void writeBuffer(Buffer<T> buffer, size_t offset,
			InputIterator first, InputIterator last) const;

		template<typename InputIterator, typename T>
		void writeBuffer(Buffer<T> buffer, InputIterator first) const;

		template<typename InputIterator, typename T>
		auto writeBufferAsync(Buffer<T> buffer, size_t offset,
			InputIterator first, InputIterator last) const -> Event;

		template<typename InputIterator, typename T>
		auto writeBufferAsync(Buffer<T> buffer, InputIterator first) const -> Event;

		//============================================================================
		// Overloads to access clEnqueueReadBufferRect
		//============================================================================

		template<typename OutIterator, typename T>
		void readBufferRect(
			Buffer<T> buffer,
			std::array<size_t, 3> const& bufferOrigin,
			std::array<size_t, 3> const& hostOrigin,
			std::array<size_t, 3> const& region,
			size_t bufferRowPitch, size_t bufferSlicePitch,
			size_t hostRowPitch, size_t hostSlicePitch,
			OutIterator first) const;

		template<typename OutIterator, typename T>
		auto readBufferRectAsync(
			Buffer<T> buffer,
			std::array<size_t, 3> const& bufferOrigin,
			std::array<size_t, 3> const& hostOrigin,
			std::array<size_t, 3> const& region,
			size_t bufferRowPitch, size_t bufferSlicePitch,
			size_t hostRowPitch, size_t hostSlicePitch,
			OutIterator first) const -> Event;

		//============================================================================
		// Overloads to access clEnqueueWriteBufferRect
		//============================================================================

		template<typename OutIterator, typename T>
		void writeBufferRect(
			Buffer<T> buffer,
			std::array<size_t, 3> const& bufferOrigin,
			std::array<size_t, 3> const& hostOrigin,
			std::array<size_t, 3> const& region,
			size_t bufferRowPitch, size_t bufferSlicePitch,
			size_t hostRowPitch, size_t hostSlicePitch,
			OutIterator out) const;

		template<typename OutIterator, typename T>
		auto writeBufferRectAsync(
			Buffer<T> buffer,
			std::array<size_t, 3> const& bufferOrigin,
			std::array<size_t, 3> const& hostOrigin,
			std::array<size_t, 3> const& region,
			size_t bufferRowPitch, size_t bufferSlicePitch,
			size_t hostRowPitch, size_t hostSlicePitch,
			OutIterator out) const -> Event;

		//============================================================================
		// Overloads to access clEnqueueCopyBuffer
		//============================================================================

		template<typename T, typename V>
		void copyBuffer(Buffer<T> src, Buffer<V> dst,
			size_t srcOffset, size_t dstOffset, size_t size
		) const {
			auto eventId = cl_event{nullptr};
			auto error   = clEnqueueCopyBuffer(
				getQueueId(), src.get(), dst.get(),
				srcOffset * sizeof(T), dstOffset * sizeof(T), size * sizeof(T),
				getWaitListSize(), getWaitListData(),
				std::addressof(eventId));
			detail::error::handle(error);
			Event::wait({eventId});
		}

		template<typename T, typename V>
		void copyBuffer(Buffer<T> src, Buffer<V> dst) const {
			auto eventId = cl_event{nullptr};
			auto error   = clEnqueueCopyBuffer(
				getQueueId(), src.get(), dst.get(),
				0, 0, std::min(src.getSizeInBytes(), dst.getSizeInBytes()),
				getWaitListSize(), getWaitListData(),
				std::addressof(eventId));
			detail::error::handle(error);
			Event::wait({eventId});
		}

		template<typename T, typename V>
		auto copyBufferAsync(Buffer<T> src, Buffer<V> dst,
			size_t srcOffset, size_t dstOffset, size_t size
		) const -> Event {
			auto eventId = cl_event{nullptr};
			auto error   = clEnqueueCopyBuffer(
				getQueueId(), src.get(), dst.get(),
				srcOffset * sizeof(T), dstOffset * sizeof(T), size * sizeof(T),
				getWaitListSize(), getWaitListData(),
				std::addressof(eventId));
			detail::error::handle(error);
			return {eventId};
		}

		template<typename T, typename V>
		auto copyBufferAsync(Buffer<T> src, Buffer<V> dst) const -> Event {
			auto eventId = cl_event{nullptr};
			auto error   = clEnqueueCopyBuffer(
				getQueueId(), src.get(), dst.get(),
				0, 0, std::min(src.getSizeInBytes(), dst.getSizeInBytes()),
				getWaitListSize(), getWaitListData(),
				std::addressof(eventId));
			detail::error::handle(error);
			return {eventId};
		}

		//============================================================================
		// Overloads to access clEnqueueCopyBufferRect
		//============================================================================

		template<typename T, typename V>
		void copyBufferRect(Buffer<T> src, Buffer<V> dest,
			std::array<size_t, 3> const& srcOrigin,
			std::array<size_t, 3> const& dstOrigin,
			std::array<size_t, 3> const& region,
			size_t srcRowPitch, size_t srcSlicePitch,
			size_t dstRowPitch, size_t dstSlidePitch
		) const {
			using namespace utility;
			constexpr size = sizeof(T);
			auto eventId = cl_event{nullptr};
			auto error   = clEnqueueCopyBufferRect(
				src.get(), dst.get(),
				toByteArray(srcOrigin).data(),
				toByteArray(dstOrigin).data(),
				toByteArray(region).data(),
				srcRowPitch * sizeof(T), srcSlicePitch * sizeof(T),
				dstRowPitch * sizeof(T), dstSlidePitch * sizeof(T),
				getWaitListSize(), getWaitListData(),
				std::addressof(eventId));
			detail::error::handle(error);
			Event::wait({eventId});
		}

		template<typename T, typename V>
		auto copyBufferRectAsync(Buffer<T> src, Buffer<V> dest,
			std::array<size_t, 3> const& srcOrigin,
			std::array<size_t, 3> const& dstOrigin,
			std::array<size_t, 3> const& region,
			size_t srcRowPitch, size_t srcSlicePitch,
			size_t dstRowPitch, size_t dstSlidePitch
		) const -> Event {
			auto eventId = cl_event{nullptr};
			auto error   = clEnqueueCopyBufferRect(
				src.get(), dst.get(),
				toByteArray(srcOrigin).data(),
				toByteArray(dstOrigin).data(),
				toByteArray(region).data(),
				srcRowPitch * sizeof(T), srcSlicePitch * sizeof(T),
				dstRowPitch * sizeof(T), dstSlidePitch * sizeof(T),
				getWaitListSize(), getWaitListData(),
				std::addressof(eventId));
			detail::error::handle(error);
			return {eventId};
		}

		//============================================================================
		// Overloads to access clEnqueueFillBuffer
		//============================================================================

		template<typename T>
		void fillBuffer(
			Buffer<T> buffer, T const& value, size_t offset, size_t size
		) const {
			auto eventId = cl_event{nullptr};
			auto error = clEnqueueFillBuffer(
				getQueueId(), buffer.get(),
				std::addressof(value), sizeof(T),
				offset * sizeof(T), size * sizeof(T),
				getWaitListSize(), getWaitListData(),
				std::addressof(eventId));
			detail::error::handle(error);
			Event::wait({eventId}); // required for blocking operation
		}

		template<typename T>
		void fillBuffer(Buffer<T> buffer, T const& value) const {
			auto eventId = cl_event{nullptr};
			auto error = clEnqueueFillBuffer(
				getQueueId(), buffer.get(),
				std::addressof(value), sizeof(T),
				0, buffer.getSizeInBytes(),
				getWaitListSize(), getWaitListData(),
				std::addressof(eventId));
			detail::error::handle(error);
			Event::wait({eventId}); // required for blocking operation
		}

		template<typename T>
		auto fillBufferAsync(
			Buffer<T> buffer, T const& value, size_t offset, size_t size
		) const -> Event {
			auto eventId = cl_event{nullptr};
			auto error   = clEnqueueFillBuffer(
				getQueueId(), buffer.get(),
				std::addressof(value), sizeof(T),
				offset * sizeof(T), size * sizeof(T),
				getWaitListSize(), getWaitListData(),
				std::addressof(eventId));
			detail::error::handle(error);
			return {eventId};
		}

		template<typename T>
		auto fillBufferAsync(Buffer<T> buffer, T const& value) const -> Event {
			auto eventId = cl_event{nullptr};
			auto error   = clEnqueueFillBuffer(
				getQueueId(), buffer.get(),
				std::addressof(value), sizeof(T),
				0, buffer.getSizeInBytes(),
				getWaitListSize(), getWaitListData(),
				std::addressof(eventId));
			detail::error::handle(error);
			return {eventId};
		}

		//============================================================================
		// Overloads to access clEnqueueMapBuffer
		//============================================================================

		template<typename T>
		void CommandQueueExecutor::mapBuffer(
			Buffer<T> const& buffer, MapAccess access, size_t offset, size_t size, MappedMemory<T> & result
		) const {
			auto error  = cl_int{CL_INVALID_VALUE};
			auto region = clEnqueueMapBuffer(
				getQueueId(), CL_BLOCKING, access,
				offset * sizeof(T), size * sizeof(T),
				getWaitListSize(), getWaitListData(),
				nullptr, std::addressof(error));
			detail::error::handle(error);
			result = {m_queue, buffer, reinterpret_cast<T*>(region), size};
		}

		template<typename T>
		void CommandQueueExecutor::mapBuffer(
			Buffer<T> const& buffer, MapAccess access, MappedMemory<T> & result
		) const {
			auto error  = cl_int{CL_INVALID_VALUE};
			auto region = clEnqueueMapBuffer(
				getQueueId(), CL_BLOCKING, access,
				0, buffer.getSizeInBytes(),
				getWaitListSize(), getWaitListData(),
				nullptr, std::addressof(error));
			detail::error::handle(error);
			result = {m_queue, buffer, reinterpret_cast<T*>(region), size};
		}

		template<typename T>
		auto CommandQueueExecutor::mapBufferAsync(
			Buffer<T> const& buffer,
			MapAccess access,
			size_t offset, size_t size,
			MappedMemory<T> & result
		) const -> Event {
			auto eventId = cl_event{nullptr};
			auto error   = cl_int{CL_INVALID_VALUE};
			auto region  = clEnqueueMapBuffer(
				getQueueId(), CL_BLOCKING, access,
				offset * sizeof(T), size * sizeof(T),
				getWaitListSize(), getWaitListData(),
				std::addressof(eventId),
				std::addressof(error));
			detail::error::handle(error);
			result = {m_queue, buffer, reinterpret_cast<T*>(region), size};
			return {eventId};
		}

		template<typename T>
		auto CommandQueueExecutor::mapBufferAsync(
			Buffer<T> const& buffer, MapAccess access, MappedMemory<T> & result
		) const -> Event {
			auto eventId = cl_event{nullptr};
			auto error   = cl_int{CL_INVALID_VALUE};
			auto region  = clEnqueueMapBuffer(
				getQueueId(), CL_BLOCKING, access,
				0, buffer.getSizeInBytes(),
				getWaitListSize(), getWaitListData(),
				std::addressof(eventId),
				std::addressof(error));
			detail::error::handle(error);
			result = {m_queue, buffer, reinterpret_cast<T*>(region), size};
			return {eventId};
		}

		//============================================================================
		// ND Range Kernel Execution
		//============================================================================

		auto CommandQueueExecutor::execute1DRange(
			Kernel const& kernel,
			size_t globalWorkOffset,
			size_t globalWorkSize,
			size_t localWorkSize
		) const -> Event {
			auto eventId = cl_event{nullptr};
			auto error   = clEnqueueNDRangeKernel(
				getQueueId(), kernel.get(), 1,
				std::addressof(globalWorkOffset),
				std::addressof(globalWorkSize),
				std::addressof(localWorkSize),
				getWaitListSize(), getWaitListData(),
				std::addressof(eventId);
			);
			detail::error::handle(error);
			return {eventId};
		}

		template<size_t N>
		auto CommandQueueExecutor::executeNDRange(
			Kernel const& kernel,
			NDRange<N> const& globalWorkOffset,
			NDRange<N> const& globalWorkSize,
			NDRange<N> const& localWorkSize
		) const -> Event {
			static_assert(N >= 1, "N must be greater than or equal to 1.")
			auto eventId = cl_event{nullptr};
			auto error   = clEnqueueNDRangeKernel(
				getQueueId(), kernel.get(), N,
				globalWorkOffset.data(),
				globalWorkSize.data(),
				localWorkSize.data(),
				getWaitListSize(), getWaitListData(),
				std::addressof(eventId);
			);
			detail::error::handle(error);
			return {eventId};
		}

		//============================================================================
		// Wait (for events), Marker & Barrier and When for async calls
		//============================================================================

		template<typename EventRange>
		auto CommandQueueExecutor::marker() const -> Event {
			auto eventId = cl_event{nullptr};
			auto error   = clEnqueueMarkerWithWaitList(
				getQueueId(), getWaitListSize(), getWaitListData(), &eventId);
			detail::error::handle(error);
			return {eventId};
		}

		template<typename EventRange>
		auto CommandQueueExecutor::barrier() const -> Event {
			auto eventId = cl_event{nullptr};
			auto error   = clEnqueueBarrierWithWaitList(
				getQueueId(), getWaitListSize(), getWaitListData(), &eventId);
			detail::error::handle(error);
			return {eventId};
		}
	}
}
