#ifdef  CLPP_AFFINITY_DOMAIN_CAPABILITIES_IPP
	#error "multiple inclusions of the same implementation file"
#else
#define CLPP_AFFINITY_DOMAIN_CAPABILITIES_IPP

#ifndef CLPP_AFFINITY_DOMAIN_CAPABILITIES_HPP
	#error "header file has not been included; maybe it isn't required anymore?"
	#include "clpp/affinity_domain_capabilities.hpp"
#endif

namespace cl {
	auto AffinityDomainCapabilities::hasNuma() const -> bool {
		return readMask<CL_DEVICE_AFFINITY_DOMAIN_NUMA>();
	}

	auto AffinityDomainCapabilities::hasL4Cache() const -> bool {
		return readMask<CL_DEVICE_AFFINITY_DOMAIN_L4_CACHE>();
	}

	auto AffinityDomainCapabilities::hasL3Cache() const -> bool {
		return readMask<CL_DEVICE_AFFINITY_DOMAIN_L3_CACHE>();
	}

	auto AffinityDomainCapabilities::hasL2Cache() const -> bool {
		return readMask<CL_DEVICE_AFFINITY_DOMAIN_L2_CACHE>();
	}

	auto AffinityDomainCapabilities::hasL1Cache() const -> bool {
		return readMask<CL_DEVICE_AFFINITY_DOMAIN_L1_CACHE>();
	}

	auto AffinityDomainCapabilities::isNextPartitionable() const -> bool {
		return readMask<CL_DEVICE_AFFINITY_DOMAIN_NEXT_PARTITIONABLE>();
	}
}

#endif
