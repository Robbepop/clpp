#ifndef CLPP_DEVICE_HPP
#define CLPP_DEVICE_HPP

#include "clpp/detail/object.hpp"
#include "clpp/detail/error_handler.hpp"

#include "clpp/affinity_domain.hpp"
#include "clpp/affinity_domain_capabilities.hpp"
#include "clpp/command_queue_flags.hpp"
#include "clpp/execution_capabilities.hpp"
#include "clpp/fp_type.hpp"
#include "clpp/fp_config.hpp"
#include "clpp/memory_cache_type.hpp"
#include "clpp/local_memory_type.hpp"
#include "clpp/platform.hpp"
#include "clpp/partition.hpp"
#include "clpp/partition_capabilities.hpp"
#include "clpp/scalar_type.hpp"
#include "clpp/svm_capabilities.hpp"

#include "boost/optional.hpp"

#include <vector>
#include <string>
#include <memory>

namespace cl {
	class Platform;

	namespace detail {
		template<>
		struct ObjectHandler<cl_device_id> final {
			using cl_type        = cl_device_id;
			using info_type      = cl_device_info;

		#if defined(CL_VERSION_1_2)
			static constexpr auto retain  = clRetainDevice;
			static constexpr auto release = clReleaseDevice;
		#else
			static constexpr auto success(cl_type) -> decltype(CL_SUCCESS) { return CL_SUCCESS; }
			static constexpr auto retain  = success;
			static constexpr auto release = success;
		#endif

			static constexpr auto getInfo = clGetDeviceInfo;
		};
	}

	class Device final : public detail::Object<cl_device_id> {
	public:

		//================================================================================
		// Constructor and Assignment
		//================================================================================

		using detail::Object<cl_type>::Object;

		auto inline operator=(const Device & rhs) -> Device &;
		
		//================================================================================
		// Methods to partition the device.
		//================================================================================
	#if defined(CL_VERSION_1_2)

	private:
		inline
		auto partition(Partition partition) -> std::vector<Device>;

	public:
		inline
		auto partitionEqually(cl_uint num) -> std::vector<Device>;

		template<typename InputRange>
		auto partitionByCounts(InputRange const& counts)
			-> std::vector<Device>;

		inline
		auto partitionByAffinityDomain(AffinityDomain domain)
			-> std::vector<Device>;

	#endif // defined(CL_VERSION_1_2)

		//================================================================================
		// Information access helper methods.
		//================================================================================

	public:
		auto inline getAddressBits() const                    -> cl_uint;
		auto inline isAvailable() const                       -> cl_bool;

	#if defined(CL_VERSION_1_2)
		auto inline getBuiltinKernels() const                 -> std::vector<std::string>;
	#endif // defined(CL_VERSION_1_2)

		auto inline isCompilerAvailable() const               -> cl_bool;
		auto inline getFpConfig(FPType type) const            -> FPConfig;
		auto inline isLittleEndian() const                    -> cl_bool;
		auto inline hasErrorCorrectionSupport() const         -> cl_bool;
		auto inline getExecutionCapabilities() const          -> ExecutionCapabilities;
		auto inline getExtensions() const                     -> std::vector<std::string>;
		auto inline hasExtension(std::string extension) const -> bool;

		auto inline getGlobalMemoryCacheSize() const     -> cl_ulong;
		auto inline getGlobalMemoryCacheType() const     -> MemoryCacheType;
		auto inline getGlobalMemoryCachelineSize() const -> cl_uint;
		auto inline getGlobalMemorySize() const          -> cl_ulong;

	#if defined(CL_VERSION_2_0)
		auto inline getGlobalVariablePreferredTotalSize() const -> size_t;
	#endif // defined(CL_VERSION_2_0)

		auto inline getImage2DMaxHeight() const -> size_t;
		auto inline getImage2DMaxWidth() const  -> size_t;
		auto inline getImage3DMaxHeight() const -> size_t;
		auto inline getImage3DMaxWidth() const  -> size_t;
		auto inline getImage3DMaxDepth() const  -> size_t;

	#if defined(CL_VERSION_1_2)
		auto inline getImageBaseAddressAlignment() const -> cl_uint;
		auto inline getImageMaxArraySize() const         -> size_t;
		auto inline getImageMaxBufferSize() const        -> size_t;
		auto inline getImagePitchAlignment() const       -> cl_uint;
	#endif // defined(CL_VERSION_1_2)

		auto inline hasImageSupport() const              -> cl_bool;

	#if defined(CL_VERSION_1_2)
		auto inline isLinkerAvailable() const   -> cl_bool;
	#endif // defined(CL_VERSION_1_2)

		auto inline getLocalMemorySize() const  -> cl_ulong;
		auto inline getLocalMemoryType() const  -> LocalMemoryType;

