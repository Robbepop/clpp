#ifndef CLPP_PARTITION_CAPABILITIES_H
#define CLPP_PARTITION_CAPABILITIES_H

#include "clpp/detail/common.hpp"
#include "clpp/detail/mask_wrapper.hpp"

namespace cl {
	class PartitionCapabilities final :
		public detail::MaskWrapper<cl_device_partition_property>
	{
	public:
		using detail::MaskWrapper<PartitionCapabilities::cl_mask_type>::MaskWrapper;

		template<typename InputRange>
		PartitionCapabilities(InputRange properties);

		auto data() -> std::vector<cl_device_partition_property>;

		auto supportsPartitionEqually() const -> cl_bool;
		auto supportsPartitionByCounts() const -> cl_bool;
		auto supportsPartitionByAffinityDomain() const -> cl_bool;

	private:
		static constexpr auto c_equally;
		static constexpr auto c_byCounts;
		static constexpr auto c_byAffinityDomain;
	};
}

#include "clpp/execution_capabilities.tpp"
#endif
