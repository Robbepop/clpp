#ifndef CLPP_COMMAND_QUEUE_H
	#error "Do not include this file directly."
#endif

namespace cl {
	auto CommandQueue::operator=(const CommandQueue & rhs) -> CommandQueue & {

	}

	//================================================================================
	// Overloads to access clEnqueueReadBuffer
	//================================================================================

	template<typename OutputIterator, typename T>
	void CommandQueue::readBuffer(Buffer<T> buffer, size_t offset,
		OutputIterator first, OutputIterator last
	) const {

	}

	template<typename OutputIterator, typename T>
	void CommandQueue::readBuffer(Buffer<T> buffer, OutputIterator first) const {

	}

	template<typename OutputIterator, typename T>
	auto CommandQueue::readBufferAsync(Buffer<T> buffer, size_t offset,
		OutputIterator first, OutputIterator last
	) const -> Event {

	}

	template<typename OutputIterator, typename T>
	auto CommandQueue::readBufferAsync(Buffer<T> buffer, OutputIterator first) const -> Event {

	}

	//================================================================================
	// Overloads to access clEnqueueWriteBuffer
	//================================================================================

	template<typename InputIterator, typename T>
	void CommandQueue::writeBuffer(Buffer<T> buffer, size_t offset,
		InputIterator first, InputIterator last
	) const {

	}

	template<typename InputIterator, typename T>
	void CommandQueue::writeBuffer(Buffer<T> buffer, InputIterator first) const {

	}

	template<typename InputIterator, typename T>
	auto CommandQueue::writeBufferAsync(Buffer<T> buffer, size_t offset,
		InputIterator first, InputIterator last
	) const -> Event {

	}

	template<typename InputIterator, typename T>
	auto CommandQueue::writeBufferAsync(Buffer<T> buffer, InputIterator first) const -> Event {

	}

	//================================================================================
	// Overloads to access clEnqueueReadBufferRect
	//================================================================================

	template<typename OutIterator, typename T>
	void CommandQueue::readBufferRect(
		Buffer<T> buffer,
		std::array<size_t, 3> const& bufferOrigin,
		std::array<size_t, 3> const& hostOrigin,
		std::array<size_t, 3> const& region,
		size_t bufferRowPitch, size_t bufferSlicePitch,
		size_t hostRowPitch, size_t hostSlicePitch,
		OutIterator first
	) const {

	}


	template<typename OutIterator, typename T>
	auto CommandQueue::readBufferRectAsync(
		Buffer<T> buffer,
		std::array<size_t, 3> const& bufferOrigin,
		std::array<size_t, 3> const& hostOrigin,
		std::array<size_t, 3> const& region,
		size_t bufferRowPitch, size_t bufferSlicePitch,
		size_t hostRowPitch, size_t hostSlicePitch,
		OutIterator first
	) const -> Event {

	}

	//================================================================================
	// Overloads to access clEnqueueWriteBufferRect
	//================================================================================

	template<typename OutIterator, typename T>
	void CommandQueue::writeBufferRect(
		Buffer<T> buffer,
		std::array<size_t, 3> const& bufferOrigin,
		std::array<size_t, 3> const& hostOrigin,
		std::array<size_t, 3> const& region,
		size_t bufferRowPitch, size_t bufferSlicePitch,
		size_t hostRowPitch, size_t hostSlicePitch,
		OutIterator out
	) const {

	}

	template<typename OutIterator, typename T>
	auto CommandQueue::writeBufferRectAsync(
		Buffer<T> buffer,
		std::array<size_t, 3> const& bufferOrigin,
		std::array<size_t, 3> const& hostOrigin,
		std::array<size_t, 3> const& region,
		size_t bufferRowPitch, size_t bufferSlicePitch,
		size_t hostRowPitch, size_t hostSlicePitch,
		OutIterator out
	) const -> Event {

	}

	//================================================================================
	// Overloads to access clEnqueueCopyBuffer
	//================================================================================

	template<typename T, typename V>
	void CommandQueue::copyBuffer(Buffer<T> src, Buffer<V> dst,
		size_t srcOffset, size_t dstOffset, size_t size
	) const {

	}

	template<typename T, typename V>
	void CommandQueue::copyBuffer(Buffer<T> src, Buffer<V> dst) const {

	}

	template<typename T, typename V>
	auto CommandQueue::copyBufferAsync(Buffer<T> src, Buffer<V> dst,
		size_t srcOffset, size_t dstOffset, size_t size
	) const -> Event {

	}

	template<typename T, typename V>
	auto CommandQueue::copyBufferAsync(Buffer<T> src, Buffer<V> dst) const -> Event {

	}

	//================================================================================
	// Overloads to access clEnqueueCopyBufferRect
	//================================================================================

