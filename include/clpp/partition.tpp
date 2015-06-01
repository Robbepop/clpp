#ifndef CLPP_PARTITION_H
	#error "Do not include this file directly."
#endif

#include "utility/to_underlying.hpp"

#include <type_traits>

namespace cl {
	auto Partition::equally(cl_uint count) -> Partition {
		const auto properties = std::vector<cl_device_partition_property> {
			{CL_DEVICE_PARTITION_EQUALLY, count, 0}
		};
		return Partition(properties);
	}

	template<typename RangeType>
	auto Partition::byCounts(RangeType const& counts) -> Partition {
		auto properties = std::vector<cl_device_partition_property>{};
		properties.reserve(counts.size() + 2);
		properties.push_back(CL_DEVICE_PARTITION_BY_COUNTS);
		for (auto&& elem : counts) {
			properties.push_back(elem);
		}
		properties.push_back(CL_DEVICE_PARTITION_BY_COUNTS);
		return Partition{properties.data()};
	}

	auto Partition::byAffinityDomain(AffinityDomain domain) -> Partition {
		const auto properties = std::vector<cl_device_partition_property>{
			CL_DEVICE_PARTITION_BY_AFFINITY_DOMAIN,
			static_cast<cl_device_partition_property>(domain),
			0
		};
		return Partition{properties.data()};
	}

	//================================================================================
	// Constructor for API compatibility.
	//================================================================================

	Partition::Partition(std::vector<cl_device_partition_property> properties):
		m_properties{std::move(properties)}
	{}

	Partition::Partition(const cl_device_partition_property* properties) {
		for (auto it = &properties[0]; *it != 0; ++it) {
			m_properties.push_back(*it);
		}
		m_properties.push_back(0);
	}

	//================================================================================
	// Access to the underlying type of this partition.
	// As well as getters to retrieve information about this partition and its
	// underlying internal buffer.
	//================================================================================

	auto Partition::getKind() const -> Kind {
		const auto head = m_properties.front();
		switch (head) {
			case CL_DEVICE_PARTITION_EQUALLY:            return Kind::equally;
			case CL_DEVICE_PARTITION_BY_COUNTS:          return Kind::byCounts;
			case CL_DEVICE_PARTITION_BY_AFFINITY_DOMAIN: return Kind::byAffinityDomain;
			default:                                     return Kind::none;
		};
	}

	auto Partition::data() -> cl_device_partition_property * {
		return m_properties.data();
	}

	auto Partition::data() const -> const cl_device_partition_property * {
		return m_properties.data();
	}

	//================================================================================
	// Methods restricted to the underlying type of partition.
	// Will result in an assertion fault or exception when called with an
	// incorrect kind.
	//================================================================================

	auto Partition::getComputeUnits() const -> cl_uint {
		if (getKind() != Kind::equally) {
			throw PartitionError("this operation can only be used by equal partitioning.");
		}
		assert(m_properties.size() == 3 && "internal buffer is invalid");
		return static_cast<cl_uint>(m_properties[1]);
	}

	auto Partition::getCounts() const -> std::vector<cl_uint> {
		if (getKind() != Kind::byCounts) {
			throw PartitionError("this operation can only be used by byCounts partitioning.");
		}
		assert(m_properties.size() >= 3 && "internal buffer is invalid");
		auto counts = std::vector<cl_uint>{};
		counts.reserve(m_properties.size() - 2);
		for (auto it = m_properties.begin() + 1; it != m_properties.end() - 1; ++it) {
			counts.push_back(static_cast<cl_uint>(*it));
		}
		return counts;
	}

	auto Partition::getAffinityDomain() const -> AffinityDomain {
		if (getKind() != Kind::equally) {
			throw PartitionError("this operation can only be used by equal partitioning.");
		}
		assert(m_properties.size() == 3 && "internal buffer is invalid");
		return static_cast<AffinityDomain>(m_properties[1]);
	}
}
