#ifndef CLPP_DEVICE_H
#define CLPP_DEVICE_H

#include "clpp/detail/object.hpp"
#include "clpp/detail/error_handler.hpp"

#include "clpp/affinity_domain.hpp"
#include "clpp/affinity_domain_capabilities.hpp"
#include "clpp/command_queue_properties.hpp"
#include "clpp/execution_capabilities.hpp"
#include "clpp/fp_type.hpp"
#include "clpp/fp_config.hpp"
#include "clpp/memory_cache_type.hpp"
#include "clpp/local_memory_type.hpp"
#include "clpp/partition.hpp"
#include "clpp/partition_capabilities.hpp"
#include "clpp/scalar_type.hpp"
#include "clpp/svm_capabilities.hpp"

#include "boost/optional.hpp"

#include <vector>
#include <string>

namespace cl {
	class Platform;

	namespace detail {
		template<>
		struct ObjectHandler<cl_device_id> final {
			using cl_type        = cl_device_id;
			using info_type      = cl_device_info;

			static auto release(cl_type id) { return clReleaseDevice(id); }

			static auto retain(cl_type id) { return clRetainDevice(id); }

			static auto getInfo(
				cl_type   device,
				info_type param_name,
				size_t    param_value_size,
				void *    param_value,
				size_t *  param_value_size_ret
			) {
				return clGetDeviceInfo(
					device, param_name, param_value_size, param_value, param_value_size_ret);
			}
		};
	}

	class Device final : public detail::Object<cl_device_id> {
	public:

		//================================================================================
		// Constructor and Assignment
		//================================================================================

		using detail::Object<cl_type>::Object;

		Device& operator=(const Device & rhs);
		
		//================================================================================
		// Methods to partition the device.
		//================================================================================

	private:
		auto partition(Partition partition) -> std::vector<Device>;

	public:
		auto partitionEqually(cl_uint num) -> std::vector<Device>;

		template<typename InputRange>
		auto partitionByCounts(InputRange const& counts)
			-> std::vector<Device>;

		auto partitionByAffinityDomain(AffinityDomain domain)
			-> std::vector<Device>;

		//================================================================================
		// Information access helper methods.
		//================================================================================

	public:
		auto getAddressBits() const                    -> cl_uint;
		auto isAvailable() const                       -> cl_bool;
		auto getBuiltinKernels() const                 -> std::vector<std::string>;
		auto isCompilerAvailable() const               -> cl_bool;
		auto getFpConfig(FPType type) const            -> FPConfig;
		auto isLittleEndian() const                    -> cl_bool;
		auto hasErrorCorrectionSupport() const         -> cl_bool;
		auto getExecutionCapabilities() const          -> ExecutionCapabilities;
		auto getExtensions() const                     -> std::vector<std::string>;
		auto hasExtension(std::string extension) const -> bool;

		auto getGlobalMemoryCacheSize() const     -> cl_ulong;
		auto getGlobalMemoryCacheType() const     -> MemoryCacheType;
		auto getGlobalMemoryCachelineSize() const -> cl_uint;
		auto getGlobalMemorySize() const          -> cl_ulong;
		auto getGlobalVariablePreferredTotalSize() const -> size_t;

		auto getImage2DMaxHeight() const -> size_t;
		auto getImage2DMaxWidth() const  -> size_t;
		auto getImage3DMaxHeight() const -> size_t;
		auto getImage3DMaxWidth() const  -> size_t;
		auto getImage3DMaxDepth() const  -> size_t;

		auto getImageBaseAddressAlignment() const -> cl_uint;
		auto getImageMaxArraySize() const         -> size_t;
		auto getImageMaxBufferSize() const        -> size_t;
		auto getImagePitchAlignment() const       -> cl_uint;
		auto hasImageSupport() const              -> cl_bool;

		auto isLinkerAvailable() const   -> cl_bool;

		auto getLocalMemorySize() const  -> cl_ulong;
		auto getLocalMemoryType() const  -> LocalMemoryType;

		auto getMaxClockFrequency() const       -> cl_uint;
		auto getMaxComputeUnits() const         -> cl_uint;
		auto getMaxConstantArgs() const         -> cl_uint;
		auto getMaxConstantBufferSize() const   -> cl_ulong;
		auto getMaxGlobalVariableSize() const   -> size_t;
		auto getMaxMemoryAllocationSize() const -> cl_ulong;
		auto getMaxOnDeviceEvents() const       -> cl_uint;
		auto getMaxOnDeviceQueues() const       -> cl_uint;
		auto getMaxParameterSize() const        -> size_t;
		auto getMaxPipeArgs() const             -> cl_uint;
		auto getMaxReadImageArgs() const        -> cl_uint;
		auto getMaxReadWriteImageArgs() const   -> cl_uint;
		auto getMaxSamplers() const             -> cl_uint;
		auto getMaxWorkGroupSize() const        -> size_t;
		auto getMaxWorkItemDimensions() const   -> cl_uint;
		auto getMaxWorkItemSizes() const        -> std::vector<size_t>;
		auto getMaxWriteImageArgs() const       -> cl_uint;

		auto getMemoryBaseAddressAlign() const  -> cl_uint;

		auto getName() const                             -> std::string;
		auto getNativeVectorWidth(ScalarType type) const -> cl_uint;
		auto getOpenCLCVersion() const                   -> std::string;

		auto getParentDevice() const                   -> boost::optional<Device>;
		auto getPartitionAffinityDomain() const        -> AffinityDomainCapabilities;
		auto getPartitionMaxSubDevices() const         -> cl_uint;
		auto getPartitionProperties() const            -> PartitionCapabilities;
		auto getPartition() const                      -> Partition;

		auto getPipeMaxActiveReservations() const -> cl_uint;
		auto getPipeMaxPacketSize() const         -> cl_uint;

		auto getPlatform() const                         -> std::unique_ptr<Platform>;
		auto getPreferredGlobalAtomicAlignment() const   -> cl_uint;
		auto hasPreferredInteropUserSync() const         -> cl_bool;
		auto getPreferredLocalAtomicAlignment() const    -> cl_uint;
		auto getPreferredPlatformAtomicAlignment() const -> cl_uint;
		auto getPreferredVectorWidth(ScalarType type) const -> cl_uint;

		auto getPrintfBufferSize() const               -> size_t;
		auto getProfile() const                        -> std::string;
		auto getProfilingTimerResolution() const       -> size_t;

		auto getQueueOnDeviceMaxSize() const           -> cl_uint;
		auto getQueueOnDevicePreferredSize() const     -> cl_uint;
		auto getQueueOnDeviceProperties() const        -> CommandQueueProperties;
		auto getQueueOnHostProperties() const          -> CommandQueueProperties;

		auto getReferenceCount() const                 -> cl_uint;

		// 'use of undeclared CL_DEVICE_SPIR_VERSIONS' in OpenCL 2.0 conformant code ...
		//auto getSpirVersions() const                   -> std::vector<std::string>;
		auto getSvmCapabilities() const                -> SvmCapabilities;

		auto getType() const                           -> DeviceType;
		auto getVendor() const                         -> std::string;
		auto getVendorID() const                       -> cl_uint;
		auto getVersion() const                        -> std::string;
		auto getDriverVersion() const                  -> std::string;
	};
}

#endif
