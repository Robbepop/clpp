#ifdef  CLPP_BUFFER_IPP
	#error "multiple inclusions of the same implementation file"
#else
#define CLPP_BUFFER_IPP

#ifndef CLPP_BUFFER_HPP
	#error "header file has not been included; maybe it isn't required anymore?"
	#include "clpp/buffer.hpp"
#endif

#include "utility/to_underlying.hpp"
#include "clpp/detail/cl_function.hpp"

namespace cl {

	//=====================================================================
	// Constructors
	//=====================================================================

	template<typename T>
	Buffer<T>::Buffer(): MemObject{} {}

	template<typename T>
	Buffer<T>::Buffer(
		Context context,
		size_t size,
		DeviceAccess deviceAccess,
		HostAccess hostAccess
	){
		using namespace utility;
		auto error = RetCode::getPreset();
		auto flags = to_underlying(deviceAccess) | to_underlying(hostAccess);
		auto sizeInBytes = size * sizeof(T);
		auto id    = clCreateBuffer(context.get(), flags, sizeInBytes, nullptr, error.data());
		detail::handleError(detail::CLFunction::clCreateBuffer(), error);
		m_object = id;
	}

	template<typename T>
	template<typename InputIterator>
	Buffer<T>::Buffer(
		Context context,
		InputIterator first,
		InputIterator last,
		TransferMode transferMode,
		DeviceAccess deviceAccess,
		HostAccess hostAccess
	){
		using namespace utility;
		auto error = RetCode::getPreset();
		auto flags = to_underlying(transferMode)
		           | to_underlying(deviceAccess)
		           | to_underlying(hostAccess);
		auto sizeInBytes = std::distance(first, last) * sizeof(T);
		auto id    = clCreateBuffer(context.get(), flags, sizeInBytes, (void *) &*first, error.data());
		detail::handleError(detail::CLFunction::clCreateBuffer(), error);
		m_object = id;
	}

	template<typename T>
	template<typename InputRange, typename>
	Buffer<T>::Buffer(
		Context context,
		InputRange const& range,
		TransferMode transferMode,
		DeviceAccess deviceAccess,
		HostAccess hostAccess
	){
		auto id = Buffer<T>{context, range.begin(), range.end(), transferMode, deviceAccess, hostAccess};
		m_object = id;
	}

	//=====================================================================
	// Wrapped OpenCL API
	//=====================================================================

	template<typename T>
	auto Buffer<T>::operator=(Buffer<T> const& rhs) -> Buffer & {
		if (this != &rhs) {
		    MemObject::operator=(rhs);
		}
		return *this;
	}

	template<typename T>
	auto Buffer<T>::createSubBuffer(
		size_t origin, size_t size,
		DeviceAccess deviceAccess,
		HostAccess hostAccess
	) const -> Buffer<T> {
		using namespace utility;
		using namespace detail;
		auto error = cl_int{CL_INVALID_VALUE};
		auto flags = to_underlying(deviceAccess)
		           | to_underlying(hostAccess);
		auto region   = cl_buffer_region{origin, size};
		auto bufferId = clCreateSubBuffer(get(), flags,
			CL_BUFFER_CREATE_TYPE_REGION, std::addressof(region), std::addressof(error));
		detail::handleError(CLFunction::clCreateSubBuffer(), error);
		return {bufferId};
	}

	template<typename T>
	auto Buffer<T>::size() const -> size_t {
		return getSize();
	}

	template<typename T>
	auto Buffer<T>::getSizeInBytes() const -> size_t {
		return MemObject::getSize();
	}

	template<typename T>
	auto Buffer<T>::getSize() const -> size_t {
		return getSizeInBytes() / sizeof(T);
	}

	template<typename T>
	auto Buffer<T>::getOffset() const -> size_t {
		return MemObject::getOffset() / sizeof(T);
	}

	template<typename T>
	auto Buffer<T>::getHostPtr() const -> T* {
		return reinterpret_cast<T*>(MemObject::getHostPtr());
	}

	template<typename T>
	auto Buffer<T>::getAssociatedBuffer() const
		-> boost::optional<std::unique_ptr<Buffer<T>>>
	{
		const auto memId = getInfo<cl_mem>(CL_MEM_ASSOCIATED_MEMOBJECT);
		if (memId == nullptr) {
			return {};
		}
		return {std::make_unique<Buffer<T>>(memId)};
	}
}

#endif
