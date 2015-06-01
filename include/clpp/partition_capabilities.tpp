#ifndef CLPP_PARTITION_CAPABILITIES_H
	#error "Do not include this file directly."
#endif

namespace cl {
	template<typename InputRange>
	PartitionCapabilities::PartitionCapabilities(InputRange properties) {
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

	auto PartitionCapabilities::supportsPartitionEqually() const -> cl_bool {
		return readMask<c_equally>();
	}

	auto PartitionCapabilities::supportsPartitionByCounts() const -> cl_bool {
		return readMask<c_byCounts>();
	}

	auto PartitionCapabilities::supportsPartitionByAffinityDomain() const -> cl_bool {
		return readMask<c_byAffinityDomain>();
	}
}
