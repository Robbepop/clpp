#ifdef  CLPP_PLATFORM_IPP
	#error "multiple inclusions of the same implementation file"
#else
#define CLPP_PLATFORM_IPP

#ifndef CLPP_PLATFORM_HPP
	#error "header file has not been included; maybe it isn't required anymore?"
	#include "clpp/platform.hpp"
#endif

#include "clpp/utility/to_underlying.hpp"
#include "clpp/detail/information_accessor.hpp"
#include "clpp/device.hpp"

#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>

#include <type_traits>

namespace cl {

	//================================================================================
	// Returns all platforms available on this system.
	//================================================================================

	auto Platform::getPlatforms()
		-> std::vector<Platform>
	{
		auto error          = cl_int{CL_INVALID_VALUE};
		auto countPlatforms = cl_uint{0};
		error               = clGetPlatformIDs(0, nullptr, std::addressof(countPlatforms));
		detail::handleError(detail::CLFunction::clGetPlatformIDs(), error);
		auto platformIds    = std::vector<Platform::cl_type>(countPlatforms);
		error               = clGetPlatformIDs(countPlatforms, platformIds.data(), nullptr);
		detail::handleError(detail::CLFunction::clGetPlatformIDs(), error);
		auto platforms = std::vector<Platform>{};
		for (auto&& id : platformIds) {
			platforms.emplace_back(id);
		}
		return platforms;
	}

	//================================================================================
	// Copy assign operator.
	// Note that move constructors and move assign operator are default generated.
	//================================================================================

	auto Platform::operator=(const Platform & rhs) -> Platform & {
		if (this != &rhs) {
		    detail::Object<cl_type>::operator=(rhs);
		}
		return *this;
	}

	//================================================================================
	// Wrapper API for clUnloadPlatformCompiler
	//================================================================================

	void Platform::unloadCompiler() const {
		const auto error = clUnloadPlatformCompiler(get());
		detail::handleError(detail::CLFunction::clUnloadPlatformCompiler(), error);
	}

	//================================================================================
	// Information access methods
	//================================================================================

	auto Platform::getProfile() const
		-> std::string
	{
		return getInfoString(CL_PLATFORM_PROFILE);
	}

	auto Platform::getVersion() const
		-> std::string	
	{
		return getInfoString(CL_PLATFORM_VERSION);
	}

	auto Platform::getName() const
		-> std::string
	{
		return getInfoString(CL_PLATFORM_NAME);
	}

	auto Platform::getVendor() const
		-> std::string
	{
		return getInfoString(CL_PLATFORM_VENDOR);
	}

	auto Platform::getExtensions() const
		-> std::vector<std::string>
	{
			  auto extensions = std::vector<std::string>{};
		const auto extString  = getInfoString(CL_PLATFORM_EXTENSIONS);
		boost::split(extensions, extString,
			boost::is_any_of("\t "),
			boost::token_compress_on);
		return extensions;
	}

	auto Platform::getDevices(DeviceType deviceType) const
		-> std::vector<Device>
	{
		using namespace utility;
		auto numDevices = cl_uint{0};
		auto error = clGetDeviceIDs(
			get(), to_underlying(deviceType), 0, nullptr, std::addressof(numDevices));
		detail::handleError(detail::CLFunction::clGetDeviceIDs(), error);
		auto deviceIds = std::vector<Device>(numDevices);
		error = clGetDeviceIDs(
			get(), to_underlying(deviceType), numDevices,
			reinterpret_cast<cl_device_id*>(deviceIds.data()), nullptr);
		detail::handleError(detail::CLFunction::clGetDeviceIDs(), error);
		return deviceIds;
	}

	auto Platform::getDevices() const -> std::vector<Device> {
		return getDevices(DeviceType::all);
	}
}

#endif
