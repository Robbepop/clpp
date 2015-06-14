#ifndef CLPP_COMMAND_QUEUE_EXECUTOR_H
	#error "Do not include this file directly."
#endif

#include "utility/concepts.hpp"
#include "utility/count_elements.hpp"

#include "clpp/event.hpp"
#include "clpp/command_queue.hpp"
#include "clpp/mapped_memory.hpp"

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
			return reinterpret_cast<cl_event const*>(m_first_event);
		}

		auto CommandQueueExecutor::getWaitListSize() const -> cl_uint {
			return m_count_events;
		}

		template<template<class, size_t> class A, class T, size_t N>
		auto CommandQueueExecutor::toByteArray(A<T,N> const& values) const -> A<T,N> {
			auto byteArray = A<T,N>{};
			for (auto i = 0u; i < N; ++i) {
				byteArray[i] = values[i] * sizeof(T);
			}
			return byteArray;
		}

		//============================================================================
		// Constructors and Assignment
		//============================================================================

		CommandQueueExecutor::CommandQueueExecutor(CommandQueue const& queue):
			m_queue{queue},
			m_first_event{nullptr},
			m_count_events{0}
		{}

		template<typename EventRange, typename>
		CommandQueueExecutor::CommandQueueExecutor(
			CommandQueue const& queue,
			EventRange const& waitList
		):
			m_queue{queue},
			m_first_event{std::addressof(*waitList.begin())},
			m_count_events{std::distance(waitList.begin(), waitList.end())}
		{}

		//============================================================================
		// Overloads to access clEnqueueReadBuffer
		//============================================================================

		template<cl_bool Blocking, typename OutputIterator, typename T>
		auto CommandQueueExecutor::readBufferImpl(
			Buffer<T> const& buffer, size_t offset,
			OutputIterator first, OutputIterator last
		) const -> Event {
			const auto size = ::utility::count_elements(first, last);
			auto eventId = cl_event{nullptr};
			auto error = clEnqueueReadBuffer(
				getQueueId(), buffer.get(), Blocking,
				offset * sizeof(T),
				std::min(buffer.getSize(), size) * sizeof(T),
				std::addressof(*first),
				getWaitListSize(), getWaitListData(),
				std::addressof(eventId)
			);
			detail::error::handle(error);
			return {eventId};
		}

		//============================================================================

		template<typename OutputIterator, typename T>
		void CommandQueueExecutor::readBufferBlocked(
			Buffer<T> const& buffer, size_t offset, OutputIterator first, OutputIterator last
		) const {
			readBufferImpl<CL_BLOCKING>(buffer, offset, first, last);
		}

		template<typename OutputIterator, typename T>
		void CommandQueueExecutor::readBufferBlocked(
			Buffer<T> const& buffer, OutputIterator first, OutputIterator last
		) const {
			readBufferImpl<CL_BLOCKING>(buffer, 0, first, last);
		}

		template<typename OutputIterator, typename T>
		auto CommandQueueExecutor::readBuffer(
			Buffer<T> const& buffer, size_t offset, OutputIterator first, OutputIterator last
		) const -> Event {
			return readBufferImpl<CL_NON_BLOCKING>(buffer, offset, first, last);
		}

		template<typename OutputIterator, typename T>
		auto CommandQueueExecutor::readBuffer(
			Buffer<T> const& buffer, OutputIterator first, OutputIterator last
		) const -> Event {
			return readBufferImpl<CL_NON_BLOCKING>(buffer, 0, first, last);
		}

		//============================================================================
		// Overloads to access clEnqueueWriteBuffer
		//============================================================================

		template<cl_bool Blocking, typename InputIterator, typename T>
		auto CommandQueueExecutor::writeBufferImpl(
			Buffer<T> const& buffer, size_t offset,
			InputIterator first, InputIterator last
		) const -> Event {
			const auto size = ::utility::count_elements(first, last);
			auto eventId = cl_event{nullptr};
			auto error = clEnqueueWriteBuffer(
				getQueueId(), buffer.get(), Blocking,
				offset * sizeof(T),
				std::min(buffer.getSize(), size) * sizeof(T),
				std::addressof(*first),
				getWaitListSize(), getWaitListData(),
				std::addressof(eventId)
			);
			detail::error::handle(error);
			return {eventId};
		}

		//============================================================================

		template<typename InputIterator, typename T>
		void CommandQueueExecutor::writeBufferBlocked(
			Buffer<T> const& buffer, size_t offset, InputIterator first, InputIterator last
		) const {
			writeBufferImpl<CL_BLOCKING>(buffer, offset, first, last);
		}

		template<typename InputIterator, typename T>
		void CommandQueueExecutor::writeBufferBlocked(
			Buffer<T> const& buffer, InputIterator first, InputIterator last
		) const {
			writeBufferImpl<CL_BLOCKING>(buffer, 0, first, last);
		}

		template<typename InputIterator, typename T>
		auto CommandQueueExecutor::writeBuffer(
			Buffer<T> const& buffer, size_t offset, InputIterator first, InputIterator last
		) const -> Event {
			return writeBufferImpl<CL_NON_BLOCKING>(buffer, offset, first, last);
		}

		template<typename InputIterator, typename T>
		auto CommandQueueExecutor::writeBuffer(
			Buffer<T> const& buffer, InputIterator first, InputIterator last
		) const -> Event {
			return writeBufferImpl<CL_NON_BLOCKING>(buffer, 0, first, last);
		}

		//============================================================================
		// Overloads to access clEnqueueReadBufferRect
		//============================================================================

		template<typename OutIterator, typename T>
		void CommandQueueExecutor::readBufferRectBlocked(
			Buffer<T> const& buffer,
			std::array<size_t, 3> const& bufferOrigin,
			std::array<size_t, 3> const& hostOrigin,
			std::array<size_t, 3> const& region,
			size_t bufferRowPitch, size_t bufferSlicePitch,
			size_t hostRowPitch, size_t hostSlicePitch,
			OutIterator first
		) const {
			static_assert(std::is_same<
				typename OutIterator::value_type,
				typename Buffer<T>::value_type>::value,
				"value_type of OutIterator must be the same as value_type of buffer");
			auto error = clEnqueueReadBufferRect(
				getQueueId(), buffer.get(), CL_BLOCKING,
				toByteArray(bufferOrigin).data(),
				toByteArray(hostOrigin).data(),
				toByteArray(region).data(),
				bufferRowPitch * sizeof(T), bufferSlicePitch * sizeof(T),
				hostRowPitch * sizeof(T), hostSlicePitch * sizeof(T),
				std::addressof(first[0]),
				getWaitListSize(), getWaitListData(),
				nullptr);
			detail::error::handle(error);
		}

		template<typename OutIterator, typename T>
		auto CommandQueueExecutor::readBufferRect(
			Buffer<T> const& buffer,
			std::array<size_t, 3> const& bufferOrigin,
			std::array<size_t, 3> const& hostOrigin,
			std::array<size_t, 3> const& region,
			size_t bufferRowPitch, size_t bufferSlicePitch,
			size_t hostRowPitch, size_t hostSlicePitch,
			OutIterator first
		) const -> Event {
			static_assert(std::is_same<
				typename OutIterator::value_type,
				typename Buffer<T>::value_type>::value,
				"value_type of OutIterator must be the same as value_type of buffer");
			auto eventId = cl_event{nullptr};
			auto error   = clEnqueueReadBufferRect(
				getQueueId(), buffer.get(), CL_NON_BLOCKING,
				toByteArray(bufferOrigin).data(),
				toByteArray(hostOrigin).data(),
				toByteArray(region).data(),
				bufferRowPitch * sizeof(T), bufferSlicePitch * sizeof(T),
				hostRowPitch * sizeof(T), hostSlicePitch * sizeof(T),
				std::addressof(first[0]),
				getWaitListSize(), getWaitListData(),
				std::addressof(eventId));
			detail::error::handle(error);
			return {eventId};
		}

		//============================================================================
		// Overloads to access clEnqueueWriteBufferRect
		//============================================================================

		template<typename InIterator, typename T>
		void CommandQueueExecutor::writeBufferRectBlocked(
			Buffer<T> const& buffer,
			std::array<size_t, 3> const& bufferOrigin,
			std::array<size_t, 3> const& hostOrigin,
			std::array<size_t, 3> const& region,
			size_t bufferRowPitch, size_t bufferSlicePitch,
			size_t hostRowPitch, size_t hostSlicePitch,
			InIterator first
		) const {
			static_assert(std::is_same<
				typename InIterator::value_type,
				typename Buffer<T>::value_type>::value,
				"value_type of InIterator must be the same as value_type of buffer");
			auto error = clEnqueueWriteBufferRect(
				getQueueId(), buffer.get(), CL_BLOCKING,
				toByteArray(bufferOrigin).data(),
				toByteArray(hostOrigin).data(),
				toByteArray(region).data(),
				bufferRowPitch * sizeof(T), bufferSlicePitch * sizeof(T),
				hostRowPitch * sizeof(T), hostSlicePitch * sizeof(T),
				std::addressof(first[0]),
				getWaitListSize(), getWaitListData(),
				nullptr);
			detail::error::handle(error);
		}

		template<typename InIterator, typename T>
		auto CommandQueueExecutor::writeBufferRect(
			Buffer<T> const& buffer,
			std::array<size_t, 3> const& bufferOrigin,
			std::array<size_t, 3> const& hostOrigin,
			std::array<size_t, 3> const& region,
			size_t bufferRowPitch, size_t bufferSlicePitch,
			size_t hostRowPitch, size_t hostSlicePitch,
			InIterator first
		) const -> Event {
			static_assert(std::is_same<
				typename InIterator::value_type,
				typename Buffer<T>::value_type>::value,
				"value_type of InIterator must be the same as value_type of buffer");
			auto eventId = cl_event{nullptr};
			auto error   = clEnqueueWriteBufferRect(
				getQueueId(), buffer.get(), CL_NON_BLOCKING,
				toByteArray(bufferOrigin).data(),
				toByteArray(hostOrigin).data(),
				toByteArray(region).data(),
				bufferRowPitch * sizeof(T), bufferSlicePitch * sizeof(T),
				hostRowPitch * sizeof(T), hostSlicePitch * sizeof(T),
				std::addressof(first[0]),
				getWaitListSize(), getWaitListData(),
				std::addressof(eventId));
			detail::error::handle(error);
			return {eventId};
		}

		//============================================================================
		// Overloads to access clEnqueueCopyBuffer
		//============================================================================

		template<typename T, typename V>
		auto CommandQueueExecutor::copyBuffer(
			Buffer<T> const& src, Buffer<V> const& dst,
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
		auto CommandQueueExecutor::copyBuffer(
			Buffer<T> const& src, Buffer<V> const& dst
		) const -> Event {
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
		auto CommandQueueExecutor::copyBufferRect(
			Buffer<T> const& src, Buffer<V> const& dst,
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
		auto CommandQueueExecutor::fillBuffer(
			Buffer<T> const& buffer, T const& value, size_t offset, size_t size
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
		auto CommandQueueExecutor::fillBuffer(
			Buffer<T> const& buffer, T const& value
		) const -> Event {
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
		void CommandQueueExecutor::mapBufferBlocked(
			Buffer<T> const& buffer, MapAccess access,
			size_t offset, size_t size,
			MappedMemory<T> & result
		) const {
			auto error  = cl_int{CL_INVALID_VALUE};
			auto region = clEnqueueMapBuffer(
				getQueueId(), buffer.get(), CL_BLOCKING, access,
				offset * sizeof(T), size * sizeof(T),
				getWaitListSize(), getWaitListData(),
				nullptr, std::addressof(error));
			detail::error::handle(error);
			result = {m_queue, buffer, reinterpret_cast<T*>(region), size};
		}

		template<typename T>
		void CommandQueueExecutor::mapBufferBlocked(
			Buffer<T> const& buffer, MapAccess access, MappedMemory<T> & result
		) const {
			auto error  = cl_int{CL_INVALID_VALUE};
			auto region = clEnqueueMapBuffer(
				getQueueId(), CL_BLOCKING, access,
				0, buffer.getSizeInBytes(),
				getWaitListSize(), getWaitListData(),
				nullptr, std::addressof(error));
			detail::error::handle(error);
			result = {m_queue, buffer, reinterpret_cast<T*>(region), buffer.getSize()};
		}

		template<typename T>
		auto CommandQueueExecutor::mapBuffer(
			Buffer<T> const& buffer,
			MapAccess access,
			size_t offset, size_t size,
			MappedMemory<T> & result
		) const -> Event {
			auto eventId = cl_event{nullptr};
			auto error   = cl_int{CL_INVALID_VALUE};
			auto region  = clEnqueueMapBuffer(
				getQueueId(), buffer.get(), CL_NON_BLOCKING, access,
				offset * sizeof(T), size * sizeof(T),
				getWaitListSize(), getWaitListData(),
				std::addressof(eventId),
				std::addressof(error));
			detail::error::handle(error);
			result = {m_queue, buffer, reinterpret_cast<T*>(region), buffer.getSize()};
			return {eventId};
		}

		template<typename T>
		auto CommandQueueExecutor::mapBuffer(
			Buffer<T> const& buffer, MapAccess access, MappedMemory<T> & result
		) const -> Event {
			auto eventId = cl_event{nullptr};
			auto error   = cl_int{CL_INVALID_VALUE};
			auto region  = clEnqueueMapBuffer(
				getQueueId(), buffer.get(), CL_NON_BLOCKING, access,
				0, buffer.getSizeInBytes(),
				getWaitListSize(), getWaitListData(),
				std::addressof(eventId),
				std::addressof(error));
			detail::error::handle(error);
			result = {m_queue, buffer, reinterpret_cast<T*>(region), buffer.getSize()};
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
				std::addressof(eventId)
			);
			detail::error::handle(error);
			return {eventId};
		}

		auto CommandQueueExecutor::execute1DRange(
			Kernel const& kernel,
			size_t globalWorkSize,
			size_t localWorkSize
		) const -> Event {
			auto eventId = cl_event{nullptr};
			auto error   = clEnqueueNDRangeKernel(
				getQueueId(), kernel.get(), 1,
				nullptr,
				std::addressof(globalWorkSize),
				std::addressof(localWorkSize),
				getWaitListSize(), getWaitListData(),
				std::addressof(eventId)
			);
			detail::error::handle(error);
			return {eventId};
		}

		auto CommandQueueExecutor::execute1DRange(
			Kernel const& kernel,
			size_t globalWorkSize
		) const -> Event {
			auto eventId = cl_event{nullptr};
			auto error   = clEnqueueNDRangeKernel(
				getQueueId(), kernel.get(), 1,
				nullptr,
				std::addressof(globalWorkSize),
				nullptr,
				getWaitListSize(), getWaitListData(),
				std::addressof(eventId)
			);
			detail::error::handle(error);
			return {eventId};
		}

		template<size_t N, typename>
		auto CommandQueueExecutor::executeNDRange(
			Kernel const& kernel,
			NDRange<N> const& globalWorkOffset,
			NDRange<N> const& globalWorkSize,
			NDRange<N> const& localWorkSize
		) const -> Event {
			auto eventId = cl_event{nullptr};
			auto error   = clEnqueueNDRangeKernel(
				getQueueId(), kernel.get(), N,
				globalWorkOffset.data(),
				globalWorkSize.data(),
				localWorkSize.data(),
				getWaitListSize(), getWaitListData(),
				std::addressof(eventId)
			);
			detail::error::handle(error);
			return {eventId};
		}

		//============================================================================
		// Wait (for events), Marker & Barrier and When for async calls
		//============================================================================

		auto CommandQueueExecutor::marker() const -> Event {
			auto eventId = cl_event{nullptr};
			auto error   = clEnqueueMarkerWithWaitList(
				getQueueId(), getWaitListSize(), getWaitListData(), std::addressof(eventId));
			detail::error::handle(error);
			return {eventId};
		}

		auto CommandQueueExecutor::barrier() const -> Event {
			auto eventId = cl_event{nullptr};
			auto error   = clEnqueueBarrierWithWaitList(
				getQueueId(), getWaitListSize(), getWaitListData(), std::addressof(eventId));
			detail::error::handle(error);
			return {eventId};
		}
	}
}
