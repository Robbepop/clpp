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

		template<typename OutIterator, typename T>
		void readBuffer(Buffer<T> buffer, size_t offset, size_t size, OutIterator out);

		template<typename OutIterator, typename T>
		void readBuffer(Buffer<T> buffer, OutIterator out);

		template<typename OutIterator, typename EventRange, typename T>
		void readBuffer(Buffer<T> buffer, size_t offset, size_t size,
			OutIterator out, EventRange waitList);

		template<typename OutIterator, typename EventRange, typename T>
		void readBuffer(Buffer<T> buffer, OutIterator out, EventRange waitList);

		template<typename OutIterator, typename T>
		auto readBufferAsync(Buffer<T> buffer, size_t offset, size_t size, OutIterator out) -> Event;

		template<typename OutIterator, typename T>
		auto readBufferAsync(Buffer<T> buffer, OutIterator out) -> Event;

		template<typename OutIterator, typename EventRange, typename T>
		auto readBufferAsync(Buffer<T> buffer, size_t offset, size_t size,
			OutIterator out, EventRange waitList) -> Event;

		template<typename OutIterator, typename EventRange, typename T>
		auto readBufferAsync(Buffer<T> buffer, OutIterator out, EventRange waitList) -> Event;

		//================================================================================
		// Overloads to access clEnqueueReadBufferRect
		//================================================================================

		template<typename OutIterator, typename T, size_t N>
		void readBufferRect(
			Buffer<T> buffer,
			size_t[N] bufferOrigin, size_t[N] hostOrigin, size_t[N] region,
			size_t bufferRowPitch, size_t bufferSlicePitch,
			size_t hostRowPitch, size_t hostSlicePitch,
			OutIterator out);

		template<typename OutIterator, typename EventRange, typename T, size_t N>
		void readBufferRect(
			Buffer<T> buffer,
			size_t[N] bufferOrigin, size_t[N] hostOrigin, size_t[N] region,
			size_t bufferRowPitch, size_t bufferSlicePitch,
			size_t hostRowPitch, size_t hostSlicePitch,
			OutIterator out, EventRange waitList);

		template<typename OutIterator, typename T, size_t N>
		auto readBufferRectAsync(
			Buffer<T> buffer,
			size_t[N] bufferOrigin, size_t[N] hostOrigin, size_t[N] region,
			size_t bufferRowPitch, size_t bufferSlicePitch,
			size_t hostRowPitch, size_t hostSlicePitch,
			OutIterator out) -> Event;

		template<typename OutIterator, typename EventRange, typename T, size_t N>
		auto readBufferRectAsync(
			Buffer<T> buffer,
			size_t[N] bufferOrigin, size_t[N] hostOrigin, size_t[N] region,
			size_t bufferRowPitch, size_t bufferSlicePitch,
			size_t hostRowPitch, size_t hostSlicePitch,
			OutIterator out, EventRange waitList) -> Event;

		//================================================================================
		// Marker & Barrier
		//================================================================================

		template<typename EventRange>
		auto marker(EventRange waitList) const -> Event;
		auto marker() const -> Event;

		template<typename EventRange>
		auto barrier(EventRange waitList) const -> Event;
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
