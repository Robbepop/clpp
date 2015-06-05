#ifndef CLPP_COMMAND_QUEUE_H
#define CLPP_COMMAND_QUEUE_H

namespace cl {
	namespace detail {
		template<>
		struct ObjectHandler<cl_command_queue> final {
			using cl_type        = cl_command_queue;
			using info_type      = cl_command_queue_info;
			using exception_type = CommandQueueError;

			static auto release(cl_command_queue id) { clReleaseCommandQueue(id); }

			static auto retain(cl_command_queue id) { clRetainCommandQueue(id); }

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

		using detail::Object<cl_command_queue>::Object;

		auto operator=(const CommandQueue & rhs) -> CommandQueue &;

		//================================================================================
		// Overloads to access clEnqueueReadBuffer
		//================================================================================

		template<typename OutputIterator, typename T>
		void readBuffer(Buffer<T> buffer, size_t offset,
			OutputIterator first, OutputIterator last);

		template<typename OutputIterator, typename T>
		void readBuffer(Buffer<T> buffer, OutputIterator first);

		template<typename OutputIterator, typename T>
		auto readBufferAsync(Buffer<T> buffer, size_t offset,
			OutputIterator first, OutputIterator last) -> Event;

		template<typename OutputIterator, typename T>
		auto readBufferAsync(Buffer<T> buffer, OutputIterator first) -> Event;

		//================================================================================
		// Overloads to access clEnqueueWriteBuffer
		//================================================================================

		template<typename InputIterator, typename T>
		void writeBuffer(Buffer<T> buffer, size_t offset,
			InputIterator first, InputIterator last);

		template<typename InputIterator, typename T>
		void writeBuffer(Buffer<T> buffer, InputIterator first);

		template<typename InputIterator, typename T>
		auto writeBufferAsync(Buffer<T> buffer, size_t offset,
			InputIterator first, InputIterator last) -> Event;

		template<typename InputIterator, typename T>
		auto writeBufferAsync(Buffer<T> buffer, InputIterator first) -> Event;

		//================================================================================
		// Overloads to access clEnqueueReadBufferRect
		//================================================================================

		template<typename OutIterator, typename T, size_t N>
		void readBufferRect(
			Buffer<T> buffer,
			size_t[N] bufferOrigin, size_t[N] hostOrigin, size_t[N] region,
			size_t bufferRowPitch, size_t bufferSlicePitch,
			size_t hostRowPitch, size_t hostSlicePitch,
			OutIterator first);

		template<typename OutIterator, typename T, size_t N>
		auto readBufferRectAsync(
			Buffer<T> buffer,
			size_t[N] bufferOrigin, size_t[N] hostOrigin, size_t[N] region,
			size_t bufferRowPitch, size_t bufferSlicePitch,
			size_t hostRowPitch, size_t hostSlicePitch,
			OutIterator first) -> Event;

		//================================================================================
		// Overloads to access clEnqueueWriteBufferRect
		//================================================================================

		template<typename OutIterator, typename T, size_t N>
		void writeBufferRect(
			Buffer<T> buffer,
			size_t[N] bufferOrigin, size_t[N] hostOrigin, size_t[N] region,
			size_t bufferRowPitch, size_t bufferSlicePitch,
			size_t hostRowPitch, size_t hostSlicePitch,
			OutIterator out);

		template<typename OutIterator, typename T, size_t N>
		auto writeBufferRectAsync(
			Buffer<T> buffer,
			size_t[N] bufferOrigin, size_t[N] hostOrigin, size_t[N] region,
			size_t bufferRowPitch, size_t bufferSlicePitch,
			size_t hostRowPitch, size_t hostSlicePitch,
			OutIterator out) -> Event;

		//================================================================================
		// Overloads to access clEnqueueCopyBuffer
		//================================================================================

		template<typename T, typename V>
		void copyBuffer(Buffer<T> src, Buffer<V> dst,
			size_t srcOffset, size_t dstOffset, size_t size);

		template<typename T, typename V>
		void copyBuffer(Buffer<T> src, Buffer<V> dst);

		template<typename T, typename V>
		auto copyBufferAsync(Buffer<T> src, Buffer<V> dst,
			size_t srcOffset, size_t dstOffset, size_t size) -> Event;

		template<typename T, typename V>
		auto copyBufferAsync(Buffer<T> src, Buffer<V> dst) -> Event;

		//================================================================================
		// Overloads to access clEnqueueCopyBufferRect
		//================================================================================

		template<typename T, typename V, size_t N>
		void copyBufferRect(Buffer<T> src, Buffer<V> dest,
			size_t[N] srcOrigin, size_t[N] dstOrigin, size_t[N] region,
			size_t srcRowPitch, size_t srcSlicePitch,
			size_t dstRowPitch, size_t dstSlidePitch);

		template<typename T, typename V, size_t N>
		auto copyBufferRectAsync(Buffer<T> src, Buffer<V> dest,
			size_t[N] srcOrigin, size_t[N] dstOrigin, size_t[N] region,
			size_t srcRowPitch, size_t srcSlicePitch,
			size_t dstRowPitch, size_t dstSlidePitch) -> Event;

		//================================================================================
		// Overloads to access clEnqueueFillBuffer
		//================================================================================

		template<typename T>
		void fillBuffer(Buffer<T> buffer, T const& value, size_t offset, size_t size);

		template<typename T>
		void fillBuffer(Buffer<T> buffer, T const& value);

		template<typename T>
		auto fillBufferAsync(Buffer<T> buffer, T const& value, size_t offset, size_t size)
			-> Event;

		template<typename T>
		auto fillBufferAsync(Buffer<T> buffer, T const& value) -> Event;

		//================================================================================
		// Wait (for events), Marker & Barrier
		//================================================================================

		template<typename EventRange>
		auto wait(EventRange const& waitList) const -> CommandQueue &;

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

#endif
