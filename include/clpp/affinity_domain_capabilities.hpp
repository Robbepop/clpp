#ifndef CLPP_AFFINITY_DOMAIN_CAPABILITIES_HPP
#define CLPP_AFFINITY_DOMAIN_CAPABILITIES_HPP

#include "clpp/detail/common.hpp"
#include "clpp/detail/mask_wrapper.hpp"

namespace cl {
	class AffinityDomainCapabilities final :
		public detail::MaskWrapper<cl_device_affinity_domain>
	{
	public:
		using detail::MaskWrapper<AffinityDomainCapabilities::cl_mask_type>::MaskWrapper;

		auto inline hasNuma() const             -> bool;
		auto inline hasL4Cache() const          -> bool;
		auto inline hasL3Cache() const          -> bool;
		auto inline hasL2Cache() const          -> bool;
		auto inline hasL1Cache() const          -> bool;
		auto inline isNextPartitionable() const -> bool;
	};
}

#endif
