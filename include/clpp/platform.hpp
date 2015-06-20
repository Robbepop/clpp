#ifndef CLPP_PLATFORM_HPP
#define CLPP_PLATFORM_HPP

#include "clpp/detail/object.hpp"
#include "clpp/device_type.hpp"

#include <vector>
#include <string>

namespace cl {
	class Device;
	class PlatformException;

	namespace detail {
		template<>
		struct ObjectHandler<cl_platform_id> final {
			using cl_type        = cl_platform_id;
			using info_type      = cl_platform_info;

			static auto release(cl_type) { return CL_SUCCESS; }

			static auto retain(cl_type) { return CL_SUCCESS; }

			static auto getInfo(
				cl_type   platform,
				info_type param_name,
				size_t    param_value_size,
				void *    param_value,
				size_t *  param_value_size_ret
			) {
				return clGetPlatformInfo(
					platform, param_name, param_value_size, param_value, param_value_size_ret);
			}
		};
	}

	class Platform final : public detail::Object<cl_platform_id> {
	public:

		//================================================================================
		// Returns all platforms available on this system.
		//================================================================================

		auto inline static getPlatforms() -> std::vector<Platform>;

		//================================================================================
		// Constructos and copy assign operator.
		// Note that move constructors and move assign operator are default generated.
		//================================================================================

		using detail::Object<cl_type>::Object;

		auto inline operator=(const Platform & rhs) -> Platform &;

		//================================================================================
		// Wrapper API for clUnloadPlatformCompiler
		//================================================================================

		void inline unloadCompiler() const;

		//================================================================================
		// Information access methods
		//================================================================================

		auto inline getProfile() const    -> std::string;
		auto inline getVersion() const    -> std::string;
		auto inline getName() const       -> std::string;
		auto inline getVendor() const     -> std::string;
		auto inline getExtensions() const -> std::vector<std::string>;
		auto inline getDevices(DeviceType deviceType) const -> std::vector<Device>;
	};
}

#endif
