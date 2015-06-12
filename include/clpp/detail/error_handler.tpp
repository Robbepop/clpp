#ifndef CLPP_DETAIL_ERROR_HANDLER_H
	#error "Do not include this file directly!"
#endif

#include "clpp/ret_code.hpp"
#include "clpp/exception.hpp"

#include <type_traits>
#include <map>

namespace cl {
	namespace detail {

		auto error::isError(code_type code) -> cl_bool {
			return code != CL_SUCCESS;
		}

		auto error::isError(RetCode code) -> cl_bool {
			return isError(static_cast<code_type>(code));
		}

		auto error::isSuccess(code_type code) -> cl_bool {
			return code == CL_SUCCESS;
		}

		auto error::isSuccess(RetCode code) -> cl_bool {
			return isSuccess(static_cast<code_type>(code));
		}

		void error::throwException(RetCode code) {
			switch (code) {
				case RetCode::deviceNotFound:
					return DeviceNotFound{"device not found"};
				case RetCode::deviceNotAvailable:
					return DeviceNotAvailable{"device not available"};
				case RetCode::compilerNotAvailable:
					return CompilerNotAvailable{"compiler not available"};
				case RetCode::memoryObjectAllocationFailure:
					return MemoryObjectAllocFailure{"memory object allocation failure"};
				case RetCode::outOfResources:
					return OutOfResources{"out of resources"};
				case RetCode::outOfHostMemory:
					return OutOfHostMemory{"out of host memory"};
				case RetCode::profilingInfoNotAvailable:
					return ProfilingInfoNotAvailable{"profiling info not available"};
				case RetCode::memoryCopyOverlap:
					return MemoryCopyOverlap{"memory copy overlap"};
				case RetCode::imageFormatMismatch:
					return ImageFormatMismatch{"image format mismatch"};
				case RetCode::imageFormatNotSupported:
					return ImageFormatNotSupported{"image format not supported"};
				case RetCode::buildProgramFailure:
					return BuildProgramFailure{"build program failure"};
				case RetCode::mapFailure:
					return MapFailure{"map failure"};
				case RetCode::misalignedSubBufferOffset:
					return MisalignedSubBufferOffset{"misaligned sub buffer offset"};
				case RetCode::executeStatusErrorForEventsInWaitList:
					return ExecStatusErrorForEventsInWaitList{"execution status error for events in wait list"};
				case RetCode::compileProgramFailure:
					return CompileProgramFailure{"compile program failure"};
				case RetCode::linkerNotAvailable:
					return LinkerNotAvailable{"linker not available"};
				case RetCode::linkProgramFailure:
					return LinkProgramFailure{"link program failure"};
				case RetCode::devicePartitionFailed:
					return DevicePartitionFailure{"device partition failure"};
				case RetCode::kernelArgumentInfoNotAvailable:
					return KernelArgInfoNotAvailable{"kernel argument info not available"};

				case RetCode::invalidValue:
					return InvalidValue{"invalid value"};
				case RetCode::invalidDeviceType:
					return InvalidDeviceType{"invalid device type"};
				case RetCode::invalidPlatform:
					return InvalidPlatform{"invalid platform"};
				case RetCode::invalidDevice:
					return InvalidDevice{"invalid device"};
				case RetCode::invalidContext:
					return InvalidContext{"invalid context"};
				case RetCode::invalidQueueProperties:
					return InvalidQueueProperties{"invalid queue properties"};
				case RetCode::invalidCommandQueue:
					return InvalidCommandQueue{"invalid command queue"};
				case RetCode::invalidHostPtr:
					return InvalidHostPtr{"invalid host pointer"};
				case RetCode::invalidMemoryObject:
					return InvalidMemoryObject{"invaild memory object"};
				case RetCode::invalidImageFormatDescriptor:
					return InvalidImageFormatDescriptor{"invalid image format descriptor"};
				case RetCode::invalidImageSize:
					return InvalidImageSize{"invalid image size"};
				case RetCode::invalidSampler:
					return InvalidSampler{"invalid sampler"};
				case RetCode::invalidBinary:
					return InvalidBinary{"invalid binary"};
				case RetCode::invalidBuildOptions:
					return InvalidBuildOptions{"invalid build options"};
				case RetCode::invalidProgram:
					return InvalidProgram{"invalid program"};
				case RetCode::invalidProgramExecutable:
					return InvalidProgramExecutable{"invalid program executable"};
				case RetCode::invalidKernelName:
					return InvalidKernelName{"invalid kernel name"};
				case RetCode::invalidKernelDefinition:
					return InvalidKernelDefinition{"invalid kernel definition"};
				case RetCode::invalidKernel:
					return InvalidKernel{"invalid kernel"};
				case RetCode::invalidArgumentIndex:
					return InvalidArgIndex{"invalid argument index"};
				case RetCode::invalidArgumentValue:
					return InvalidArgValue{"invalid argument value"};
				case RetCode::invalidArgumentSize:
					return InvalidArgSize{"invalid argument size"};
				case RetCode::invalidKernelArguments:
					return InvalidKernelArgs{"invalid kernel arguments"};
				case RetCode::invalidWorkDimension:
					return InvalidWorkDimension{"invalid work dimension"};
				case RetCode::invalidWorkGroupSize:
					return InvalidWorkGroupSize{"invalid work group size"};
				case RetCode::invalidWorkItemSize:
					return InvalidWorkItemSize{"invalid work item size"};
				case RetCode::invalidGlobalOffset:
					return InvalidGlobalOffset{"invalid global offset"};
				case RetCode::invalidEventWaitList:
					return InvalidEventWaitList{"invalid event wait list"};
				case RetCode::invalidEvent:
					return InvalidEvent{"invalid event"};
				case RetCode::invalidOperation:
					return InvalidOperation{"invalid operation"};
				case RetCode::invalidGlObject:
					return InvalidGLObject{"invalid OpenGL object"};
				case RetCode::invalidBufferSize:
					return InvalidBufferSize{"invalid buffer size"};
				case RetCode::invalidMipLevel:
					return InvalidMipLevel{"invalid mip level"};
				case RetCode::invalidGlobalWorkSize:
					return InvalidGlobalWorkSize{"invalid global work size"};
				case RetCode::invalidProperty:
					return InvalidProperty{"invalid property"};
				case RetCode::invalidImageDescriptor:
					return InvalidImageDescriptor{"invalid image descriptor"};
				case RetCode::invalidCompilerOptions:
					return InvalidCompilerOptions{"invalid compiler options"};
				case RetCode::invalidLinkerOptions:
					return InvalidLinkerOptions{"invalid linker options"};
				case RetCode::invalidDevicePartitionCount:
					return InvalidDevicePartitionCount{"invalid device partition count"};

				default:
					assert(false);
			}
		}

		auto error::handle(
			RetCode code,
			error::info_map const* local_info_map
		)
			-> cl_bool
		{
			using namespace std::literals;
			static const auto global_info_map = info_map{
				{RetCode::outOfResources, "there was a failure to allocate resources required by the OpenCL implementation on the device."},
				{RetCode::outOfHostMemory, "there was a failure to allocate resources required by the OpenCL implementation on the host."}
			};
			if (isSuccess(code)) { return CL_SUCCESS; }
			if (local_info_map != nullptr) {
				const auto it = local_info_map->find(code);
				const auto errorMessage =
					it != local_info_map->end() ? it->second : ""s;
				throw std::runtime_error{errorMessage};
//				throw ExceptionType{code, errorMessage};
			}
			const auto it = global_info_map.find(code);
			throw std::runtime_error{it != global_info_map.end() ? it->second : ""s};
		}

		auto error::handle(
			error::code_type code,
			error::info_map const& local_info_map
		)
			-> cl_bool
		{
			return handle(
				static_cast<RetCode>(code),
				std::addressof(local_info_map));
		}

		auto error::handle(error::code_type code) -> cl_bool {
			return handle(static_cast<RetCode>(code), nullptr);
		}
	}
}
