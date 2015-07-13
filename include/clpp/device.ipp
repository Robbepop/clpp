#ifdef  CLPP_DEVICE_IPP
	#error "multiple inclusions of the same implementation file"
#else
#define CLPP_DEVICE_IPP

#ifndef CLPP_DEVICE_HPP
	#error "header file has not been included; maybe it isn't required anymore?"
	#include "clpp/device.hpp"
#endif

#include "clpp/partition.hpp"

#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>

namespace cl {

	//====================================================================================
	// Assignment
	//====================================================================================

    auto Device::operator=(const Device & rhs) -> Device & {
        if (this != &rhs) {
            detail::Object<cl_type>::operator=(rhs);
        }
        return *this;
    }

	//====================================================================================
	// Partitioning
	//====================================================================================
#if defined(CL_VERSION_1_2)

	auto Device::partition(Partition partition) -> std::vector<Device> {
		auto error      = RetCode::getPreset();
		auto countElems = cl_uint{0};
		error = clCreateSubDevices(m_object, partition.data(), 0, nullptr, std::addressof(countElems));
		detail::handleError(detail::CLFunction::clCreateSubDevices(), error);
		auto ids = std::vector<Device::cl_type>(countElems);
		error = clCreateSubDevices(m_object, partition.data(), countElems, ids.data(), nullptr);
		detail::handleError(detail::CLFunction::clCreateSubDevices(), error);
		return {ids.begin(), ids.end()};
	}

	auto Device::partitionEqually(cl_uint num) -> std::vector<Device>{
		return partition(Partition::equally(num));
	}

	template<typename InputRange>
	auto Device::partitionByCounts(InputRange const& counts)
		-> std::vector<Device>
	{
		return partition(Partition::byCounts(counts));
	}

	auto Device::partitionByAffinityDomain(AffinityDomain domain)
		-> std::vector<Device>
	{
		return partition(Partition::byAffinityDomain(domain));
	}

#endif // defined(CL_VERSION_1_2)

	//====================================================================================
	// getInfo helper methods
	//====================================================================================

	auto Device::getAddressBits() const -> cl_uint {
		return getInfo<cl_uint>(CL_DEVICE_ADDRESS_BITS);
	}

	auto Device::isAvailable() const -> cl_bool {
		return getInfo<cl_bool>(CL_DEVICE_AVAILABLE);
	}

	auto Device::getBuiltinKernels() const -> std::vector<std::string> {
			  auto kernels       = std::vector<std::string>{};
		const auto kernelsString = getInfoString(CL_DEVICE_BUILT_IN_KERNELS);
		boost::split(kernels, kernelsString, boost::is_any_of("\t "), boost::token_compress_on);
		return kernels;
	}

	auto Device::isCompilerAvailable() const -> cl_bool {
		return getInfo<cl_bool>(CL_DEVICE_COMPILER_AVAILABLE);
	}

	auto Device::getFpConfig(FPType type) const -> FPConfig {
		switch (type) {
		case FPType::halfPrecision:
			assert(false && "unsupported operation");
		//	return {getInfo<cl_device_fp_config>(CL_DEVICE_HALF_FP_CONFIG)};
		case FPType::singlePrecision:
			return {getInfo<cl_device_fp_config>(CL_DEVICE_SINGLE_FP_CONFIG)};
		case FPType::doublePrecision:
			return {getInfo<cl_device_fp_config>(CL_DEVICE_DOUBLE_FP_CONFIG)};
		default:
			assert(false);
		}
	}

	auto Device::isLittleEndian() const -> cl_bool {
		return getInfo<cl_bool>(CL_DEVICE_ENDIAN_LITTLE);
	}

	auto Device::hasErrorCorrectionSupport() const -> cl_bool {
		return getInfo<cl_bool>(CL_DEVICE_ERROR_CORRECTION_SUPPORT);
	}

