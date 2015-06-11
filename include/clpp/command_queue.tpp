#ifndef CLPP_COMMAND_QUEUE_H
	#error "Do not include this file directly."
#endif

namespace cl {
	auto CommandQueue::operator=(const CommandQueue & rhs) -> CommandQueue & {

	}

	//================================================================================
	// Returns the CommandQueueExecutor for non-delayed execution
	//================================================================================

	auto CommandQueue::getExecutor() const -> CommandQueueExecutor {
		return {*this};
	}

	//================================================================================
	// Overloads to access clEnqueueReadBuffer
	//================================================================================

	template<typename OutputIterator, typename T>
	void CommandQueue::readBufferBlocked(
		Buffer<T> const& buffer, size_t offset,
		OutputIterator first, OutputIterator last
	) const {
		getExecutor().readBufferBlocked(buffer, offset, first, last);
	}

	template<typename OutputIterator, typename T>
	void CommandQueue::readBufferBlocked(
		Buffer<T> const& buffer, OutputIterator first, OutputIterator last
	) const {
		getExecutor().readBufferBlocked(buffer, first, last);
	}

	template<typename OutputIterator, typename T>
	auto CommandQueue::readBuffer(
		Buffer<T> const& buffer, size_t offset,
		OutputIterator first, OutputIterator last
	) const -> Event {
		return getExecutor().readBuffer(buffer, offset, first, last);
	}

	template<typename OutputIterator, typename T>
	auto CommandQueue::readBuffer(
		Buffer<T> const& buffer, OutputIterator first, OutputIterator last
	) const -> Event {
		return getExecutor().readBuffer(buffer, first, last);
	}

	//================================================================================
	// Overloads to access clEnqueueWriteBuffer
	//================================================================================

	template<typename InputIterator, typename T>
	void CommandQueue::writeBufferBlocked(
		Buffer<T> const& buffer, size_t offset,
		InputIterator first, InputIterator last
	) const {
		getExecutor().writeBufferBlocked(buffer, offset, first, last);
	}

	template<typename InputIterator, typename T>
	void CommandQueue::writeBufferBlocked(
		Buffer<T> const& buffer, InputIterator first, OutputIterator last
	) const {
		getExecutor().writeBufferBlocked(buffer, first, last);
	}

	template<typename InputIterator, typename T>
	auto CommandQueue::writeBuffer(
		Buffer<T> const& buffer, size_t offset,
		InputIterator first, InputIterator last
	) const -> Event {
		return getExecutor().writeBuffer(buffer, offset, first, last);
	}

	template<typename InputIterator, typename T>
	auto CommandQueue::writeBuffer(
		Buffer<T> const& buffer, InputIterator first, OutputIterator last
	) const -> Event {
		return getExecutor().writeBuffer(buffer, first, last);
	}

	//================================================================================
	// Overloads to access clEnqueueReadBufferRect
	//================================================================================

	template<typename OutIterator, typename T>
	void CommandQueue::readBufferRectBlocked(
		Buffer<T> const& buffer,
		std::array<size_t, 3> const& bufferOrigin,
		std::array<size_t, 3> const& hostOrigin,
		std::array<size_t, 3> const& region,
		size_t bufferRowPitch, size_t bufferSlicePitch,
		size_t hostRowPitch, size_t hostSlicePitch,
		OutIterator first
	) const {
		getExecutor().readBufferBlocked(
			buffer, bufferOrigin, hostOrigin, region,
			bufferRowPitch, bufferSlicePitch,
			hostRowPitch, hostSlicePitch, first);
	}


	template<typename OutIterator, typename T>
	auto CommandQueue::readBufferRect(
		Buffer<T> const& buffer,
		std::array<size_t, 3> const& bufferOrigin,
		std::array<size_t, 3> const& hostOrigin,
		std::array<size_t, 3> const& region,
		size_t bufferRowPitch, size_t bufferSlicePitch,
		size_t hostRowPitch, size_t hostSlicePitch,
		OutIterator first
	) const -> Event {
		return getExecutor().readBufferRect(
			buffer, bufferOrigin, hostOrigin, region,
			bufferRowPitch, bufferSlicePitch,
			hostRowPitch, hostSlicePitch, first)
	}

	//================================================================================
	// Overloads to access clEnqueueWriteBufferRect
	//================================================================================

	template<typename OutIterator, typename T>
	void CommandQueue::writeBufferRectBlocked(
		Buffer<T> const& buffer,
		std::array<size_t, 3> const& bufferOrigin,
		std::array<size_t, 3> const& hostOrigin,
		std::array<size_t, 3> const& region,
		size_t bufferRowPitch, size_t bufferSlicePitch,
		size_t hostRowPitch, size_t hostSlicePitch,
		OutIterator first
	) const {
		getExecutor().writeBufferRectBlocked(
			buffer, bufferOrigin, hostOrigin, region,
			bufferRowPitch, bufferSlicePitch,
			hostRowPitch, hostSlicePitch, first)
	}

