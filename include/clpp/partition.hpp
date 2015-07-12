#if defined(CL_VERSION_1_2)

#ifndef CLPP_PARTITION_HPP
#define CLPP_PARTITION_HPP

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
		inline
		Partition(std::vector<cl_device_partition_property> properties);

		//================================================================================
		// Constructor for API compatibility.
		//================================================================================

		inline explicit
		Partition(const cl_device_partition_property* properties);

		//================================================================================
		// Access to the underlying type of this partition.
		// As well as getters to retrieve information about this partition and its
		// underlying internal buffer.
		//================================================================================

		auto inline getKind() const -> Kind;
		auto inline isEqually() const -> bool;
		auto inline isByCounts() const -> bool;
		auto inline isByAffinityDomain() const -> bool;

		auto inline data()          ->       cl_device_partition_property *;
		auto inline data() const    -> const cl_device_partition_property *;

		//================================================================================
		// Methods restricted to the underlying type of partition.
		// Will result in an assertion fault or exception when called with an
		// incorrect kind.
		//================================================================================

		auto inline getComputeUnits() const -> cl_uint;
		auto inline getCounts() const -> std::vector<cl_uint>;
		auto inline getAffinityDomain() const -> AffinityDomain;

	private:
		std::vector<cl_device_partition_property> m_properties;
	};
}

#endif // CLPP_PARTITION_HPP
#endif // defined(CL_VERSION_1_2)
