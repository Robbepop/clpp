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

			virtual auto code() const noexcept -> cl::RetCode = 0;
		};

		template<cl::RetCode retCode>
		class BasicError : public AnyError {
			using AnyError::AnyError;
			cl::RetCode code() const noexcept override { return retCode; }
		};

		using DeviceNotFound            = BasicError<RetCode::deviceNotFound>;
		using DeviceNotAvailable        = BasicError<RetCode::deviceNotAvailable>;
		using CompilerNotAvailable      = BasicError<RetCode::compilerNotAvailable>;
		using MemoryObjectAllocFailure  = BasicError<RetCode::memoryObjectAllocationFailure>;
		using OutOfResources            = BasicError<RetCode::outOfResources>;
		using OutOfHostMemory           = BasicError<RetCode::outOfHostMemory>;
		using ProfilingInfoNotAvailable = BasicError<RetCode::profilingInfoNotAvailable>;
		using MemoryCopyOverlap         = BasicError<RetCode::memoryCopyOverlap>;
		using ImageFormatMismatch       = BasicError<RetCode::imageFormatMismatch>;
		using ImageFormatNotSupported   = BasicError<RetCode::imageFormatNotSupported>;
		using BuildProgramFailure       = BasicError<RetCode::buildProgramFailure>;
		using MapFailure                = BasicError<RetCode::mapFailure>;
		using MisalignedSubBufferOffset = BasicError<RetCode::misalignedSubBufferOffset>;
		using ExecStatusErrorForEventsInWaitList
		                                = BasicError<RetCode::executeStatusErrorForEventsInWaitList>;
		using CompileProgramFailure     = BasicError<RetCode::compileProgramFailure>;
		using LinkerNotAvailable        = BasicError<RetCode::linkerNotAvailable>;
		using LinkProgramFailure        = BasicError<RetCode::linkProgramFailure>;
		using DevicePartitionFailure    = BasicError<RetCode::devicePartitionFailed>;
		using KernelArgInfoNotAvailable = BasicError<RetCode::kernelArgumentInfoNotAvailable>;


		using InvalidValue              = BasicError<RetCode::invalidValue>;
		using InvalidDeviceType         = BasicError<RetCode::invalidDeviceType>;
		using InvalidPlatform           = BasicError<RetCode::invalidPlatform>;
		using InvalidDevice             = BasicError<RetCode::invalidDevice>;
		using InvalidContext            = BasicError<RetCode::invalidContext>;
		using InvalidQueueProperties    = BasicError<RetCode::invalidQueueProperties>;
		using InvalidCommandQueue       = BasicError<RetCode::invalidCommandQueue>;
		using InvalidHostPtr            = BasicError<RetCode::invalidHostPtr>;
		using InvalidMemoryObject       = BasicError<RetCode::invalidMemoryObject>;
		using InvalidImageFormatDescriptor
		                                = BasicError<RetCode::invalidImageFormatDescriptor>;
		using InvalidImageSize          = BasicError<RetCode::invalidImageSize>;
		using InvalidSampler            = BasicError<RetCode::invalidSampler>;
		using InvalidBinary             = BasicError<RetCode::invalidBinary>;
		using InvalidBuildOptions       = BasicError<RetCode::invalidBuildOptions>;
		using InvalidProgram            = BasicError<RetCode::invalidProgram>;
		using InvalidProgramExecutable  = BasicError<RetCode::invalidProgramExecutable>;
		using InvalidKernelName         = BasicError<RetCode::invalidKernelName>;
		using InvalidKernelDefinition   = BasicError<RetCode::invalidKernelDefinition>;
		using InvalidKernel             = BasicError<RetCode::invalidKernel>;
		using InvalidArgIndex           = BasicError<RetCode::invalidArgumentIndex>;
		using InvalidArgValue           = BasicError<RetCode::invalidArgumentValue>;
		using InvalidArgSize            = BasicError<RetCode::invalidArgumentSize>;
		using InvalidKernelArgs         = BasicError<RetCode::invalidKernelArguments>;
		using InvalidWorkDimension      = BasicError<RetCode::invalidWorkDimension>;
		using InvalidWorkGroupSize      = BasicError<RetCode::invalidWorkGroupSize>;
		using InvalidWorkItemSize       = BasicError<RetCode::invalidWorkItemSize>;
		using InvalidGlobalOffset       = BasicError<RetCode::invalidGlobalOffset>;
		using InvalidEventWaitList      = BasicError<RetCode::invalidEventWaitList>;
		using InvalidEvent              = BasicError<RetCode::invalidEvent>;
		using InvalidOperation          = BasicError<RetCode::invalidOperation>;
		using InvalidGLObject           = BasicError<RetCode::invalidGlObject>;
		using InvalidBufferSize         = BasicError<RetCode::invalidBufferSize>;
		using InvalidMipLevel           = BasicError<RetCode::invalidMipLevel>;
		using InvalidGlobalWorkSize     = BasicError<RetCode::invalidGlobalWorkSize>;
		using InvalidProperty           = BasicError<RetCode::invalidProperty>;
		using InvalidImageDescriptor    = BasicError<RetCode::invalidImageDescriptor>;
		using InvalidCompilerOptions    = BasicError<RetCode::invalidCompilerOptions>;
		using InvalidLinkerOptions      = BasicError<RetCode::invalidLinkerOptions>;
		using InvalidDevicePartitionCount
		                                = BasicError<RetCode::invalidDevicePartitionCount>;
	}
}

#endif
