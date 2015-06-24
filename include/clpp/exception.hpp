#ifndef CLPP_EXCEPTION_HPP
#define CLPP_EXCEPTION_HPP

#include "clpp/detail/common.hpp"
#include "clpp/ret_code.hpp"

#include <stdexcept>

namespace cl {
	namespace error {
		class AnyError : public std::runtime_error {
		public:
			using std::runtime_error::runtime_error;

			virtual detail::CLFunction func() const noexcept = 0;
			virtual RetCode code() const noexcept = 0;
		};

		template<RetCode::id_type retCode>
		class BasicError : public AnyError {
		public:
			using AnyError::AnyError;
			BasicError(detail::CLFunction const& func, std::string const& msg):
				AnyError{msg},
				m_func{func}
			{}

			detail::CLFunction func() const noexcept override { return m_func; }
			RetCode code() const noexcept override { return retCode; }

		private:
			detail::CLFunction m_func = detail::CLFunction::unknown();
		};

		using DeviceNotFound            = BasicError<CL_DEVICE_NOT_FOUND>;
		using DeviceNotAvailable        = BasicError<CL_DEVICE_NOT_AVAILABLE>;
		using CompilerNotAvailable      = BasicError<CL_COMPILER_NOT_AVAILABLE>;
		using MemoryObjectAllocFailure  = BasicError<CL_MEM_OBJECT_ALLOCATION_FAILURE>;
		using OutOfResources            = BasicError<CL_OUT_OF_RESOURCES>;
		using OutOfHostMemory           = BasicError<CL_OUT_OF_HOST_MEMORY>;
		using ProfilingInfoNotAvailable = BasicError<CL_PROFILING_INFO_NOT_AVAILABLE>;
		using MemoryCopyOverlap         = BasicError<CL_MEM_COPY_OVERLAP>;
		using ImageFormatMismatch       = BasicError<CL_IMAGE_FORMAT_MISMATCH>;
		using ImageFormatNotSupported   = BasicError<CL_IMAGE_FORMAT_NOT_SUPPORTED>;
		using BuildProgramFailure       = BasicError<CL_BUILD_PROGRAM_FAILURE>;
		using MapFailure                = BasicError<CL_MAP_FAILURE>;
		using MisalignedSubBufferOffset = BasicError<CL_MISALIGNED_SUB_BUFFER_OFFSET>;
		using ExecStatusErrorForEventsInWaitList
		                                = BasicError<CL_EXEC_STATUS_ERROR_FOR_EVENTS_IN_WAIT_LIST>;
		using CompileProgramFailure     = BasicError<CL_COMPILE_PROGRAM_FAILURE>;
		using LinkerNotAvailable        = BasicError<CL_LINKER_NOT_AVAILABLE>;
		using LinkProgramFailure        = BasicError<CL_LINK_PROGRAM_FAILURE>;
		using DevicePartitionFailure    = BasicError<CL_DEVICE_PARTITION_FAILED>;
		using KernelArgInfoNotAvailable = BasicError<CL_KERNEL_ARG_INFO_NOT_AVAILABLE>;


		using InvalidValue              = BasicError<CL_INVALID_VALUE>;
		using InvalidDeviceType         = BasicError<CL_INVALID_DEVICE_TYPE>;
		using InvalidPlatform           = BasicError<CL_INVALID_PLATFORM>;
		using InvalidDevice             = BasicError<CL_INVALID_DEVICE>;
		using InvalidContext            = BasicError<CL_INVALID_CONTEXT>;
		using InvalidQueueProperties    = BasicError<CL_INVALID_QUEUE_PROPERTIES>;
		using InvalidCommandQueue       = BasicError<CL_INVALID_COMMAND_QUEUE>;
		using InvalidHostPtr            = BasicError<CL_INVALID_HOST_PTR>;
		using InvalidMemoryObject       = BasicError<CL_INVALID_MEM_OBJECT>;
		using InvalidImageFormatDescriptor
		                                = BasicError<CL_INVALID_IMAGE_DESCRIPTOR>;
		using InvalidImageSize          = BasicError<CL_INVALID_IMAGE_SIZE>;
		using InvalidSampler            = BasicError<CL_INVALID_SAMPLER>;
		using InvalidBinary             = BasicError<CL_INVALID_BINARY>;
		using InvalidBuildOptions       = BasicError<CL_INVALID_BUILD_OPTIONS>;
		using InvalidProgram            = BasicError<CL_INVALID_PROGRAM>;
		using InvalidProgramExecutable  = BasicError<CL_INVALID_PROGRAM_EXECUTABLE>;
		using InvalidKernelName         = BasicError<CL_INVALID_KERNEL_NAME>;
		using InvalidKernelDefinition   = BasicError<CL_INVALID_KERNEL_DEFINITION>;
		using InvalidKernel             = BasicError<CL_INVALID_KERNEL>;
		using InvalidArgIndex           = BasicError<CL_INVALID_ARG_INDEX>;
		using InvalidArgValue           = BasicError<CL_INVALID_ARG_VALUE>;
		using InvalidArgSize            = BasicError<CL_INVALID_ARG_SIZE>;
		using InvalidKernelArgs         = BasicError<CL_INVALID_KERNEL_ARGS>;
		using InvalidWorkDimension      = BasicError<CL_INVALID_WORK_DIMENSION>;
		using InvalidWorkGroupSize      = BasicError<CL_INVALID_WORK_GROUP_SIZE>;
		using InvalidWorkItemSize       = BasicError<CL_INVALID_WORK_ITEM_SIZE>;
		using InvalidGlobalOffset       = BasicError<CL_INVALID_GLOBAL_OFFSET>;
		using InvalidEventWaitList      = BasicError<CL_INVALID_EVENT_WAIT_LIST>;
		using InvalidEvent              = BasicError<CL_INVALID_EVENT>;
		using InvalidOperation          = BasicError<CL_INVALID_OPERATION>;
		using InvalidGLObject           = BasicError<CL_INVALID_GL_OBJECT>;
		using InvalidBufferSize         = BasicError<CL_INVALID_BUFFER_SIZE>;
		using InvalidMipLevel           = BasicError<CL_INVALID_MIP_LEVEL>;
		using InvalidGlobalWorkSize     = BasicError<CL_INVALID_GLOBAL_WORK_SIZE>;
		using InvalidProperty           = BasicError<CL_INVALID_PROPERTY>;
		using InvalidImageDescriptor    = BasicError<CL_INVALID_IMAGE_DESCRIPTOR>;
		using InvalidCompilerOptions    = BasicError<CL_INVALID_COMPILER_OPTIONS>;
		using InvalidLinkerOptions      = BasicError<CL_INVALID_LINKER_OPTIONS>;
		using InvalidDevicePartitionCount
		                                = BasicError<CL_INVALID_DEVICE_PARTITION_COUNT>;
	}
}

#endif
