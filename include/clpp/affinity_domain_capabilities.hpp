#ifndef CLPP_COMMAND_QUEUE_PROPERTIES_H
#define CLPP_COMMAND_QUEUE_PROPERTIES_H

#include "clpp/detail/common.hpp"
#include "clpp/detail/mask_wrapper.hpp"

namespace cl {
	class AffinityDomainCapabilities final :
		public detail::MaskWrapper<cl_device_affinity_domain>
	{
	public:
		using detail::MaskWrapper<AffinityDomainCapabilities::cl_mask_type>::MaskWrapper;

		auto hasNuma() const             -> cl_bool;
		auto hasL4Cache() const          -> cl_bool;
		auto hasL3Cache() const          -> cl_bool;
		auto hasL2Cache() const          -> cl_bool;
		auto hasL1Cache() const          -> cl_bool;
		auto isNextPartitionable() const -> cl_bool;
	};
}

#include "clpp/command_queue_properties.tpp"
#endif
