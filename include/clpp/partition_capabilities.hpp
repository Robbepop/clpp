#if defined(CL_VERSION_1_2)

#ifndef CLPP_PARTITION_CAPABILITIES_HPP
#define CLPP_PARTITION_CAPABILITIES_HPP

#include "clpp/detail/common.hpp"
#include "clpp/detail/mask_wrapper.hpp"

namespace cl {
	class PartitionCapabilities final :
		public detail::MaskWrapper<cl_device_partition_property>
	{
	public:
		using detail::MaskWrapper<PartitionCapabilities::cl_mask_type>::MaskWrapper;

		inline
		PartitionCapabilities(std::vector<cl_device_partition_property> properties);

		auto inline data() -> std::vector<cl_device_partition_property>;

		auto inline supportsPartitionEqually() const          -> bool;
		auto inline supportsPartitionByCounts() const         -> bool;
		auto inline supportsPartitionByAffinityDomain() const -> bool;

	private:
		static constexpr auto c_equally          = 1u;
		static constexpr auto c_byCounts         = 2u;
		static constexpr auto c_byAffinityDomain = 4u;
	};
}

#endif // CLPP_PARTITION_CAPABILITIES_HPP
#endif // defined(CL_VERSION_1_2)
