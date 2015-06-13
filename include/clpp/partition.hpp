#ifndef CLPP_PARTITION_H
#define CLPP_PARTITION_H

#include "clpp/detail/common.hpp"

namespace cl {
	class Partition final {
	public:
		enum class Kind {
			none,
			equally,
			byCounts,
			byAffinityDomain
		};

		//================================================================================
		// Named constructors for the user to use.
		//================================================================================

		static auto equally(cl_uint count) -> Partition;

		template<typename RangeType>
		static auto byCounts(RangeType const& counts) -> Partition;

		static auto byAffinityDomain(AffinityDomain domain) -> Partition;

	public:
		Partition(std::vector<cl_device_partition_property> properties);

		//================================================================================
		// Constructor for API compatibility.
		//================================================================================

		explicit Partition(const cl_device_partition_property* properties);

		//================================================================================
		// Access to the underlying type of this partition.
		// As well as getters to retrieve information about this partition and its
		// underlying internal buffer.
		//================================================================================

		auto getKind() const -> Kind;
		auto isEqually() const -> bool;
		auto isByCounts() const -> bool;
		auto isByAffinityDomain() const -> bool;

		auto data()          ->       cl_device_partition_property *;
		auto data() const    -> const cl_device_partition_property *;

		//================================================================================
		// Methods restricted to the underlying type of partition.
		// Will result in an assertion fault or exception when called with an
		// incorrect kind.
		//================================================================================

		auto getComputeUnits() const -> cl_uint;
		auto getCounts() const -> std::vector<cl_uint>;
		auto getAffinityDomain() const -> AffinityDomain;

	private:
		std::vector<cl_device_partition_property> m_properties;
	};
}

#endif
