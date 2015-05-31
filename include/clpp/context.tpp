#ifndef CLPP_CONTEXT_H
	#error "Do not include this file directly."
#endif

namespace cl {
	//================================================================================
	// Basic Constructors and Copy-Assignment
	//================================================================================

	Context::Context():
		detail::Wrapper<Device::cl_type>{}
	{}

	Context::Context(Context::cl_type context):
		m_object{device}
	{}

	Context::Context(const Context & context):
		detail::Wrapper<cl_type>{device}
	{}


	Context& Context::operator=(const Context & rhs) {
        if (this != &rhs) {
            detail::Wrapper<cl_type>::operator=(rhs);
        }
        return *this;
	}


	//================================================================================
	// Special Constructors
	//================================================================================

	template<typename Function, typename T>
	Context::Context(
		ContextProperties const& properties,
		std::vector<Device> const& devices,
		Function callback,
		T* user_data
	){
		// TODO
	}

	Context::Context(
		ContextProperties const& properties,
		std::vector<Device> const& devices
	){
		// TODO
	}

	template<typename Function, typename T>
	Context::Context(
		ContextProperties const& properties,
		DeviceType type,
		Function callback,
		T* user_data
	){
		// TODO
	}

	Context::Context(
		ContextProperties const& properties,
		DeviceType type
	){
		// TODO
	}

	//================================================================================
	// Information access helper methods.
	//================================================================================

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
		return {getInfo<cl_context_properties[]>(CL_CONTEXT_PROPERTIES)};
	}

}
