#ifdef  CLPP_CONTEXT_IPP
	#error "multiple inclusions of the same implementation file"
#else
#define CLPP_CONTEXT_IPP

#ifndef CLPP_CONTEXT_HPP
	#error "header file has not been included; maybe it isn't required anymore?"
	#include "clpp/context.hpp"
#endif

#include "utility/to_underlying.hpp"

//#include <iostream>
#include <iterator>
#include <algorithm>

namespace cl {
	//====================================================================================
	// Copy-Assignment
	//====================================================================================

	auto Context::operator=(const Context & rhs) -> Context & {
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
		if (detail::error::handle(error)) {
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
		if (detail::error::handle(error)) {
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
		if (detail::error::handle(error)) {
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
		if (detail::error::handle(error)) {
			m_object = contex;
		}
	}

	//================================================================================
	// Create Command Queue Objects
	//================================================================================

	auto Context::createCommandQueue(Device const& device) const -> CommandQueue {
		auto error   = cl_int{CL_INVALID_VALUE};
		auto queueId = clCreateCommandQueueWithProperties(
			get(), device.get(), nullptr, std::addressof(error));
		detail::error::handle(error);
		return {queueId};
	}

	//================================================================================
	// Create Memory Objects
	//================================================================================

	template<typename T>
	auto Context::createBuffer(
		size_t size,
		DeviceAccess deviceAccess,
		HostAccess hostAccess
	) const
		-> Buffer<T>
	{
		using namespace utility;
		auto error = cl_int{CL_INVALID_VALUE};
		auto flags = to_underlying(deviceAccess) | to_underlying(hostAccess);
		auto sizeInBytes = size * sizeof(T);
		auto id    = clCreateBuffer(get(), flags, sizeInBytes, nullptr, std::addressof(error));
		detail::error::handle(error);
		return {id};
	}

	template<typename T, typename InputIterator>
	auto Context::createBuffer(
		InputIterator first,
		InputIterator last,
		TransferMode transferMode,
		DeviceAccess deviceAccess,
		HostAccess hostAccess
	) const
		-> Buffer<T>
	{
		using namespace utility;
		auto error = cl_int{CL_INVALID_VALUE};
		auto flags = to_underlying(transferMode)
		           | to_underlying(deviceAccess)
		           | to_underlying(hostAccess);
		auto sizeInBytes = std::distance(first, last) * sizeof(T);
		auto id    = clCreateBuffer(get(), flags, sizeInBytes, (void *) &*first, std::addressof(error));
		detail::error::handle(error);
		return {id};
	}

	template<typename T, typename InputRange, typename>
	auto Context::createBuffer(
		InputRange const& range,
		TransferMode transferMode,
		DeviceAccess deviceAccess,
		HostAccess hostAccess
	) const
		-> Buffer<T>
	{
		return createBuffer<T>(range.begin(), range.end(), transferMode, deviceAccess, hostAccess);
	}

	//================================================================================
	// Create Program Objects
	//================================================================================

	auto Context::createProgramWithSource(std::string const& source) const -> Program {
		auto error     = cl_int{CL_INVALID_VALUE};
		auto cStr      = source.c_str();
		auto programId = clCreateProgramWithSource(
			get(), 1, std::addressof(cStr), nullptr, std::addressof(error));
		detail::error::handle(error);
		return {programId};
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

#endif