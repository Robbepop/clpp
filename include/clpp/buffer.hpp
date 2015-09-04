#ifndef CLPP_BUFFER_HPP
#define CLPP_BUFFER_HPP

#include "clpp/mem_object.hpp"
#include "clpp/device_access.hpp"
#include "clpp/host_access.hpp"
#include "clpp/transfer_mode.hpp"
#include "clpp/utility/concepts.hpp"

namespace cl {
	template<typename T>
	class Buffer final : public MemObject {
	public:
		using value_type = T;

		//=====================================================================
		// Constructors
		//=====================================================================
	public:

		using MemObject::MemObject;

		Buffer();

		Buffer(
			Context context,
			size_t size,
			DeviceAccess deviceAccess = DeviceAccess::readWrite,
			HostAccess hostAccess     = HostAccess::readWrite
		);

		template<typename InputIterator>
		Buffer(
			Context context,
			InputIterator first,
			InputIterator last,
			TransferMode transferMode = TransferMode::copy,
			DeviceAccess deviceAccess = DeviceAccess::readWrite,
			HostAccess hostAccess     = HostAccess::readWrite
		);

		template<typename InputRange,
			CLPP_REQUIRES(concept::is_range<InputRange>::value)>
		Buffer(
			Context context,
			InputRange const& range,
			TransferMode transferMode = TransferMode::copy,
			DeviceAccess deviceAccess = DeviceAccess::readWrite,
			HostAccess hostAccess     = HostAccess::readWrite
		);

		//=====================================================================
		// Wrapped OpenCL API
		//=====================================================================

		auto operator=(Buffer const& rhs) -> Buffer &;

		auto createSubBuffer(
			size_t origin, size_t size,
			DeviceAccess deviceAccess = DeviceAccess::readWrite,
			HostAccess hostAccess     = HostAccess::readWrite
		) const -> Buffer<T>;

		auto size() const           -> size_t;
		auto getSizeInBytes() const -> size_t;

		auto getSize() const    -> size_t;
		auto getOffset() const  -> size_t;

		auto getHostPtr() const -> T*;
		auto getAssociatedBuffer() const -> boost::optional<std::unique_ptr<Buffer<T>>>;
	};
}

#endif