	auto Device::getExecutionCapabilities() const -> ExecutionCapabilities {
		return {getInfo<cl_device_exec_capabilities>(CL_DEVICE_EXECUTION_CAPABILITIES)};
	}

	auto Device::getExtensions() const -> std::vector<std::string> {
			  auto extensions = std::vector<std::string>{};
		const auto extString  = getInfoString(CL_DEVICE_EXTENSIONS);
		boost::split(extensions, extString, boost::is_any_of("\t "), boost::token_compress_on);
		return extensions;
	}

	auto Device::hasExtension(std::string extension) const -> bool {
		const auto extensions = getExtensions();
		return std::find(extensions.cbegin(), extensions.cend(), extension) != extensions.end();
	}


	auto Device::getGlobalMemoryCacheSize() const -> cl_ulong {
		return getInfo<cl_ulong>(CL_DEVICE_GLOBAL_MEM_CACHE_SIZE);
	}

	auto Device::getGlobalMemoryCacheType() const -> MemoryCacheType {
		return static_cast<MemoryCacheType>(
			getInfo<cl_device_mem_cache_type>(CL_DEVICE_GLOBAL_MEM_CACHE_TYPE));
	}

	auto Device::getGlobalMemoryCachelineSize() const -> cl_uint {
		return getInfo<cl_uint>(CL_DEVICE_GLOBAL_MEM_CACHELINE_SIZE);
	}

	auto Device::getGlobalMemorySize() const -> cl_ulong {
		return getInfo<cl_ulong>(CL_DEVICE_GLOBAL_MEM_SIZE);
	}

#if defined(CL_VERSION_2_0)
	auto Device::getGlobalVariablePreferredTotalSize() const -> size_t {
		return getInfo<size_t>(CL_DEVICE_GLOBAL_VARIABLE_PREFERRED_TOTAL_SIZE);
	}
#endif // defined(CL_VERSION_2_0)

	auto Device::getImage2DMaxHeight() const -> size_t {
		return getInfo<size_t>(CL_DEVICE_IMAGE2D_MAX_HEIGHT);
	}

	auto Device::getImage2DMaxWidth() const  -> size_t {
		return getInfo<size_t>(CL_DEVICE_IMAGE2D_MAX_WIDTH);
	}

	auto Device::getImage3DMaxHeight() const -> size_t {
		return getInfo<size_t>(CL_DEVICE_IMAGE3D_MAX_HEIGHT);
	}

	auto Device::getImage3DMaxWidth() const  -> size_t {
		return getInfo<size_t>(CL_DEVICE_IMAGE3D_MAX_WIDTH);
	}

	auto Device::getImage3DMaxDepth() const  -> size_t {
		return getInfo<size_t>(CL_DEVICE_IMAGE3D_MAX_DEPTH);
	}


	auto Device::getImageBaseAddressAlignment() const -> cl_uint {
		return getInfo<cl_uint>(CL_DEVICE_IMAGE_BASE_ADDRESS_ALIGNMENT);
	}

	auto Device::getImageMaxArraySize() const -> size_t {
		return getInfo<size_t>(CL_DEVICE_IMAGE_MAX_ARRAY_SIZE);
	}

	auto Device::getImageMaxBufferSize() const -> size_t {
		return getInfo<size_t>(CL_DEVICE_IMAGE_MAX_BUFFER_SIZE);
	}

	auto Device::getImagePitchAlignment() const -> cl_uint {
		return getInfo<cl_uint>(CL_DEVICE_IMAGE_PITCH_ALIGNMENT);
	}

	auto Device::hasImageSupport() const -> cl_bool {
		return getInfo<cl_bool>(CL_DEVICE_IMAGE_SUPPORT);
	}

	auto Device::isLinkerAvailable() const -> cl_bool {
		return getInfo<cl_bool>(CL_DEVICE_LINKER_AVAILABLE);
	}

	auto Device::getLocalMemorySize() const -> cl_ulong {
		return getInfo<cl_ulong>(CL_DEVICE_LOCAL_MEM_SIZE);
	}

