#ifndef CLPP_EXCEPTION_H
#define CLPP_EXCEPTION_H

#include "clpp/detail/common.hpp"
#include "clpp/ret_code.hpp"

#include <stdexcept>

namespace cl {
	namespace error {
		class AnyError : public std::runtime_error {
		public:
			using std::runtime_error::runtime_error;

			virtual auto what() const noexcept -> const char * = 0;
			virtual auto code() const noexcept -> RetCode      = 0;
		};

		#define EXCEPTION(ExceptionName, RetCode, Msg)              \
			class ExceptionName final : public AnyError {           \
			public:                                                 \
				using AnyError::AnyError;                           \
				auto what() const override noexcept -> const char*; \
				auto code() const override noexcept -> RetCode;     \
			};                                                      \
			                                                        \
			auto ExceptionName::what() const noexcept               \
				-> const char *                                     \
			{                                                       \
				return Msg;                                         \
			}                                                       \
			                                                        \
			auto ExceptionName::code() const noexcept               \
				-> RetCode                                          \
			{                                                       \
				return RetCode;                                     \
			}

			EXCEPTION(DeviceNotFound,
				RetCode::deviceNotFound, "device not found")
			EXCEPTION(DeviceNotAvailable,
				RetCode::deviceNotAvailable, "device not available")
			EXCEPTION(CompilerNotAvailable,
				RetCode::compilerNotAvailable, "compiler not available")
			EXCEPTION(MemoryObjectAllocFailure,
				RetCode::memoryObjectAllocationFailure, "memory object allocation failure")
			EXCEPTION(OutOfResources,
				RetCode::outOfResources, "out of resources")
			EXCEPTION(OutOfHostMemory,
				RetCode::outOfHostMemory, "out of host memory")
			EXCEPTION(ProfilingInfoNotAvailable,
				RetCode::profilingInfoNotAvailable, "profiling info not available")
			EXCEPTION(MemoryCopyOverlap,
				RetCode::memoryCopyOverlap, "memory copy overlap")
			EXCEPTION(ImageFormatMismatch,
				RetCode::imageFormatMismatch, "image format mismatch")
			EXCEPTION(ImageFormatNotSupported,
				RetCode::imageFormatNotSupported, "image format not supported")
			EXCEPTION(BuildProgramFailure,
				RetCode::buildProgramFailure, "build program failure")
			EXCEPTION(MapFailure,
				RetCode::mapFailure, "map failure")
			EXCEPTION(MisalignedSubBufferOffset,
				RetCode::misalignedSubBufferOffset, "misaligned sub buffer offset")
			EXCEPTION(ExecStatusErrorForEventsInWaitList,
				RetCode::executeStatusErrorForEventsInWaitList, "execute status error for events in wait list")
			EXCEPTION(CompileProgramFailure,
				RetCode::compileProgramFailure, "compile program failure")
			EXCEPTION(LinkerNotAvailable,
				RetCode::linkerNotAvailable, "linker not available")
			EXCEPTION(LinkProgramFailure,
				RetCode::linkProgramFailure, "link program failure")
			EXCEPTION(DevicePartitionFailure,
				RetCode::devicePartitionFailed, "device partition failure")
			EXCEPTION(KernelArgInfoNotAvailable,
				RetCode::kernelArgumentInfoNotAvailable, "kernel argument not available")

