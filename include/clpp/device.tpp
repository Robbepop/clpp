#ifndef CLPP_DEVICE_H
	#error "Do not include this file directly!"
#endif

namespace cl {

	//====================================================================================
	// Constructor and Assignment
	//====================================================================================

    Device::Device():
		detail::Wrapper<Device::cl_type>{}
	{}

    Device::Device(Device::cl_type device):
		m_object{device}
	{}

    Device::Device(const Device & device):
		detail::Wrapper<cl_type>{device}
	{}

    Device& Device::operator=(const Device & rhs)
    {
        if (this != &rhs) {
            detail::Wrapper<cl_type>::operator=(rhs);
        }
        return *this;
    }


	//====================================================================================
	// Partitioning
	//====================================================================================

	auto Device::partition(Partition partition) -> std::vector<Device> {
		auto error      = cl_int{CL_INVALID_VALUE};
		auto countElems = cl_uint{0};
		error = clCreateSubDevices(m_object, partition.data(), 0, nullptr, std::addressof(countElems));
		detail::error::handle<DeviceException>(error, info_map);
		auto ids = std::vector<Device::cl_type>(countElems);
		error = clCreateSubDevices(m_object, properties.data(), countElems, ids.data(), nullptr);
		detail::error::handle<DeviceException>(error, info_map);
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

	auto Device::partitionByAffinityDomain(DeviceAffinityDomain domain)
		-> std::vector<Device>
	{
		return partition(Partition::byAffinityDomain(domain));
	}

	//====================================================================================
	// getInfo helper methods
	//====================================================================================

	auto getAddressBits() const -> cl_uint {
		return getInfo<cl_uint>(CL_DEVICE_ADDRESS_BITS);
	}

	auto isAvailable() const -> cl_bool {
		return getInfo<cl_bool>(CL_DEVICE_AVAILABLE);
	}

	auto isCompilerAvailable() const -> cl_bool {
		return getInfo<cl_bool>(CL_DEVICE_COMPILER_AVAILABLE);
	}

	auto getFpConfig(FPType type) const -> FPConfig {
		switch (type) {
		case FPType::halfPrecision:
			return {getInfo<cl_device_fp_config>(CL_DEVICE_HALF_FP_CONFIG)};
		case FPType::singlePrecision:
			return {getInfo<cl_device_fp_config>(CL_DEVICE_SINGLE_FP_CONFIG)};
		case FPType::doublePrecision:
			return {getInfo<cl_device_fp_config>(CL_DEVICE_DOUBLE_FP_CONFIG)};
		default:
			assert(false);
		}
	}

	auto isLittleEndian() const -> cl_bool {
		return getInfo<cl_bool>(CL_DEVICE_ENDIAN_LITTLE);
	}

	auto hasErrorCorrectionSupport() const -> cl_bool {
		return getInfo<cl_bool>(CL_DEVICE_ERROR_CORRECTION_SUPPORT);
	}

	auto getExecutionCapabilities() const -> ExecutionCapabilities {
		return {getInfo<cl_device_exec_capabilities>(CL_DEVICE_EXECUTION_CAPABILITIES)};
	}

	auto getExtensions() const -> std::vector<std::string> {
			  auto extensions = std::vector<std::string>{};
		const auto extString  = getInfoString(CL_DEVICE_EXTENSIONS);
		boost::split(extensions, extString, boost::is_any_of("\t "), boost::token_compress_on);
		return extensions;
	}


	auto getGlobalMemoryCacheSize() const -> cl_ulong {
		return getInfo<cl_ulong>(CL_DEVICE_GLOBAL_MEM_CACHE_SIZE);
	}

	auto getGlobalMemoryCacheType() const -> MemoryCacheType {
		return static_cast<MemoryCacheType>(
			getInfo<cl_device_mem_cache_type>(CL_DEVICE_GLOBAL_MEM_CACHE_TYPE));
	}

	auto getGlobalMemoryCachelineSize() const -> cl_uint {
		return getInfo<cl_uint>(CL_DEVICE_GLOBAL_MEM_CACHELINE_SIZE);
	}

	auto getGlobalMemorySize() const -> cl_ulong {
		return getInfo<cl_ulong>(CL_DEVICE_GLOBAL_MEM_SIZE);
	}

	auto getGlobalVariablePreferredTotalSize() const -> size_t {
		return getInfo<size_t>(CL_DEVICE_GLOBAL_VARIABLE_ PREFERRED_TOTAL_SIZE);
	}

	auto getImage2DMaxHeight() const -> size_t {
		return getInfo<size_t>(CL_DEVICE_IMAGE2D_MAX_HEIGHT);
	}

	auto getImage2DMaxWidth() const  -> size_t {
		return getInfo<size_t>(CL_DEVICE_IMAGE2D_MAX_WIDTH);
	}

	auto getImage3DMaxHeight() const -> size_t {
		return getInfo<size_t>(CL_DEVICE_IMAGE3D_MAX_HEIGHT);
	}

	auto getImage3DMaxWidth() const  -> size_t {
		return getInfo<size_t>(CL_DEVICE_IMAGE3D_MAX_WIDTH);
	}

	auto getImage3DMaxDepth() const  -> size_t {
		return getInfo<size_t>(CL_DEVICE_IMAGE3D_MAX_DEPTH);
	}


	auto getImageBaseAddressAlignment() const -> cl_uint {
		return getInfo<cl_uint>(CL_DEVICE_IMAGE_BASE_ADDRESS_ALIGNMENT);
	}

	auto getImageMaxArraySize() const -> size_t {
		return getInfo<size_t>(CL_DEVICE_IMAGE_MAX_ARRAY_SIZE);
	}

	auto getImageMaxBufferSize() const -> size_t {
		return getInfo<size_t>(CL_DEVICE_IMAGE_MAX_BUFFER_SIZE);
	}

	auto getImagePitchAlignment() const -> cl_uint {
		return getInfo<cl_uint>(CL_DEVICE_IMAGE_PITCH_ALIGNMENT);
	}

	auto hasImageSupport() const -> cl_bool {
		return getInfo<cl_bool>(CL_DEVICE_IMAGE_SUPPORT);
	}

	auto isLinkerAvailable() const -> cl_bool {
		return getInfo<cl_bool>(CL_DEVICE_LINKER_AVAILABLE);
	}

	auto getLocalMemorySize() const -> cl_ulong {
		return getInfo<cl_ulong>(CL_DEVICE_LOCAL_MEM_SIZE);
	}

	auto getLocalMemoryType() const  -> LocalMemoryType {
		return static_cast<LocalMemoryType>(
			getInfo<cl_device_local_mem_type>(CL_DEVICE_LOCAL_MEM_TYPE));
	}

	auto getMaxClockFrequency() const -> cl_uint {
		return getInfo<cl_uint>(CL_DEVICE_MAX_CLOCK_FREQUENCY);
	}

	auto getMaxComputeUnits() const -> cl_uint {
		return getInfo<cl_uint>(CL_DEVICE_MAX_COMPUTE_UNITS);
	}

	auto getMaxConstantArgs() const -> cl_uint {
		return getInfo<cl_uint>(CL_DEVICE_MAX_CONSTANT_ARGS);
	}

	auto getMaxConstantBufferSize() const -> cl_ulong {
		return getInfo<cl_ulong>(CL_DEVICE_MAX_CONSTANT_BUFFER_SIZE);
	}

	auto getMaxGlobalVariableSize() const -> size_t {
		return getInfo<size_t>(CL_DEVICE_MAX_GLOBAL_VARIABLE_SIZE);
	}

	auto getMaxMemoryAllocationSize() const -> cl_ulong {
		return getInfo<cl_ulong>(CL_DEVICE_MAX_MEM_ALLOC_SIZE);
	}

	auto getMaxOnDeviceEvents() const -> cl_uint {
		return getInfo<cl_uint>(CL_DEVICE_MAX_ON_DEVICE_EVENTS);
	}

	auto getMaxOnDeviceQueues() const -> cl_uint {
		return getInfo<cl_uint>(CL_DEVICE_MAX_ON_DEVICE_QUEUES);
	}

	auto getMaxParameterSize() const -> size_t {
		return getInfo<size_t>(CL_DEVICE_MAX_PARAMETER_SIZE);
	}

	auto getMaxPipeArgs() const -> cl_uint {
		return getInfo<cl_uint>(CL_DEVICE_MAX_PIPE_ARGS);
	}

	auto getMaxReadImageArgs() const -> cl_uint {
		return getInfo<cl_uint>(CL_DEVICE_MAX_READ_IMAGE_ARGS);
	}

	auto getMaxReadWriteImageArgs() const -> cl_uint {
		return getInfo<cl_uint>(CL_DEVICE_MAX_READ_WRITE_IMAGE_ARGS);
	}

	auto getMaxSamplers() const -> cl_uint {
		return getInfo<cl_uint>(CL_DEVICE_MAX_SAMPLERS);
	}

	auto getMaxWorkGroupSize() const -> size_t {
		return getInfo<size_t>(CL_DEVICE_MAX_WORK_GROUP_SIZE);
	}

	auto getMaxWorkItemDimensions() const -> cl_uint {
		return getInfo<cl_uint>(CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS);
	}

	auto getMaxWorkItemSizes() const -> std::vector<size_t> {
		return getInfoVector<size_t>(CL_DEVICE_MAX_WORK_ITEM_SIZES);
	}

	auto getMaxWriteImageArgs() const -> cl_uint {
		return getInfo<cl_uint>(CL_DEVICE_MAX_WRITE_IMAGE_ARGS);
	}


	auto getMemoryBaseAddressAlign() const -> cl_uint {
		return getInfo<cl_uint>(CL_DEVICE_MEM_BASE_ADDR_ALIGN);
	}


	auto getName() const                             -> std::string;
	auto getNativeVectorWidth(ScalarType type) const -> cl_uint;

	template<typename T>
	auto getNativeVectorWith<T>() const -> cl_uint;

	auto canPartitionEqually() const          -> cl_bool;
	auto canPartitionByCounts() const         -> cl_bool;
	auto canPartitionByAffinityDomain() const -> cl_bool;

	auto getPipeMaxActiveReservations() const -> cl_uint;
	auto getPipeMaxPacketSize() const         -> cl_uint;

	auto getParition() const                  -> Partition;

	auto getParentDevice() const                   -> Device;
	auto getPartitionAffinityDomain() const        -> AffinityDomain;
	auto getPreferredGlobalAtomicAlignment() const -> cl_uint;
	auto hasPreferredInteropUserSync() const       -> cl_bool;
	auto getPreferredLocalAtomicAlignment() const  -> cl_uint;
	auto getPreferredPlatformAtomicAlignment() const -> cl_uint;
	auto getPrintfBufferSize() const               -> size_t;
	auto getQueueOnDeviceMaxSize() const           -> cl_uint;
	auto getQueueOnDevicePreferredSize() const     -> cl_uint;
	auto getQueueOnDeviceProperties() const        -> CommandQueueProperties;
	auto getQueueOnHostProperties() const          -> CommandQueueProperties;
	auto getReferenceCount() const                 -> cl_uint;
	auto getSpirVersions() const                   -> std::vector<std::string>;
	auto getSvmCapabilities() const                -> SvmCapabilities;
	auto getTerminateCapabilities() const          -> TerminateCapabilities;
	auto getMaxSubDevices() const                  -> cl_uint;
	auto getPlatform() const                       -> Platform;
	auto getPreferredVectorWidth(ScalarType type) const -> cl_uint;
	auto getProfile() const                        -> std::string;
	auto getProfilingTimerResolution() const       -> size_t;
	auto getType() const                           -> DeviceType;
	auto getVendor() const                         -> std::string;
	auto getVendorID() const                       -> cl_uint;
	auto getVersion() const                        -> std::string;
	auto getVersionOpenCLC() const                 -> std::string;
	auto getDriverVersion() const                  -> std::string;

}