	auto Device::getLocalMemoryType() const  -> LocalMemoryType {
		return static_cast<LocalMemoryType>(
			getInfo<cl_device_local_mem_type>(CL_DEVICE_LOCAL_MEM_TYPE));
	}

	auto Device::getMaxClockFrequency() const -> cl_uint {
		return getInfo<cl_uint>(CL_DEVICE_MAX_CLOCK_FREQUENCY);
	}

	auto Device::getMaxComputeUnits() const -> cl_uint {
		return getInfo<cl_uint>(CL_DEVICE_MAX_COMPUTE_UNITS);
	}

	auto Device::getMaxConstantArgs() const -> cl_uint {
		return getInfo<cl_uint>(CL_DEVICE_MAX_CONSTANT_ARGS);
	}

	auto Device::getMaxConstantBufferSize() const -> cl_ulong {
		return getInfo<cl_ulong>(CL_DEVICE_MAX_CONSTANT_BUFFER_SIZE);
	}

	auto Device::getMaxGlobalVariableSize() const -> size_t {
		return getInfo<size_t>(CL_DEVICE_MAX_GLOBAL_VARIABLE_SIZE);
	}

	auto Device::getMaxMemoryAllocationSize() const -> cl_ulong {
		return getInfo<cl_ulong>(CL_DEVICE_MAX_MEM_ALLOC_SIZE);
	}

	auto Device::getMaxOnDeviceEvents() const -> cl_uint {
		return getInfo<cl_uint>(CL_DEVICE_MAX_ON_DEVICE_EVENTS);
	}

	auto Device::getMaxOnDeviceQueues() const -> cl_uint {
		return getInfo<cl_uint>(CL_DEVICE_MAX_ON_DEVICE_QUEUES);
	}

	auto Device::getMaxParameterSize() const -> size_t {
		return getInfo<size_t>(CL_DEVICE_MAX_PARAMETER_SIZE);
	}

#if defined(CL_VERSION_2_0)
	auto Device::getMaxPipeArgs() const -> cl_uint {
		return getInfo<cl_uint>(CL_DEVICE_MAX_PIPE_ARGS);
	}
#endif // defined(CL_VERSION_2_0)

	auto Device::getMaxReadImageArgs() const -> cl_uint {
		return getInfo<cl_uint>(CL_DEVICE_MAX_READ_IMAGE_ARGS);
	}

	auto Device::getMaxReadWriteImageArgs() const -> cl_uint {
		return getInfo<cl_uint>(CL_DEVICE_MAX_READ_WRITE_IMAGE_ARGS);
	}

	auto Device::getMaxSamplers() const -> cl_uint {
		return getInfo<cl_uint>(CL_DEVICE_MAX_SAMPLERS);
	}

	auto Device::getMaxWorkGroupSize() const -> size_t {
		return getInfo<size_t>(CL_DEVICE_MAX_WORK_GROUP_SIZE);
	}

	auto Device::getMaxWorkItemDimensions() const -> cl_uint {
		return getInfo<cl_uint>(CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS);
	}

	auto Device::getMaxWorkItemSizes() const -> std::vector<size_t> {
		return getInfoVector<size_t>(CL_DEVICE_MAX_WORK_ITEM_SIZES);
	}

	auto Device::getMaxWriteImageArgs() const -> cl_uint {
		return getInfo<cl_uint>(CL_DEVICE_MAX_WRITE_IMAGE_ARGS);
	}


	auto Device::getMemoryBaseAddressAlign() const -> cl_uint {
		return getInfo<cl_uint>(CL_DEVICE_MEM_BASE_ADDR_ALIGN);
	}


	auto Device::getName() const -> std::string {
		return getInfoString(CL_DEVICE_NAME);
	}

