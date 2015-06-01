#ifndef CLPP_AFFINITY_DOMAIN_CAPABILITIES_H
	#error "Do not include this file directly."
#endif

namespace cl {
	auto AffinityDomainCapabilities::hasNuma() const -> cl_bool {
		readMask<CL_DEVICE_AFFINITY_DOMAIN_NUMA>();
	}

	auto AffinityDomainCapabilities::hasL4Cache() const -> cl_bool {
		readMask<CL_DEVICE_AFFINITY_DOMAIN_L4_CACHE>();
	}

	auto AffinityDomainCapabilities::hasL3Cache() const -> cl_bool {
		readMask<CL_DEVICE_AFFINITY_DOMAIN_L3_CACHE>();
	}

	auto AffinityDomainCapabilities::hasL2Cache() const -> cl_bool {
		readMask<CL_DEVICE_AFFINITY_DOMAIN_L2_CACHE>();
	}

	auto AffinityDomainCapabilities::hasL1Cache() const -> cl_bool {
		readMask<CL_DEVICE_AFFINITY_DOMAIN_L1_CACHE>();
	}

	auto AffinityDomainCapabilities::isNextPartitionable() const -> cl_bool {
		readMask<CL_DEVICE_AFFINITY_DOMAIN_NEXT_PARTITIONABLE>();
	}

}
