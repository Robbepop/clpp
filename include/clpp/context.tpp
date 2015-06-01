#ifndef CLPP_CONTEXT_H
	#error "Do not include this file directly."
#endif

namespace cl {
	//====================================================================================
	// Copy-Assignment
	//====================================================================================

	Context& Context::operator=(const Context & rhs) {
        if (this != &rhs) {
            detail::Object<cl_type>::operator=(rhs);
        }
        return *this;
	}


	//====================================================================================
	// Special Constructors
	//====================================================================================

	template<typename Function, typename T>
	Context::Context(
		ContextProperties const& properties,
		std::vector<Device> const& devices,
		Function callback,
		T* user_data
	){
		struct callback_data {
			Function callback;
			T* user_data;
		};
		auto cbWrapper = new callback_data{callback, user_data};
		auto ids       = std::vector<cl_device_id>{};
		ids.reserve(devices.size());
		std::transform(devices.cbegin(), devices.cend(), ids.begin(),
			[](auto device) {
				return device.get();
			});		
		auto error  = cl_int{CL_INVALID_VALUE};
		auto contex = clCreateContext(
			properties.data().data(),
			ids.size(), ids.data(),
			[](
				const char * error_info,
				const void * private_info,
				size_t cb,
				void * user_data
			) {
				auto temp = reinterpret_cast<callback_data*>(user_data);
				auto errorString = std::string{error_info};
				auto privateData = std::vector<char>{
					reinterpret_cast<const char*>(private_info),
					reinterpret_cast<const char*>(private_info) + cb};
				auto userData    = temp->user_data;
				delete temp; // call delete before calling user's callback
				             // to ensure that data is freed even if the user's
				             // callback throws an exception.
				temp->callback(errorString, privateData, userData);
			},
			std::addressof(cbWrapper),
			std::addressof(error)
		);
		if (detail::error::handle<exception_type>(error)) {
			m_object = contex;
		}
	}

	Context::Context(
		ContextProperties const& properties,
		std::vector<Device> const& devices
	){
		auto ids = std::vector<cl_device_id>{};
		ids.reserve(devices.size());
		std::transform(devices.cbegin(), devices.cend(), ids.begin(),
			[](auto device) {
				return device.get();
			});
		auto error  = cl_int{CL_INVALID_VALUE};
		auto contex = clCreateContext(
			properties.data().data(),
			ids.size(), ids.data(),
			nullptr, nullptr,
			std::addressof(error)
		);
		if (detail::error::handle<exception_type>(error)) {
			m_object = contex;
		}
	}

	template<typename Function, typename T>
	Context::Context(
		ContextProperties const& properties,
		DeviceType type,
		Function callback,
		T* user_data
	){
		struct callback_data {
			Function callback;
			T* user_data;
		};
		auto cbWrapper = new callback_data{callback, user_data};
		auto error  = cl_int{CL_INVALID_VALUE};
		auto contex = clCreateContextFromType(
			properties.data().data(),
			static_cast<std::underlying_type<DeviceType>::type>(type),
			[](
				const char * error_info,
				const void * private_info,
				size_t cb,
				void * user_data
			) {
				auto temp = reinterpret_cast<callback_data*>(user_data);
				auto errorString = std::string{error_info};
				auto privateData = std::vector<char>{
					reinterpret_cast<const char*>(private_info),
					reinterpret_cast<const char*>(private_info) + cb};
				auto userData    = temp->user_data;
				delete temp; // call delete before calling user's callback
				             // to ensure that data is freed even if the user's
				             // callback throws an exception.
				temp->callback(errorString, privateData, userData);
			},
			std::addressof(cbWrapper),
			std::addressof(error)
		);
		if (detail::error::handle<exception_type>(error)) {
			m_object = contex;
		}
	}

	Context::Context(
		ContextProperties const& properties,
		DeviceType type
	){
		auto error  = cl_int{CL_INVALID_VALUE};
		auto contex = clCreateContextFromType(
			properties.data().data(),
			static_cast<std::underlying_type<DeviceType>::type>(type),
			nullptr, nullptr,
			std::addressof(error)
		);
		if (detail::error::handle<exception_type>(error)) {
			m_object = contex;
		}
	}

	//====================================================================================
	// Information access helper methods.
	//====================================================================================

	auto Context::getReferenceCount() const -> cl_uint {
		return getInfo<cl_uint>(CL_CONTEXT_REFERENCE_COUNT);
	}

	auto Context::getNumDevices() const -> cl_uint {
		return getInfo<cl_uint>(CL_CONTEXT_NUM_DEVICES);
	}

	auto Context::getDevices() const -> std::vector<Device> {
		const auto device_ids = getInfoVector<cl_device_id>(CL_CONTEXT_DEVICES);
		      auto devices    = std::vector<Device>{};	
		for (auto&& device_id : device_ids) {
			devices.emplace_back(device_id);
		}
		return devices;
	}

	auto Context::getProperties() const -> ContextProperties {
		return {getInfoVector<cl_context_properties>(CL_CONTEXT_PROPERTIES)};
	}

}
