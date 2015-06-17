#ifndef CLPP_AFFINITY_DOMAIN_HPP
#define CLPP_AFFINITY_DOMAIN_HPP

#include "clpp/detail/common.hpp"

namespace cl {
	enum class AffinityDomain : cl_device_affinity_domain {
		numa              = CL_DEVICE_AFFINITY_DOMAIN_NUMA,
		cacheL4           = CL_DEVICE_AFFINITY_DOMAIN_L4_CACHE,
		cacheL3           = CL_DEVICE_AFFINITY_DOMAIN_L3_CACHE,
		cacheL2           = CL_DEVICE_AFFINITY_DOMAIN_L2_CACHE,
		cacheL1           = CL_DEVICE_AFFINITY_DOMAIN_L1_CACHE,
		nextPartitionable = CL_DEVICE_AFFINITY_DOMAIN_NEXT_PARTITIONABLE
	};
}
#endif