	auto Device::getNativeVectorWidth(ScalarType type) const -> cl_uint {
		auto id = cl_device_info{};
		switch (type) {
			case ScalarType::charType:   id = CL_DEVICE_NATIVE_VECTOR_WIDTH_CHAR;   break;
			case ScalarType::shortType:  id = CL_DEVICE_NATIVE_VECTOR_WIDTH_SHORT;  break;
			case ScalarType::intType:    id = CL_DEVICE_NATIVE_VECTOR_WIDTH_INT;    break;
			case ScalarType::longType:   id = CL_DEVICE_NATIVE_VECTOR_WIDTH_LONG;   break;
			case ScalarType::floatType:  id = CL_DEVICE_NATIVE_VECTOR_WIDTH_FLOAT;  break;
			case ScalarType::doubleType: id = CL_DEVICE_NATIVE_VECTOR_WIDTH_DOUBLE; break;
			case ScalarType::halfType:   id = CL_DEVICE_NATIVE_VECTOR_WIDTH_HALF;   break;
			default: assert(false);
		}
		return getInfo<cl_uint>(id);
	}

	auto Device::getOpenCLCVersion() const -> std::string {
		return getInfoString(CL_DEVICE_OPENCL_C_VERSION);
	}

#if defined(CL_VERSION_1_2)
	auto Device::getParentDevice() const -> boost::optional<Device> {
		const auto parentId = getInfo<cl_device_id>(CL_DEVICE_PARENT_DEVICE);
		if (parentId == nullptr) {
			return {};
		}
		return {{parentId}};
	}

	auto Device::getPartitionAffinityDomain() const -> AffinityDomainCapabilities {
		return {getInfo<cl_device_affinity_domain>(CL_DEVICE_PARTITION_AFFINITY_DOMAIN)};
	}

	auto Device::getPartitionMaxSubDevices() const -> cl_uint {
		return getInfo<cl_uint>(CL_DEVICE_PARTITION_MAX_SUB_DEVICES);
	}

	auto Device::getPartitionProperties() const -> PartitionCapabilities {
		return {getInfoVector<cl_device_partition_property>(CL_DEVICE_PARTITION_PROPERTIES)};
	}

	auto Device::getPartition() const -> Partition {
		return {getInfoVector<cl_device_partition_property>(CL_DEVICE_PARTITION_TYPE)};
	}
#endif // defined(CL_VERSION_1_2)

#if defined(CL_VERSION_2_0)
	auto Device::getPipeMaxActiveReservations() const -> cl_uint {
		return getInfo<cl_uint>(CL_DEVICE_PIPE_MAX_ACTIVE_RESERVATIONS);
	}

	auto Device::getPipeMaxPacketSize() const -> cl_uint {
		return getInfo<cl_uint>(CL_DEVICE_PIPE_MAX_PACKET_SIZE);
	}
#endif // defined(CL_VERSION_2_0)

	auto Device::getPlatform() const -> Platform {
		return {getInfo<cl_platform_id>(CL_DEVICE_PLATFORM)};
	}

	auto Device::getPreferredGlobalAtomicAlignment() const -> cl_uint {
		return getInfo<cl_uint>(CL_DEVICE_PREFERRED_GLOBAL_ATOMIC_ALIGNMENT);
	}

	auto Device::hasPreferredInteropUserSync() const -> cl_bool {
		return getInfo<cl_bool>(CL_DEVICE_PREFERRED_INTEROP_USER_SYNC);
	}

	auto Device::getPreferredLocalAtomicAlignment() const -> cl_uint {
		return getInfo<cl_uint>(CL_DEVICE_PREFERRED_LOCAL_ATOMIC_ALIGNMENT);
	}

	auto Device::getPreferredPlatformAtomicAlignment() const -> cl_uint {
		return getInfo<cl_uint>(CL_DEVICE_PREFERRED_PLATFORM_ATOMIC_ALIGNMENT);
	}

