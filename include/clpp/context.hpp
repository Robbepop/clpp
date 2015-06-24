#ifndef CLPP_CONTEXT_HPP
#define CLPP_CONTEXT_HPP

#include "clpp/detail/error_handler.hpp"
#include "clpp/detail/object.hpp"
#include "clpp/device.hpp"
#include "clpp/command_queue.hpp"
#include "clpp/context_properties.hpp"
#include "clpp/device_access.hpp"
#include "clpp/host_access.hpp"
#include "clpp/transfer_mode.hpp"
#include "clpp/buffer.hpp"
#include "clpp/program.hpp"

#include "utility/concepts.hpp"

#include <cstdint>

namespace cl {
	class ContextProperties;
	class ContextError;

	namespace detail {
		template<>
		struct ObjectHandler<cl_context> final {
			using cl_type   = cl_context;
			using info_type = cl_context_info;

			static constexpr auto retain  = clRetainContext;
			static constexpr auto release = clReleaseContext;
			static constexpr auto getInfo = clGetContextInfo;
		};
	}

	class Context final : public detail::Object<cl_context> {
	public:
		//================================================================================
		// Basic Constructors and Copy-Assignment
		//================================================================================

		using detail::Object<cl_type>::Object;

		auto inline operator=(const Context & rhs) -> Context &;

		//================================================================================
		// Named Constructors
		//================================================================================

		inline
		static auto createDefault() -> Context;

		template<typename DeviceIterator>
		static auto createForDevices(
			DeviceIterator first, DeviceIterator last
		) -> Context;

		template<typename DeviceRange,
			CLPP_REQUIRES(concept::is_range<DeviceRange>::value)>
		static auto createForDevices(
			DeviceRange const& devices
		) -> Context;

		template<typename... Devices>
		static auto createForDevices(
			Devices&&... devices
		) -> Context;

		inline
		static auto createForType(
			DeviceType type
		) -> Context;

		inline
		static auto createForType(
			ContextProperties const& properties,
			DeviceType type
		) -> Context;

		//================================================================================
		// Special Constructors
		//================================================================================

		template<typename DeviceIterator, typename Function, typename T>
		Context(
			ContextProperties const& properties,
			DeviceIterator firstDevice,
			DeviceIterator lastDevice,
			Function callback,
			T* user_data
		);

		template<typename DeviceIterator>
		Context(
			ContextProperties const& properties,
			DeviceIterator firstDevice,
			DeviceIterator lastDevice
		);

		template<typename Function, typename T>
		Context(
			ContextProperties const& properties,
			DeviceType type,
			Function callback,
			T* user_data
		);

		//================================================================================
		// Create Command Queue Objects
		//================================================================================

		auto inline createCommandQueue(Device const& device) const -> CommandQueue;

		//================================================================================
		// Create Memory Objects
		//================================================================================

		template<typename T>
		auto createBuffer(
			size_t size,
			DeviceAccess deviceAccess = DeviceAccess::readWrite,
			HostAccess hostAccess     = HostAccess::readWrite
		) const -> Buffer<T>;

		template<typename T, typename InputIterator>
		auto createBuffer(
			InputIterator first,
			InputIterator last,
			TransferMode transferMode = TransferMode::copy,
			DeviceAccess deviceAccess = DeviceAccess::readWrite,
			HostAccess hostAccess     = HostAccess::readWrite
		) const -> Buffer<T>;

		template<typename T, typename InputRange,
			CLPP_REQUIRES(concept::is_range<InputRange>::value)>
		auto createBuffer(
			InputRange const& range,
			TransferMode transferMode = TransferMode::copy,
			DeviceAccess deviceAccess = DeviceAccess::readWrite,
			HostAccess hostAccess     = HostAccess::readWrite
		) const -> Buffer<T>;

		//================================================================================
		// Create Program Objects
		//================================================================================

		auto inline createProgramWithSource(std::string const& source) const -> Program;

		//================================================================================
		// Information access helper methods.
		//================================================================================

		auto inline getReferenceCount() const -> cl_uint;
		auto inline getNumDevices() const     -> cl_uint;
		auto inline getDevices() const        -> std::vector<Device>;
		auto inline getProperties() const     -> ContextProperties;
	};
}

#endif