	template<typename T, typename V>
	void CommandQueue::copyBufferRect(Buffer<T> src, Buffer<V> dest,
		std::array<size_t, 3> const& srcOrigin,
		std::array<size_t, 3> const& dstOrigin,
		std::array<size_t, 3> const& region,
		size_t srcRowPitch, size_t srcSlicePitch,
		size_t dstRowPitch, size_t dstSlidePitch
	) const {

	}

	template<typename T, typename V>
	auto CommandQueue::copyBufferRectAsync(Buffer<T> src, Buffer<V> dest,
		std::array<size_t, 3> const& srcOrigin,
		std::array<size_t, 3> const& dstOrigin,
		std::array<size_t, 3> const& region,
		size_t srcRowPitch, size_t srcSlicePitch,
		size_t dstRowPitch, size_t dstSlidePitch
	) const -> Event {

	}

	//================================================================================
	// Overloads to access clEnqueueFillBuffer
	//================================================================================

	template<typename T>
	void CommandQueue::fillBuffer(Buffer<T> buffer, T const& value, size_t offset, size_t size) const {

	}

	template<typename T>
	void CommandQueue::fillBuffer(Buffer<T> buffer, T const& value) const {

	}

	template<typename T>
	auto CommandQueue::fillBufferAsync(Buffer<T> buffer, T const& value, size_t offset, size_t size) const -> Event {

	}

	template<typename T>
	auto CommandQueue::fillBufferAsync(Buffer<T> buffer, T const& value) const -> Event {

	}

	//================================================================================
	// Overloads to access clEnqueueMapBuffer
	//================================================================================

	template<typename T>
	void CommandQueue::mapBuffer(Buffer<T>, MapAccess access, MappedMemory<T> & result,
		size_t offset, size_t size
	) const {

	}

	template<typename T>
	void CommandQueue::mapBuffer(Buffer<T>, MapAccess access, MappedMemory<T> & result) const {

	}

	template<typename T>
	auto CommandQueue::mapBufferAsync(Buffer<T>, MapAccess access, MappedMemory<T> & result,
		size_t offset, size_t size
	) const -> Event {

	}

	template<typename T>
	auto CommandQueue::mapBufferAsync(Buffer<T>, MapAccess access, MappedMemory<T> & result) const -> Event {

	}

	//================================================================================
	// ND Range Kernel Execution
	//================================================================================

	template<typename T>
	auto execute1DRange(
		Kernel const& kernel,
		size_t globalWorkOffset,
		size_t globalWorkSize,
		size_t localWorkSize
	) const -> Event {

	}

	template<typename T>
	auto execute2DRange(
		Kernel const& kernel,
		NDRange<2> const& globalWorkOffset,
		NDRange<2> const& globalWorkSize,
		NDRange<2> const& localWorkSize
	) const -> Event {

	}

	template<typename T>
	auto execute3DRange(
		Kernel const& kernel,
		NDRange<3> const& globalWorkOffset,
		NDRange<3> const& globalWorkSize,
		NDRange<3> const& localWorkSize
	) const -> Event {

	}

	template<typename T, size_t N>
	auto executeNDRange(
		Kernel const& kernel,
		NDRange<N> const& globalWorkOffset,
		NDRange<N> const& globalWorkSize,
		NDRange<N> const& localWorkSize
	) const -> Event {

	}

	//================================================================================
	// Wait (for events), Marker & Barrier and When for async calls
	//================================================================================

	template<typename EventRange>
	auto CommandQueue::when(EventRange const& waitList) -> CommandQueue & {

	}

	template<typename EventRange>
	auto CommandQueue::when(EventRange const& waitList) const -> CommandQueue const& {

	}

	template<typename EventRange>
	auto CommandQueue::marker() const -> Event {

	}

	template<typename EventRange>
	auto CommandQueue::barrier() const -> Event {

	}

	//================================================================================
	// Flush & Finish
	//================================================================================

	void CommandQueue::flush() const {
		detail::error::handle(clFlush(get()));
	}

	void CommandQueue::finish() const {
		detail::error::handle(clFinish(get()));
	}

	//================================================================================
	// Information Getters
	//================================================================================

	auto CommandQueue::getContext() const -> Context {
		return {getInfo<cl_context>(CL_QUEUE_CONTEXT)};
	}

	auto CommandQueue::getDevice() const -> Device {
		return {getInfo<cl_device_id>(CL_QUEUE_DEVICE)};
	}

	auto CommandQueue::getReferenceCount() const -> cl_uint {
		return getInfo<cl_uint>(CL_QUEUE_REFERENCE_COUNT);
	}

	auto CommandQueue::getProperties() const -> CommandQueueProperties {
		return {getInfo<cl_command_queue_properties>(CL_QUEUE_PROPERTIES)};
	}

	auto CommandQueue::getSize() const -> cl_uint {
		return getInfo<cl_uint>(CL_QUEUE_SIZE);
	}

	auto CommandQueue::size() const -> cl_uint {
		return getSize();
	}
}
