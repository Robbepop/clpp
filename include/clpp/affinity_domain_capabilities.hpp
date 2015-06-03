#ifndef CLPP_AFFINITY_DOMAIN_CAPABILITIES_H
#define CLPP_AFFINITY_DOMAIN_CAPABILITIES_H

#include "clpp/detail/common.hpp"
#include "clpp/detail/mask_wrapper.hpp"

namespace cl {
	class AffinityDomainCapabilities final :
		public detail::MaskWrapper<cl_device_affinity_domain>
	{
	public:
		using detail::MaskWrapper<AffinityDomainCapabilities::cl_mask_type>::MaskWrapper;

		auto hasNuma() const             -> bool;
		auto hasL4Cache() const          -> bool;
		auto hasL3Cache() const          -> bool;
		auto hasL2Cache() const          -> bool;
		auto hasL1Cache() const          -> bool;
		auto isNextPartitionable() const -> bool;
	};
}

#include "clpp/affinity_domain_capabilities.tpp"
#endif