	auto Device::getPreferredVectorWidth(ScalarType type) const -> cl_uint {
		auto id = cl_device_info{};
		switch (type) {
			case ScalarType::charType:   id = CL_DEVICE_PREFERRED_VECTOR_WIDTH_CHAR;   break;
			case ScalarType::shortType:  id = CL_DEVICE_PREFERRED_VECTOR_WIDTH_SHORT;  break;
			case ScalarType::intType:    id = CL_DEVICE_PREFERRED_VECTOR_WIDTH_INT;    break;
			case ScalarType::longType:   id = CL_DEVICE_PREFERRED_VECTOR_WIDTH_LONG;   break;
			case ScalarType::floatType:  id = CL_DEVICE_PREFERRED_VECTOR_WIDTH_FLOAT;  break;
			case ScalarType::doubleType: id = CL_DEVICE_PREFERRED_VECTOR_WIDTH_DOUBLE; break;
			case ScalarType::halfType:   id = CL_DEVICE_PREFERRED_VECTOR_WIDTH_HALF;   break;
			default: assert(false);
		}
		return getInfo<cl_uint>(id);
	}


	auto Device::getPrintfBufferSize() const -> size_t {
		return getInfo<size_t>(CL_DEVICE_PRINTF_BUFFER_SIZE);
	}

	auto Device::getProfile() const -> std::string {
		return getInfoString(CL_DEVICE_PROFILE);
	}

	auto Device::getProfilingTimerResolution() const -> size_t {
		return getInfo<size_t>(CL_DEVICE_PROFILING_TIMER_RESOLUTION);
	}


	auto Device::getQueueOnDeviceMaxSize() const -> cl_uint {
		return getInfo<cl_uint>(CL_DEVICE_QUEUE_ON_DEVICE_MAX_SIZE);
	}

	auto Device::getQueueOnDevicePreferredSize() const -> cl_uint {
		return getInfo<cl_uint>(CL_DEVICE_QUEUE_ON_DEVICE_PREFERRED_SIZE);
	}

	auto Device::getQueueOnDeviceProperties() const -> CommandQueueProperties {
		return {getInfo<cl_command_queue_properties>(CL_DEVICE_QUEUE_ON_DEVICE_PROPERTIES)};
	}

	auto Device::getQueueOnHostProperties() const -> CommandQueueProperties {
		#if defined(CL_VERSION_2_0)
			return {getInfo<cl_command_queue_properties>(CL_DEVICE_QUEUE_ON_HOST_PROPERTIES)};
		#else
			return {getInfo<cl_command_queue_properties>(CL_DEVICE_QUEUE_PROPERTIES)};
		#endif
	}


	auto Device::getReferenceCount() const -> cl_uint {
		return getInfo<cl_uint>(CL_DEVICE_REFERENCE_COUNT);
	}


//	auto Device::getSpirVersions() const -> std::vector<std::string> {
//			  auto versions  = std::vector<std::string>{};
//		const auto verString = getInfoString(CL_DEVICE_SPIR_VERSIONS);
//		boost::split(versions, verString, boost::is_any_of("\t "), boost::token_compress_on);
//		return versions;
//	}

#if defined(CL_VERSION_2_0)
	auto Device::getSvmCapabilities() const -> SvmCapabilities {
		return {getInfo<cl_device_svm_capabilities>(CL_DEVICE_SVM_CAPABILITIES)};
	}
#endif // defined(CL_VERSION_2_0)

	auto Device::getType() const -> DeviceType {
		return static_cast<DeviceType>(getInfo<cl_device_type>(CL_DEVICE_TYPE));
	}

	auto Device::getVendor() const -> std::string {
		return getInfoString(CL_DEVICE_VENDOR);
	}

	auto Device::getVendorID() const -> cl_uint {
		return getInfo<cl_uint>(CL_DEVICE_VENDOR_ID);
	}

	auto Device::getVersion() const -> std::string {
		return getInfoString(CL_DEVICE_VERSION);
	}

	auto Device::getDriverVersion() const -> std::string {
		return getInfoString(CL_DRIVER_VERSION);
	}
}

#endif