			EXCEPTION(InvalidValue,
				RetCode::invalidValue, "invalid value")
			EXCEPTION(InvalidDeviceType,
				RetCode::invalidDeviceType, "invalid device type")
			EXCEPTION(InvalidPlatform,
				RetCode::invalidPlatform, "invalid platform")
			EXCEPTION(InvalidDevice,
				RetCode::invalidDevice, "invalid device")
			EXCEPTION(InvalidContext,
				RetCode::invalidContext, "invalid context")
			EXCEPTION(InvalidQueueProperties,
				RetCode::invalidQueueProperties, "invalid command queue properties")
			EXCEPTION(InvalidCommandQueue,
				RetCode::invalidCommandQueue, "invalid command queue")
			EXCEPTION(InvalidHostPtr,
				RetCode::invalidHostPtr, "invalid host pointer")
			EXCEPTION(InvalidMemoryObject,
				RetCode::invalidMemoryObject, "invalid memory object")
			EXCEPTION(InvalidImageFormatDescriptor,
				RetCode::invalidImageFormatDescriptor, "invalid image format descriptor")
			EXCEPTION(InvalidImageSize,
				RetCode::invalidImageSize, "invalid image size")
			EXCEPTION(InvalidSampler,
				RetCode::invalidSampler, "invalid sampler")
			EXCEPTION(InvalidBinary,
				RetCode::invalidBinary, "invalid binary")
			EXCEPTION(InvalidBuildOptions,
				RetCode::invalidBuildOptions, "invalid build options")
			EXCEPTION(InvalidProgram,
				RetCode::invalidProgram, "invalid program")
			EXCEPTION(InvalidProgramExecutable,
				RetCode::invalidProgramExecutable, "invalid program executable")
			EXCEPTION(InvalidKernelName,
				RetCode::invalidKernelName, "invalid kernel name")
			EXCEPTION(InvalidKernelDefinition,
				RetCode::invalidKernelDefinition, "invalid kernel definition")
			EXCEPTION(InvalidKernel,
				RetCode::invalidKernel, "invalid kernel")
			EXCEPTION(InvalidArgIndex,
				RetCode::invalidArgumentIndex, "invalid argument index")
			EXCEPTION(InvalidArgValue,
				RetCode::invalidArgumentValue, "invalid argument value")
			EXCEPTION(InvalidArgSize,
				RetCode::invalidArgumentSize, "invalid argument size")
			EXCEPTION(InvalidKernelArgs,
				RetCode::invalidKernelArguments, "invalid kernel arguments")
			EXCEPTION(InvalidWorkDimension,
				RetCode::invalidWorkDimension, "invalid work dimension")
			EXCEPTION(InvalidWorkGroupSize,
				RetCode::invalidWorkGroupSize, "invalid work group size")
			EXCEPTION(InvalidWorkItemSize,
				RetCode::invalidWorkItemSize, "invalid work item size")
			EXCEPTION(InvalidGlobalOffset,
				RetCode::invalidGlobalOffset, "invalid global offset")
			EXCEPTION(InvalidEventWaitList,
				RetCode::invalidEventWaitList, "invalid event wait list")
			EXCEPTION(InvalidEvent,
				RetCode::invalidEvent, "invalid event")
			EXCEPTION(InvalidOperation,
				RetCode::invalidOperation, "invalid operation")
			EXCEPTION(InvalidGLObject,
				RetCode::invalidGlObject, "invalid OpenGL object")
			EXCEPTION(InvalidBufferSize,
				RetCode::invalidBufferSize, "invalid buffer size")
			EXCEPTION(InvalidMipLevel,
				RetCode::invalidMipLevel, "invalid MIP level")
			EXCEPTION(InvalidGlobalWorkSize,
				RetCode::invalidGlobalWorkSize, "invalid global work size")
			EXCEPTION(InvalidProperty,
				RetCode::invalidProperty, "invalid property")
			EXCEPTION(InvalidImageDescriptor,
				RetCode::invalidImageDescriptor, "invalid image descriptor")
			EXCEPTION(InvalidCompilerOptions,
				RetCode::invalidCompilerOptions, "invalid compiler options")
			EXCEPTION(InvalidLinkerOptions,
				RetCode::invalidLinkerOptions, "invalid linker options")
			EXCEPTION(InvalidDevicePartitionCount,
				RetCode::invalidDevicePartitionCount, "invalid device partition count")
		#undef EXCEPTION
	}
}

#endif