		auto inline getMaxClockFrequency() const       -> cl_uint;
		auto inline getMaxComputeUnits() const         -> cl_uint;
		auto inline getMaxConstantArgs() const         -> cl_uint;
		auto inline getMaxConstantBufferSize() const   -> cl_ulong;

	#if defined(CL_VERSION_2_0)
		auto inline getMaxGlobalVariableSize() const   -> size_t;
	#endif // defined(CL_VERSION_2_0)

		auto inline getMaxMemoryAllocationSize() const -> cl_ulong;

	#if defined(CL_VERSION_2_0)
		auto inline getMaxOnDeviceEvents() const       -> cl_uint;
		auto inline getMaxOnDeviceQueues() const       -> cl_uint;
	#endif // defined(CL_VERSION_2_0)

		auto inline getMaxParameterSize() const        -> size_t;

	#if defined(CL_VERSION_2_0)
		auto inline getMaxPipeArgs() const             -> cl_uint;
	#endif // defined(CL_VERSION_2_0)

		auto inline getMaxReadImageArgs() const        -> cl_uint;

	#if defined(CL_VERSION_2_0)
		auto inline getMaxReadWriteImageArgs() const   -> cl_uint;
	#endif // defined(CL_VERSION_2_0)

		auto inline getMaxSamplers() const             -> cl_uint;
		auto inline getMaxWorkGroupSize() const        -> size_t;
		auto inline getMaxWorkItemDimensions() const   -> cl_uint;
		auto inline getMaxWorkItemSizes() const        -> std::vector<size_t>;
		auto inline getMaxWriteImageArgs() const       -> cl_uint;

		auto inline getMemoryBaseAddressAlign() const  -> cl_uint;

		auto inline getName() const                             -> std::string;
		auto inline getNativeVectorWidth(ScalarType type) const -> cl_uint;
		auto inline getOpenCLCVersion() const                   -> std::string;

	#if defined(CL_VERSION_1_2)
		auto inline getParentDevice() const                   -> boost::optional<Device>;
		auto inline getPartitionAffinityDomain() const        -> AffinityDomainCapabilities;
		auto inline getPartitionMaxSubDevices() const         -> cl_uint;
		auto inline getPartitionProperties() const            -> PartitionCapabilities;
		auto inline getPartition() const                      -> Partition;
	#endif // defined(CL_VERSION_1_2)

	#if defined(CL_VERSION_2_0)
		auto inline getPipeMaxActiveReservations() const -> cl_uint;
		auto inline getPipeMaxPacketSize() const         -> cl_uint;
	#endif // defined(CL_VERSION_2_0)

		auto inline getPlatform() const                         -> Platform;

	#if defined(CL_VERSION_1_2)
		auto inline hasPreferredInteropUserSync() const         -> cl_bool;
	#endif // defined(CL_VERSION_1_2)

	#if defined(CL_VERSION_2_0)
		auto inline getPreferredGlobalAtomicAlignment() const   -> cl_uint;
		auto inline getPreferredLocalAtomicAlignment() const    -> cl_uint;
		auto inline getPreferredPlatformAtomicAlignment() const -> cl_uint;
	#endif // defined(CL_VERSION_2_0)

		auto inline getPreferredVectorWidth(ScalarType type) const -> cl_uint;

	#if defined(CL_VERSION_1_2)
		auto inline getPrintfBufferSize() const               -> size_t;
	#endif // defined(CL_VERSION_1_2)

		auto inline getProfile() const                        -> std::string;
		auto inline getProfilingTimerResolution() const       -> size_t;

	#if defined(CL_VERSION_2_0)
		auto inline getQueueOnDeviceMaxSize() const           -> cl_uint;
		auto inline getQueueOnDevicePreferredSize() const     -> cl_uint;
		auto inline getQueueOnDeviceFlags() const        -> CommandQueueFlags;
		auto inline getQueueOnHostFlags() const          -> CommandQueueFlags;
	#else
		auto inline getCommandQueueFlags() const                     -> CommandQueueFlags;
	#endif // defined(CL_VERSION_2_0)

	#if defined(CL_VERSION_1_2)
		auto inline getReferenceCount() const                 -> cl_uint;
	#endif // defined(CL_VERSION_1_2)

//		'use of undeclared CL_DEVICE_SPIR_VERSIONS' in OpenCL 2.0 conformant code ...
//		auto inline getSpirVersions() const                   -> std::vector<std::string>;

	#if defined(CL_VERSION_2_0)
		auto inline getSvmCapabilities() const                -> SvmCapabilities;
	#endif // defined(CL_VERSION_2_0)

		auto inline getType() const                           -> DeviceType;
		auto inline getVendor() const                         -> std::string;
		auto inline getVendorID() const                       -> cl_uint;
		auto inline getVersion() const                        -> std::string;
		auto inline getDriverVersion() const                  -> std::string;
	};
}

#endif
