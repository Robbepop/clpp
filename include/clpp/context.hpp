#ifndef CLPP_CONTEXT_H
#define CLPP_CONTEXT_H

#include "clpp/detail/error_handler.hpp"
#include "clpp/detail/object.hpp"
#include "clpp/device.hpp"
#include "clpp/context_properties.hpp"

#include <cstdint>

namespace cl {
	class ContextProperties;
	class ContextError;

	namespace detail {
		template<>
		struct ObjectHandler<cl_context> final {
			using cl_type = cl_context;
			using info_type = cl_context_info;
			using exception_type = ContextError;

			static auto release(cl_type id) { return clReleaseContext(id); }

			static auto retain(cl_type id) { return clRetainContext(id); }

			static auto getInfo(
				cl_type   context,
				info_type param_name,
				size_t    param_value_size,
				void *    param_value,
				size_t *  param_value_size_ret
			) {
				return clGetContextInfo(
					context, param_name, param_value_size, param_value, param_value_size_ret);
			}
		};
	}

	class Context final : public detail::Object<cl_context> {
	public:
		//================================================================================
		// Basic Constructors and Copy-Assignment
		//================================================================================

		using detail::Object<cl_type>::Object;

		Context& operator=(const Context & rhs);

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

		Context(
			ContextProperties const& properties,
			DeviceType type
		);

		//================================================================================
		// Create Memory Objects
		//================================================================================

		template<typename T>
		auto createBuffer(
			size_t size,
			DeviceAccess deviceAccess = DeviceAccess::readWrite,
			HostAccess hostAccess     = HostAccess::readWrite
		) const -> Buffer<T>;

		template<typename InputIterator>
		auto createBuffer(
			InputIterator first,
			InputIterator last,
			TransferMode transferMode,
			DeviceAccess deviceAccess = DeviceAccess::readWrite,
			HostAccess hostAccess     = HostAccess::readWrite
		) const -> Buffer<InputIterator::value_type>;

		template<typename InputRange>
		auto createBuffer(
			InputRange const& range,
			TransferMode transferMode = TransferMode::none,
			DeviceAccess deviceAccess = DeviceAccess::readWrite,
			HostAccess hostAccess     = HostAccess::readWrite
		) const -> Buffer<InputRange::value_type>;

		//================================================================================
		// Create Program Objects
		//================================================================================

		auto createProgramWithSource(std::string const& source) const -> Program;

		//================================================================================
		// Information access helper methods.
		//================================================================================

		auto getReferenceCount() const -> cl_uint;
		auto getNumDevices() const     -> cl_uint;
		auto getDevices() const        -> std::vector<Device>;
		auto getProperties() const     -> ContextProperties;
	};
}

#include "clpp/context.tpp"
#endif
