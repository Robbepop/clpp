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

	template<>
	struct ObjectHandler<cl_context> final {
		using cl_type = cl_context;
		using info_type = cl_context_info;
		using exception_type = ContextException;

		static auto release(cl_context id) { return clReleaseContext(id); }

		static auto retain(cl_context id) { return clRetainContext(id); }

		static auto getInfo
		(
			cl_context context,
			cl_context_info param_name,
			size_t param_value_size,
			void *param_value,
			size_t *param_value_size_ret
		) {
			return clGetContextInfo(
				context, param_name, param_value_size, param_value, param_value_size_ret);
		}
	};

	class Context final : public detail::Object<cl_context> {
	public:
		//================================================================================
		// Basic Constructors and Copy-Assignment
		//================================================================================

		Context();
		Context(cl_type context);
		Context(const Context & context);

		Context& operator=(const Context & rhs);

		//================================================================================
		// Special Constructors
		//================================================================================

		template<typename Function, typename T>
		Context(
			ContextProperties const& properties,
			std::vector<Device> const& devices,
			Function callback,
			T* user_data
		);

		Context(
			ContextProperties const& properties,
			std::vector<Device> const& devices
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
		// Information access helper methods.
		//================================================================================

		auto getReferenceCount() const -> cl_uint;
		auto getNumDevices() const -> cl_uint;
		auto getDevices() const -> std::vector<Device>;
		auto getProperties() const -> ContextProperties;
	};
}

#include "clpp/context.tpp"
#endif