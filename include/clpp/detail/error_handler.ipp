#ifdef  CLPP_DETAIL_ERROR_HANDLER_IPP
	#error "multiple inclusions of the same implementation file"
#else
#define CLPP_DETAIL_ERROR_HANDLER_IPP

#ifndef CLPP_DETAIL_ERROR_HANDLER_HPP
	#error "header file has not been included; maybe it isn't required anymore?"
	#include "clpp/detail/error_handler.hpp"
#endif

#include "clpp/ret_code.hpp"
#include "clpp/exception.hpp"

#include <type_traits>
#include <map>
#include <cassert>

namespace cl {
	namespace detail {
		namespace impl {
			void throwException(CLFunction const& func, RetCode2 const& code) {
				using namespace ::cl::error;
				const auto msg = std::string{code.getCLName().to_string()}
					+ " (" + std::to_string(code.getCLId()) + ") thrown by "
					+ func.getCLName().to_string() + '\n';

				switch (code.getCLId()) {
					default: assert(false);

					case CL_DEVICE_NOT_FOUND:
						throw DeviceNotFound{msg};
					case CL_DEVICE_NOT_AVAILABLE:
						throw DeviceNotAvailable{msg};
					case CL_COMPILER_NOT_AVAILABLE:
						throw CompilerNotAvailable{msg};
					case CL_MEM_OBJECT_ALLOCATION_FAILURE:
						throw MemoryObjectAllocFailure{msg};
					case CL_OUT_OF_RESOURCES:
						throw OutOfResources{msg};
					case CL_OUT_OF_HOST_MEMORY:
						throw OutOfHostMemory{msg};
					case CL_PROFILING_INFO_NOT_AVAILABLE:
						throw ProfilingInfoNotAvailable{msg};
					case CL_MEM_COPY_OVERLAP:
						throw MemoryCopyOverlap{msg};
					case CL_IMAGE_FORMAT_MISMATCH:
						throw ImageFormatMismatch{msg};
					case CL_IMAGE_FORMAT_NOT_SUPPORTED:
						throw ImageFormatNotSupported{msg};
					case CL_BUILD_PROGRAM_FAILURE:
						throw BuildProgramFailure{msg};
					case CL_MAP_FAILURE:
						throw MapFailure{msg};
					case CL_MISALIGNED_SUB_BUFFER_OFFSET:
						throw MisalignedSubBufferOffset{msg};
					case CL_EXEC_STATUS_ERROR_FOR_EVENTS_IN_WAIT_LIST:
						throw ExecStatusErrorForEventsInWaitList{msg};
					case CL_COMPILE_PROGRAM_FAILURE:
						throw CompileProgramFailure{msg};
					case CL_LINKER_NOT_AVAILABLE:
						throw LinkerNotAvailable{msg};
					case CL_LINK_PROGRAM_FAILURE:
						throw LinkProgramFailure{msg};
					case CL_DEVICE_PARTITION_FAILED:
						throw DevicePartitionFailure{msg};
					case CL_KERNEL_ARG_INFO_NOT_AVAILABLE:
						throw KernelArgInfoNotAvailable{msg};

					case CL_INVALID_VALUE:
						throw InvalidValue{msg};
					case CL_INVALID_DEVICE_TYPE:
						throw InvalidDeviceType{msg};
					case CL_INVALID_PLATFORM:
						throw InvalidPlatform{msg};
					case CL_INVALID_DEVICE:
						throw InvalidDevice{msg};
					case CL_INVALID_CONTEXT:
						throw InvalidContext{msg};
					case CL_INVALID_QUEUE_PROPERTIES:
						throw InvalidQueueProperties{msg};
					case CL_INVALID_COMMAND_QUEUE:
						throw InvalidCommandQueue{msg};
					case CL_INVALID_HOST_PTR:
						throw InvalidHostPtr{msg};
					case CL_INVALID_MEM_OBJECT:
						throw InvalidMemoryObject{msg};
					case CL_INVALID_IMAGE_FORMAT_DESCRIPTOR:
						throw InvalidImageFormatDescriptor{msg};
					case CL_INVALID_IMAGE_SIZE:
						throw InvalidImageSize{msg};
					case CL_INVALID_SAMPLER:
						throw InvalidSampler{msg};
					case CL_INVALID_BINARY:
						throw InvalidBinary{msg};
					case CL_INVALID_BUILD_OPTIONS:
						throw InvalidBuildOptions{msg};
					case CL_INVALID_PROGRAM:
						throw InvalidProgram{msg};
					case CL_INVALID_PROGRAM_EXECUTABLE:
						throw InvalidProgramExecutable{msg};
					case CL_INVALID_KERNEL_NAME:
						throw InvalidKernelName{msg};
					case CL_INVALID_KERNEL_DEFINITION:
						throw InvalidKernelDefinition{msg};
					case CL_INVALID_KERNEL:
						throw InvalidKernel{msg};
					case CL_INVALID_ARG_INDEX:
						throw InvalidArgIndex{msg};
					case CL_INVALID_ARG_VALUE:
						throw InvalidArgValue{msg};
					case CL_INVALID_ARG_SIZE:
						throw InvalidArgSize{msg};
					case CL_INVALID_KERNEL_ARGS:
						throw InvalidKernelArgs{msg};
					case CL_INVALID_WORK_DIMENSION:
						throw InvalidWorkDimension{msg};
					case CL_INVALID_WORK_GROUP_SIZE:
						throw InvalidWorkGroupSize{msg};
					case CL_INVALID_WORK_ITEM_SIZE:
						throw InvalidWorkItemSize{msg};
					case CL_INVALID_GLOBAL_OFFSET:
						throw InvalidGlobalOffset{msg};
					case CL_INVALID_EVENT_WAIT_LIST:
						throw InvalidEventWaitList{msg};
					case CL_INVALID_EVENT:
						throw InvalidEvent{msg};
					case CL_INVALID_OPERATION:
						throw InvalidOperation{msg};
					case CL_INVALID_GL_OBJECT:
						throw InvalidGLObject{msg};
					case CL_INVALID_BUFFER_SIZE:
						throw InvalidBufferSize{msg};
					case CL_INVALID_MIP_LEVEL:
						throw InvalidMipLevel{msg};
					case CL_INVALID_GLOBAL_WORK_SIZE:
						throw InvalidGlobalWorkSize{msg};
					case CL_INVALID_PROPERTY:
						throw InvalidProperty{msg};
					case CL_INVALID_IMAGE_DESCRIPTOR:
						throw InvalidImageDescriptor{msg};
					case CL_INVALID_COMPILER_OPTIONS:
						throw InvalidCompilerOptions{msg};
					case CL_INVALID_LINKER_OPTIONS:
						throw InvalidLinkerOptions{msg};
					case CL_INVALID_DEVICE_PARTITION_COUNT:
						throw InvalidDevicePartitionCount{msg};
				}
			}
		}

