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
#include <utility>

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

	//================================================================================
	// Named Constructors - createForDevices & createForType
	//================================================================================

	auto Context::createDefault() -> Context {
		static auto const instance =
			Context::createForType(DeviceType::defaultType);
		return instance;
	}

	template<typename DeviceIterator>
	auto Context::createForDevices(DeviceIterator first, DeviceIterator last) -> Context {
		auto error     = RetCode::getPreset();
		auto contextId = clCreateContext(
			nullptr,
			static_cast<cl_uint>(std::distance(first, last)),
			reinterpret_cast<cl_device_id*>(std::addressof(*first)),
			nullptr, nullptr,
			error.data()
		);
		detail::handleError(detail::CLFunction::clCreateContext(), error);
		return {contextId};
	}

	template<typename DeviceRange, typename>
	auto Context::createForDevices(DeviceRange const& devices) -> Context {
		return createForDevices(devices.begin(), devices.end());
	}

	template<typename... Devices>
	auto Context::createForDevices(Devices&&... devices) -> Context {
		auto deviceArray = utility::make_array(devices...);
		return createForDevices(deviceArray.begin(), deviceArray.end());
	}

	auto Context::createForType(DeviceType type) -> Context {
		std::cout << "Context::createForType() - start\n";
		auto error     = RetCode::getPreset();
		auto contextId = clCreateContextFromType(
			nullptr,
			utility::to_underlying(type),
			nullptr, nullptr,
			error.data()
		);
//		std::cout << "Context::createForType() - error = " << error << '\n';
		detail::handleError(detail::CLFunction::clCreateContextFromType(), error);
//		std::cout << "Context::createForType() - end\n";
		return {contextId};
	}

	auto Context::createForType(
		ContextProperties const& properties,
		DeviceType type
	)
		-> Context
	{
		auto error     = RetCode::getPreset();
		auto contextId = clCreateContextFromType(
			properties.data().data(),
			utility::to_underlying(type),
			nullptr, nullptr,
			error.data()
		);
		detail::handleError(detail::CLFunction::clCreateContextFromType(), error);
		return {contextId};
	}

	auto Context::createBest() -> Context {
		Device  bestDevice;
		cl_uint mostComputeUnits = 0;
		auto platforms = Platform::getPlatforms();
		for (auto&& platform : platforms) {
			auto devices = platform.getDevices();
			for (auto&& device : devices) {
				auto curComputeUnits = device.getMaxComputeUnits();
				if (curComputeUnits > mostComputeUnits) {
					bestDevice       = device;
					mostComputeUnits = curComputeUnits;
				}
			}
		}
		return createForDevices(bestDevice);
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
		auto error  = RetCode::getPreset();
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
			error.data()
		);
		if (detail::handleError(detail::CLFunction::clCreateContext(), error)) {
			m_object = contex;
			delete cbWrapper; // can be safely deleted as the callback requiring this
			                  // instance will never be called since clCreateContext
			                  // ran successfully at this point of computation.
			                  // TODO: need to check if this is really true at all!
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
		auto error  = RetCode::getPreset();
		auto contex = clCreateContext(
			properties.data().data(),
			static_cast<cl_uint>(ids.size()), ids.data(),
			nullptr, nullptr,
			error.data()
		);
		if (detail::handleError(detail::CLFunction::clCreateContext(), error)) {
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
		auto error  = RetCode::getPreset();
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
			error.data()
		);
		if (detail::handleError(detail::CLFunction::clCreateContextFromType(), error)) {
			m_object = contex;
		}
	}

	//================================================================================
	// Create Command Queue Objects
	//================================================================================

	auto Context::createCommandQueue(Device const& device) const -> CommandQueue {
		auto error = RetCode::getPreset();
		#if defined(CL_VERSION_2_0)
			auto queueId = clCreateCommandQueueWithProperties(
				get(), device.get(), nullptr, error.data());
			detail::handleError(
				detail::CLFunction::clCreateCommandQueueWithProperties(), error);
		#else
			auto queueId = clCreateCommandQueue(
				get(), device.get(), CommandQueueFlags::null, error.data());
			detail::handleError(
				detail::CLFunction::clCreateCommandQueue(), error);
		#endif // defined(CL_VERSION_2_0)
		return {queueId};
	}

	auto Context::createCommandQueue(
		Device const& device,
		CommandQueueFlags const& flags
	) const -> CommandQueue {
		auto error = RetCode::getPreset();
		#if defined(CL_VERSION_2_0)
			auto props   = CommandQueueProperties{};
			props.setCommandQueueFlags(flags);
			auto queueId = clCreateCommandQueueWithProperties(
				get(), device.get(), props.data().data(), error.data());
			detail::handleError(
				detail::CLFunction::clCreateCommandQueueWithProperties(), error);
		#else
			auto queueId = clCreateCommandQueue(
				get(), device.get(), flags.mask(), error.data());
			detail::handleError(
				detail::CLFunction::clCreateCommandQueue(), error);
		#endif // defined(CL_VERSION_2_0)
		return {queueId};
	}

#if defined(CL_VERSION_2_0)
	auto Context::createCommandQueue(
		Device const& device,
		CommandQueueProperties const& properties
	) const -> CommandQueue {
		auto error = RetCode::getPreset();
		auto queueId = clCreateCommandQueueWithProperties(
			get(), device.get(), properties.data().data(), error.data());
		detail::handleError(
			detail::CLFunction::clCreateCommandQueueWithProperties(), error);
		return {queueId};
	}
#endif // defined(CL_VERSION_1_2)

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
		auto error = RetCode::getPreset();
		auto flags = to_underlying(deviceAccess) | to_underlying(hostAccess);
		auto sizeInBytes = size * sizeof(T);
		auto id    = clCreateBuffer(get(), flags, sizeInBytes, nullptr, error.data());
		detail::handleError(detail::CLFunction::clCreateBuffer(), error);
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
		auto error = RetCode::getPreset();
		auto flags = to_underlying(transferMode)
		           | to_underlying(deviceAccess)
		           | to_underlying(hostAccess);
		auto sizeInBytes = std::distance(first, last) * sizeof(T);
		auto id    = clCreateBuffer(get(), flags, sizeInBytes, (void *) &*first, error.data());
		detail::handleError(detail::CLFunction::clCreateBuffer(), error);
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
		auto error     = RetCode::getPreset();
		auto cStr      = source.c_str();
		auto programId = clCreateProgramWithSource(
			get(), 1, std::addressof(cStr), nullptr, error.data());
		detail::handleError(detail::CLFunction::clCreateProgramWithSource(), error);
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
		return {getInfoVector<cl_context_properties>(CL_CONTEXT_PROPERTIES).data()};
	}

}

#endif
