#ifndef CLPP_COMMAND_QUEUE_H
#define CLPP_COMMAND_QUEUE_H

namespace cl {
	namespace detail {
		template<>
		struct ObjectHandler<cl_command_queue> final {
			using cl_type        = cl_command_queue;
			using info_type      = cl_command_queue_info;
			using exception_type = CommandQueueError;

			static auto release(cl_type id) { clReleaseCommandQueue(id); }

			static auto retain(cl_type id) { clRetainCommandQueue(id); }

			static auto getInfo
			(
				cl_type   queue,
				info_type param_name,
				size_t    param_value_size,
				void *    param_value,
				size_t *  param_value_size_ret
			) {
				return clGetCommandQueueInfo(
					device, param_name, param_value_size, param_value, param_value_size_ret);
			}
		};
	}

	class CommandQueue final : public detail::Object<cl_command_queue> {
	public:
		//================================================================================
		// Constructors and Assignment
		//================================================================================

		using detail::Object<cl_type>::Object;

		auto operator=(const CommandQueue & rhs) -> CommandQueue &;

		//================================================================================
		// Overloads to access clEnqueueReadBuffer
		//================================================================================

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

		//================================================================================
		// Overloads to access clEnqueueWriteBuffer
		//================================================================================

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

		//================================================================================
		// Overloads to access clEnqueueReadBufferRect
		//================================================================================

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

		//================================================================================
		// Overloads to access clEnqueueWriteBufferRect
		//================================================================================

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

		//================================================================================
		// Overloads to access clEnqueueCopyBuffer
		//================================================================================

		template<typename T, typename V>
		void copyBuffer(Buffer<T> src, Buffer<V> dst,
			size_t srcOffset, size_t dstOffset, size_t size) const;

		template<typename T, typename V>
		void copyBuffer(Buffer<T> src, Buffer<V> dst) const;

		template<typename T, typename V>
		auto copyBufferAsync(Buffer<T> src, Buffer<V> dst,
			size_t srcOffset, size_t dstOffset, size_t size) const -> Event;

		template<typename T, typename V>
		auto copyBufferAsync(Buffer<T> src, Buffer<V> dst) const -> Event;

		//================================================================================
		// Overloads to access clEnqueueCopyBufferRect
		//================================================================================

		template<typename T, typename V>
		void copyBufferRect(Buffer<T> src, Buffer<V> dest,
			std::array<size_t, 3> const& srcOrigin,
			std::array<size_t, 3> const& dstOrigin,
			std::array<size_t, 3> const& region,
			size_t srcRowPitch, size_t srcSlicePitch,
			size_t dstRowPitch, size_t dstSlidePitch) const;

		template<typename T, typename V>
		auto copyBufferRectAsync(Buffer<T> src, Buffer<V> dest,
			std::array<size_t, 3> const& srcOrigin,
			std::array<size_t, 3> const& dstOrigin,
			std::array<size_t, 3> const& region,
			size_t srcRowPitch, size_t srcSlicePitch,
			size_t dstRowPitch, size_t dstSlidePitch) const -> Event;

		//================================================================================
		// Overloads to access clEnqueueFillBuffer
		//================================================================================

		template<typename T>
		void fillBuffer(Buffer<T> buffer, T const& value, size_t offset, size_t size) const;

		template<typename T>
		void fillBuffer(Buffer<T> buffer, T const& value) const;

		template<typename T>
		auto fillBufferAsync(Buffer<T> buffer, T const& value, size_t offset, size_t size) const
			-> Event;

		template<typename T>
		auto fillBufferAsync(Buffer<T> buffer, T const& value) const -> Event;

		//================================================================================
		// Overloads to access clEnqueueMapBuffer
		//================================================================================

		template<typename T>
		void mapBuffer(Buffer<T>, MapAccess access, MappedMemory<T> & result,
			size_t offset, size_t size) const;

		template<typename T>
		void mapBuffer(Buffer<T>, MapAccess access, MappedMemory<T> & result) const;

		template<typename T>
		auto mapBufferAsync(Buffer<T>, MapAccess access, MappedMemory<T> & result,
			size_t offset, size_t size) const -> Event;

		template<typename T>
		auto mapBufferAsync(Buffer<T>, MapAccess access, MappedMemory<T> & result) const -> Event;

		//================================================================================
		// Wait (for events), Marker & Barrier and When for async calls
		//================================================================================

		template<typename EventRange>
		auto when(EventRange const& waitList) -> CommandQueue &;

		template<typename EventRange>
		auto when(EventRange const& waitList) const -> CommandQueue const&;

		template<typename EventRange>
		auto marker() const -> Event;

		template<typename EventRange>
		auto barrier() const -> Event;

		//================================================================================
		// Flush & Finish
		//================================================================================

		void flush() const;
		void finish() const;

		//================================================================================
		// Information Getters
		//================================================================================

		auto getContext() const        -> Context;
		auto getDevice() const         -> Device;
		auto getReferenceCount() const -> cl_uint;
		auto getProperties() const     -> CommandQueueProperties;
		auto getSize() const           -> cl_uint; // the same as 'size()'
		auto size() const              -> cl_uint; // the same as 'getSize()'
	};
}

#include "clpp/command_queue.tpp"
#endif
