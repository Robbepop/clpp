#ifndef CLPP_CONTEXT_H
	#error "Do not include this file directly."
#endif

#include "utility/to_underlying.hpp"

//#include <iostream>
#include <iterator>

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

	template<typename DeviceIterator, typename Function, typename T>
	Context::Context(
		ContextProperties const& properties,
		DeviceIterator firstDevice,
		DeviceIterator lastDevice,
		Function callback,
		T* user_data
	){
		struct callback_data {
			Function callback;
			T* user_data;
		};
		auto cbWrapper = new callback_data{callback, user_data};
		auto ids       = std::vector<cl_device_id>{};
		ids.reserve(std::distance(firstDevice, lastDevice));
		std::transform(firstDevice, lastDevice, std::back_inserter(ids),
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
				temp->callback(errorString, privateData, userData);
				delete temp;
			},
			std::addressof(cbWrapper),
			std::addressof(error)
		);
		if (detail::error::handle<exception_type>(error)) {
			m_object = contex;
		}
	}

	template<typename DeviceIterator>
	Context::Context(
		ContextProperties const& properties,
		DeviceIterator firstDevice,
		DeviceIterator lastDevice
	){
		auto ids = std::vector<cl_device_id>{};
		ids.reserve(std::distance(firstDevice, lastDevice));
		std::transform(firstDevice, lastDevice, ids.begin(),
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
				temp->callback(errorString, privateData, userData);
				delete temp;
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

	//================================================================================
	// Create Memory Objects
	//================================================================================

	template<typename T>
	auto createBuffer(
		size_t size,
		DeviceAccess deviceAccess = DeviceAccess::readWrite,
		HostAccess hostAccess     = HostAccess::readWrite
	) const
		-> Buffer<T>
	{
		using namespace utility;
		auto error = cl_int{CL_INVALID_VALUE};
		auto flags = to_underlying(deviceAccess) | to_underlying(hostAccess);
		auto id    = clCreateBuffer(get(), flags, size, nullptr, std::addressof(error));
		detail::error::handle<exception_type>(error);
		return {id};
	}

	template<typename InputIterator>
	auto createBuffer(
		InputIterator first,
		InputIterator last,
		TransferMode transferMode,
		DeviceAccess deviceAccess = DeviceAccess::readWrite,
		HostAccess hostAccess     = HostAccess::readWrite
	) const
		-> Buffer<InputRange::value_type>
	{
		using namespace utility;
		auto error = cl_int{CL_INVALID_VALUE};
		auto flags = to_underlying(transferMode)
		           | to_underlying(deviceAccess)
		           | to_underlying(hostAccess);
		auto size  = std::distance(first, last);
		auto id    = clCreateBuffer(get(), flags, size, first, std::addressof(error));
		detail::error::handle<exception_type>(error);
		return {id};
	}

	template<typename InputRange>
	auto createBuffer(
		InputRange range,
		TransferMode transferMode,
		DeviceAccess deviceAccess = DeviceAccess::readWrite,
		HostAccess hostAccess     = HostAccess::readWrite
	) const
		-> Buffer<InputRange::value_type>
	{
		return createBuffer(range.begin(), range.end(), transferMode, deviceAccess, hostAccess);
	}

	//====================================================================================
	// Wrapper API for clLinkProgram
	//====================================================================================

	template<typename DeviceIterator, typename ProgramIterator>
	auto linkProgram(
		DeviceIterator firstDevice,
		DeviceIterator lastDevice,
		ProgramIterator firstProgram,
		ProgramIterator lastProgram,
		std::string const& options = ""
	) const -> Program {
		// TODO
	}

	template<typename DeviceIterator, typename ProgramIterator>
	auto linkProgram(
		DeviceIterator firstDevice,
		DeviceIterator lastDevice,
		ProgramIterator firstProgram,
		ProgramIterator lastProgram,
		std::string const& options,
		Function callback, T&& data
	) const -> Program {
		// TODO
	}

// cl_program clLinkProgram ( 	cl_context context,
//  	cl_uint num_devices,
//  	const cl_device_id *device_list,
//  	const char *options,
//  	cl_uint num_input_programs,
//  	const cl_program *input_programs,
//  	void (CL_CALLBACK *pfn_notify) (cl_program program, void *user_data),
//  	void *user_data,
//  	cl_int *errcode_ret)

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