	template<typename OutIterator, typename T>
	auto CommandQueue::writeBufferRect(
		Buffer<T> const& buffer,
		std::array<size_t, 3> const& bufferOrigin,
		std::array<size_t, 3> const& hostOrigin,
		std::array<size_t, 3> const& region,
		size_t bufferRowPitch, size_t bufferSlicePitch,
		size_t hostRowPitch, size_t hostSlicePitch,
		OutIterator first
	) const -> Event {
		return getExecutor().writeBufferRect(
			buffer, bufferOrigin, hostOrigin, region,
			bufferRowPitch, bufferSlicePitch,
			hostRowPitch, hostSlicePitch, first);
	}

	//================================================================================
	// Overloads to access clEnqueueCopyBuffer
	//================================================================================

	template<typename T, typename V>
	auto CommandQueue::copyBuffer(
		Buffer<T> const& src, Buffer<V> const& dst,
		size_t srcOffset, size_t dstOffset, size_t size
	) const -> Event {
		return getExecutor().copyBuffer(
			src, dst, srcOffset, dstOffset, size);
	}

	template<typename T, typename V>
	auto CommandQueue::copyBuffer(
		Buffer<T> const& src, Buffer<V> const& dst
	) const -> Event {
		return getExecutor().copyBuffer(src, dst);
	}

	//================================================================================
	// Overloads to access clEnqueueCopyBufferRect
	//================================================================================

	template<typename T, typename V>
	auto CommandQueue::copyBufferRect(
		Buffer<T> const& src, Buffer<V> const& dst,
		std::array<size_t, 3> const& srcOrigin,
		std::array<size_t, 3> const& dstOrigin,
		std::array<size_t, 3> const& region,
		size_t srcRowPitch, size_t srcSlicePitch,
		size_t dstRowPitch, size_t dstSlidePitch
	) const -> Event {
		return getExecutor().copyBufferRect(
			src, dst, srcOrigin, dstOrigin, region,
			srcRowPitch, srcSlicePitch,
			dstRowPitch, dstSlidePitch);
	}

	//================================================================================
	// Overloads to access clEnqueueFillBuffer
	//================================================================================

	template<typename T>
	auto CommandQueue::fillBuffer(
		Buffer<T> const& buffer, T const& value, size_t offset, size_t size
	) const -> Event {
		return getExecutor().fillBuffer(buffer, value, offset, size);
	}

	template<typename T>
	auto CommandQueue::fillBuffer(Buffer<T> const& buffer, T const& value) const -> Event {
		return getExecutor().fillBuffer(buffer, value);
	}

	//================================================================================
	// Overloads to access clEnqueueMapBuffer
	//================================================================================

	template<typename T>
	void CommandQueue::mapBufferBlocked(
		Buffer<T> const& buffer, MapAccess access, size_t offset, size_t size, MappedMemory<T> & result
	) const {
		getExecutor().mapBufferBlocked(buffer, access, offset, size, result);
	}

	template<typename T>
	void CommandQueue::mapBufferBlocked(
		Buffer<T> const& buffer, MapAccess access, MappedMemory<T> & result
	) const {
		getExecutor().mapBufferBlocked(buffer, access, result);
	}

	template<typename T>
	auto CommandQueue::mapBuffer(
		Buffer<T> const& buffer, MapAccess access, size_t offset, size_t size, MappedMemory<T> & result
	) const -> Event {
		return getExecutor().mapBuffer(buffer, access, offset, size, result);
	}

	template<typename T>
	auto CommandQueue::mapBuffer(
		Buffer<T> const& buffer, MapAccess access, MappedMemory<T> & result
	) const -> Event {
		return getExecutor().mapBuffer(buffer, access, result);
	}

	//================================================================================
	// ND Range Kernel Execution
	//================================================================================

	auto CommandQueue::execute1DRange(
		Kernel const& kernel,
		size_t globalWorkOffset,
		size_t globalWorkSize,
		size_t localWorkSize
	) const -> Event {
		return getExecutor().execute1DRange(
			kernel, globalWorkOffset, globalWorkSize, localWorkSize);
	}

	template<size_t N>
	auto CommandQueue::executeNDRange(
		Kernel const& kernel,
		NDRange<N> const& globalWorkOffset,
		NDRange<N> const& globalWorkSize,
		NDRange<N> const& localWorkSize
	) const -> Event {
		return getExecutor().executeNDRange<N>(
			kernel, globalWorkOffset, globalWorkSize, localWorkSize);
	}

	//================================================================================
	// Wait (for events), Marker & Barrier and When for async calls
	//================================================================================

	template<typename EventRange>
	auto when(EventRange const& waitList) const -> CommandQueueExecutor {
		return {*this, waitList.begin(), waitList.end()};
	}

	template<typename...Events>
	auto when(Events... events) const -> CommandQueueExecutor {
		auto waitList = utility::make_array(events...);
		return {*this, waitList.begin(), waitList.end()};
	}

	auto CommandQueue::marker() const -> Event {
		return getExecutor().marker();
	}

	auto CommandQueue::barrier() const -> Event {
		return getExecutor().barrier();
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