		auto handleError(CLFunction const& func, RetCode2 const& code) -> bool {
			if (code.isError()) {
				impl::throwException(func, code);
			}
			return true;
		}

		auto error::isError(code_type code) -> bool {
			return code != CL_SUCCESS;
		}

		auto error::isError(RetCode code) -> bool {
			return code != RetCode::success;
		}

		auto error::isSuccess(code_type code) -> bool {
			return code == CL_SUCCESS;
		}

		auto error::isSuccess(RetCode code) -> bool {
			return code == RetCode::success;
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

				default: assert(false);
			}
		}

		auto error::handle(
			RetCode code,
			error::info_map const* local_info_map
		)
			-> bool
		{
			using namespace std::literals;
			static const auto global_info_map = info_map{
				{RetCode::outOfResources, "there was a failure to allocate resources required by the OpenCL implementation on the device."},
				{RetCode::outOfHostMemory, "there was a failure to allocate resources required by the OpenCL implementation on the host."}
			};
			if (isError(code)) {
				if (local_info_map != nullptr) {
					const auto it = local_info_map->find(code);
					const auto errorMessage =
						it != local_info_map->end() ? it->second : ""s;
					throwException(code);
					assert(false);
				}
				const auto it = global_info_map.find(code);
				const auto errorMessage =
					it != global_info_map.end() ? it->second : ""s;
				throwException(code);
				assert(false);
			}
			return true;
		}

		auto error::handle(
			error::code_type code,
			error::info_map const& local_info_map
		)
			-> bool
		{
			return handle(
				static_cast<RetCode>(code),
				std::addressof(local_info_map));
		}

		auto error::handle(error::code_type code) -> bool {
			return handle(static_cast<RetCode>(code), nullptr);
		}
	}
}

#endif
