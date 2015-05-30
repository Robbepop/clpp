#ifndef CLPP_PLATFORM_H
	#error "Do not include this file directly!"
#endif

#include "clpp/detail/get_info_helper.hpp"

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
		error::handler<Platform::exception_type>(error);
		auto platformIds    = std::vector<Platform::cl_type>(num_platforms);
		error               = clGetPlatformIDs(countPlatforms, platformIds.data(), nullptr);
		error::handler<Platform::exception_type>(error);
		auto platforms = std::vector<Platform>{};
		for (auto&& id : platformIds) {
			platforms.emplace_back(id);
		}
		return platforms;
	}

	//================================================================================
	// Constructos and copy assign operator.
	// Note that move constructors and move assign operator are default generated.
	//================================================================================

	Platform::Platform():
		detail::Object<cl_type>{}
	{}

	explicit Platform::Platform(Platform::cl_type platform):
		m_object{object}
	{}

	Platform::Platform(const Platform & platform):
		detail::Object<cl_type>{platform}
	{}

	Platform& Platform::operator=(const Platform & rhs)
	{
		if (this != &rhs) {
		    detail::Object<cl_type>::operator=(rhs);
		}
		return *this;
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
		-> std::vector<std::string>>
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
		using device_type_t = std::underlying_type<DeviceType>::type;
		auto deviceIds = detail::getInfoVector<Device::cl_type>(
			m_object, static_cast<device_type_t>(deviceType), clGetDeviceIDs);
		auto devices = std::vector<Device>{};
			 devices.reserve(deviceIds.size());
		for (auto&& id : deviceIds) {
			devices.emplace_back(id);
		}
		return devices;
	}
}

#endif
