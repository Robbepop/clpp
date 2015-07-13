#if defined(CL_VERSION_1_2)

#ifdef  CLPP_PARTITION_CAPABILITIES_IPP
	#error "multiple inclusions of the same implementation file"
#else
#define CLPP_PARTITION_CAPABILITIES_IPP

#ifndef CLPP_PARTITION_CAPABILITIES_HPP
	#error "header file has not been included; maybe it isn't required anymore?"
	#include "clpp/partition_capabilities.hpp"
#endif

namespace cl {
	PartitionCapabilities::PartitionCapabilities(
		std::vector<cl_device_partition_property> properties
	){
		for (auto&& property : properties) {
			switch (property) {
				case CL_DEVICE_PARTITION_EQUALLY:            modifyMask<c_equally>(true);          break;
				case CL_DEVICE_PARTITION_BY_COUNTS:          modifyMask<c_byCounts>(true);         break;
				case CL_DEVICE_PARTITION_BY_AFFINITY_DOMAIN: modifyMask<c_byAffinityDomain>(true); break;
				case 0: return;
				default: assert(false);
			}
		}
	}

	auto PartitionCapabilities::data() -> std::vector<cl_device_partition_property> {
		auto properties = std::vector<cl_device_partition_property>{};
		if (supportsPartitionEqually()) {
			properties.push_back(CL_DEVICE_PARTITION_EQUALLY);
		}
		if (supportsPartitionByCounts()) {
			properties.push_back(CL_DEVICE_PARTITION_BY_COUNTS);
		}
		if (supportsPartitionByAffinityDomain()) {
			properties.push_back(CL_DEVICE_PARTITION_BY_AFFINITY_DOMAIN);
		}
		if (properties.size() == 0) {
			properties.push_back(0);
		}
		return properties;
	}

	auto PartitionCapabilities::supportsPartitionEqually() const -> bool {
		return readMask<c_equally>();
	}

	auto PartitionCapabilities::supportsPartitionByCounts() const -> bool {
		return readMask<c_byCounts>();
	}

	auto PartitionCapabilities::supportsPartitionByAffinityDomain() const -> bool {
		return readMask<c_byAffinityDomain>();
	}
}

#endif // CLPP_PARTITION_CAPABILITIES_IPP
#endif // defined(CL_VERSION_1_2)
