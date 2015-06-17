#ifndef CLPP_RET_CODE_HPP
#define CLPP_RET_CODE_HPP

#include "clpp/detail/common.hpp"

namespace cl {
	enum class RetCode : cl_int {
		success                               = CL_SUCCESS,

		deviceNotFound                        = CL_DEVICE_NOT_FOUND,
		deviceNotAvailable                    = CL_DEVICE_NOT_AVAILABLE,
		compilerNotAvailable                  = CL_COMPILER_NOT_AVAILABLE,
		memoryObjectAllocationFailure         = CL_MEM_OBJECT_ALLOCATION_FAILURE,
		outOfResources                        = CL_OUT_OF_RESOURCES,
		outOfHostMemory                       = CL_OUT_OF_HOST_MEMORY,
		profilingInfoNotAvailable             = CL_PROFILING_INFO_NOT_AVAILABLE,
		memoryCopyOverlap                     = CL_MEM_COPY_OVERLAP,
		imageFormatMismatch                   = CL_IMAGE_FORMAT_MISMATCH,
		imageFormatNotSupported               = CL_IMAGE_FORMAT_NOT_SUPPORTED,
		buildProgramFailure                   = CL_BUILD_PROGRAM_FAILURE,
		mapFailure                            = CL_MAP_FAILURE,
		misalignedSubBufferOffset             = CL_MISALIGNED_SUB_BUFFER_OFFSET,
		executeStatusErrorForEventsInWaitList = CL_EXEC_STATUS_ERROR_FOR_EVENTS_IN_WAIT_LIST,
		compileProgramFailure                 = CL_COMPILE_PROGRAM_FAILURE,
		linkerNotAvailable                    = CL_LINKER_NOT_AVAILABLE,
		linkProgramFailure                    = CL_LINK_PROGRAM_FAILURE,
		devicePartitionFailed                 = CL_DEVICE_PARTITION_FAILED,
		kernelArgumentInfoNotAvailable        = CL_KERNEL_ARG_INFO_NOT_AVAILABLE,

		invalidValue                     = CL_INVALID_VALUE,
		invalidDeviceType                = CL_INVALID_DEVICE_TYPE,
		invalidPlatform                  = CL_INVALID_PLATFORM,
		invalidDevice                    = CL_INVALID_DEVICE,
		invalidContext                   = CL_INVALID_CONTEXT,
		invalidQueueProperties           = CL_INVALID_QUEUE_PROPERTIES,
		invalidCommandQueue              = CL_INVALID_COMMAND_QUEUE,
		invalidHostPtr                   = CL_INVALID_HOST_PTR,
		invalidMemoryObject              = CL_INVALID_MEM_OBJECT,
		invalidImageFormatDescriptor     = CL_INVALID_IMAGE_FORMAT_DESCRIPTOR,
		invalidImageSize                 = CL_INVALID_IMAGE_SIZE,
		invalidSampler                   = CL_INVALID_SAMPLER,
		invalidBinary                    = CL_INVALID_BINARY,
		invalidBuildOptions              = CL_INVALID_BUILD_OPTIONS,
		invalidProgram                   = CL_INVALID_PROGRAM,
		invalidProgramExecutable         = CL_INVALID_PROGRAM_EXECUTABLE,
		invalidKernelName                = CL_INVALID_KERNEL_NAME,
		invalidKernelDefinition          = CL_INVALID_KERNEL_DEFINITION,
		invalidKernel                    = CL_INVALID_KERNEL,
		invalidArgumentIndex             = CL_INVALID_ARG_INDEX,
		invalidArgumentValue             = CL_INVALID_ARG_VALUE,
		invalidArgumentSize              = CL_INVALID_ARG_SIZE,
		invalidKernelArguments           = CL_INVALID_KERNEL_ARGS,
		invalidWorkDimension             = CL_INVALID_WORK_DIMENSION,
		invalidWorkGroupSize             = CL_INVALID_WORK_GROUP_SIZE,
		invalidWorkItemSize              = CL_INVALID_WORK_ITEM_SIZE,
		invalidGlobalOffset              = CL_INVALID_GLOBAL_OFFSET,
		invalidEventWaitList             = CL_INVALID_EVENT_WAIT_LIST,
		invalidEvent                     = CL_INVALID_EVENT,
		invalidOperation                 = CL_INVALID_OPERATION,
		invalidGlObject                  = CL_INVALID_GL_OBJECT,
		invalidBufferSize                = CL_INVALID_BUFFER_SIZE,
		invalidMipLevel                  = CL_INVALID_MIP_LEVEL,
		invalidGlobalWorkSize            = CL_INVALID_GLOBAL_WORK_SIZE,
		invalidProperty                  = CL_INVALID_PROPERTY,
		invalidImageDescriptor           = CL_INVALID_IMAGE_DESCRIPTOR,
		invalidCompilerOptions           = CL_INVALID_COMPILER_OPTIONS,
		invalidLinkerOptions             = CL_INVALID_LINKER_OPTIONS,
		invalidDevicePartitionCount      = CL_INVALID_DEVICE_PARTITION_COUNT
	};
}

#endif
