#ifndef CLPP_DETAIL_ERROR_HANDLER_H
	#error "Do not include this file directly!"
#endif

#include "clpp/ret_code.hpp"
#include "clpp/exception.hpp"

#include <type_traits>
#include <map>
#include <cassert>

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
			using namespace error;
			switch (code) {
				case RetCode::deviceNotFound:
					throw DeviceNotFound{"device not found"};
				case RetCode::deviceNotAvailable:
					throw DeviceNotAvailable{"device not available"};
				case RetCode::compilerNotAvailable:
					throw CompilerNotAvailable{"compiler not available"};
				case RetCode::memoryObjectAllocationFailure:
					throw MemoryObjectAllocFailure{"memory object allocation failure"};
				case RetCode::outOfResources:
					throw OutOfResources{"out of resources"};
				case RetCode::outOfHostMemory:
					throw OutOfHostMemory{"out of host memory"};
				case RetCode::profilingInfoNotAvailable:
					throw ProfilingInfoNotAvailable{"profiling info not available"};
				case RetCode::memoryCopyOverlap:
					throw MemoryCopyOverlap{"memory copy overlap"};
				case RetCode::imageFormatMismatch:
					throw ImageFormatMismatch{"image format mismatch"};
				case RetCode::imageFormatNotSupported:
					throw ImageFormatNotSupported{"image format not supported"};
				case RetCode::buildProgramFailure:
					throw BuildProgramFailure{"build program failure"};
				case RetCode::mapFailure:
					throw MapFailure{"map failure"};
				case RetCode::misalignedSubBufferOffset:
					throw MisalignedSubBufferOffset{"misaligned sub buffer offset"};
				case RetCode::executeStatusErrorForEventsInWaitList:
					throw ExecStatusErrorForEventsInWaitList{"execution status error for events in wait list"};
				case RetCode::compileProgramFailure:
					throw CompileProgramFailure{"compile program failure"};
				case RetCode::linkerNotAvailable:
					throw LinkerNotAvailable{"linker not available"};
				case RetCode::linkProgramFailure:
					throw LinkProgramFailure{"link program failure"};
				case RetCode::devicePartitionFailed:
					throw DevicePartitionFailure{"device partition failure"};
				case RetCode::kernelArgumentInfoNotAvailable:
					throw KernelArgInfoNotAvailable{"kernel argument info not available"};

				case RetCode::invalidValue:
					throw InvalidValue{"invalid value"};
				case RetCode::invalidDeviceType:
					throw InvalidDeviceType{"invalid device type"};
				case RetCode::invalidPlatform:
					throw InvalidPlatform{"invalid platform"};
				case RetCode::invalidDevice:
					throw InvalidDevice{"invalid device"};
				case RetCode::invalidContext:
					throw InvalidContext{"invalid context"};
				case RetCode::invalidQueueProperties:
					throw InvalidQueueProperties{"invalid queue properties"};
				case RetCode::invalidCommandQueue:
					throw InvalidCommandQueue{"invalid command queue"};
				case RetCode::invalidHostPtr:
					throw InvalidHostPtr{"invalid host pointer"};
				case RetCode::invalidMemoryObject:
					throw InvalidMemoryObject{"invaild memory object"};
				case RetCode::invalidImageFormatDescriptor:
					throw InvalidImageFormatDescriptor{"invalid image format descriptor"};
				case RetCode::invalidImageSize:
					throw InvalidImageSize{"invalid image size"};
				case RetCode::invalidSampler:
					throw InvalidSampler{"invalid sampler"};
				case RetCode::invalidBinary:
					throw InvalidBinary{"invalid binary"};
				case RetCode::invalidBuildOptions:
					throw InvalidBuildOptions{"invalid build options"};
				case RetCode::invalidProgram:
					throw InvalidProgram{"invalid program"};
				case RetCode::invalidProgramExecutable:
					throw InvalidProgramExecutable{"invalid program executable"};
				case RetCode::invalidKernelName:
					throw InvalidKernelName{"invalid kernel name"};
				case RetCode::invalidKernelDefinition:
					throw InvalidKernelDefinition{"invalid kernel definition"};
				case RetCode::invalidKernel:
					throw InvalidKernel{"invalid kernel"};
				case RetCode::invalidArgumentIndex:
					throw InvalidArgIndex{"invalid argument index"};
				case RetCode::invalidArgumentValue:
					throw InvalidArgValue{"invalid argument value"};
				case RetCode::invalidArgumentSize:
					throw InvalidArgSize{"invalid argument size"};
				case RetCode::invalidKernelArguments:
					throw InvalidKernelArgs{"invalid kernel arguments"};
				case RetCode::invalidWorkDimension:
					throw InvalidWorkDimension{"invalid work dimension"};
				case RetCode::invalidWorkGroupSize:
					throw InvalidWorkGroupSize{"invalid work group size"};
				case RetCode::invalidWorkItemSize:
					throw InvalidWorkItemSize{"invalid work item size"};
				case RetCode::invalidGlobalOffset:
					throw InvalidGlobalOffset{"invalid global offset"};
				case RetCode::invalidEventWaitList:
					throw InvalidEventWaitList{"invalid event wait list"};
				case RetCode::invalidEvent:
					throw InvalidEvent{"invalid event"};
				case RetCode::invalidOperation:
					throw InvalidOperation{"invalid operation"};
				case RetCode::invalidGlObject:
					throw InvalidGLObject{"invalid OpenGL object"};
				case RetCode::invalidBufferSize:
					throw InvalidBufferSize{"invalid buffer size"};
				case RetCode::invalidMipLevel:
					throw InvalidMipLevel{"invalid mip level"};
				case RetCode::invalidGlobalWorkSize:
					throw InvalidGlobalWorkSize{"invalid global work size"};
				case RetCode::invalidProperty:
					throw InvalidProperty{"invalid property"};
				case RetCode::invalidImageDescriptor:
					throw InvalidImageDescriptor{"invalid image descriptor"};
				case RetCode::invalidCompilerOptions:
					throw InvalidCompilerOptions{"invalid compiler options"};
				case RetCode::invalidLinkerOptions:
					throw InvalidLinkerOptions{"invalid linker options"};
				case RetCode::invalidDevicePartitionCount:
					throw InvalidDevicePartitionCount{"invalid device partition count"};

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
				throwException(code);
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
