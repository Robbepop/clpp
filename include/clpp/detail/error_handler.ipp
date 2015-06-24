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
			void throwException(CLFunction const& func, RetCode const& code) {
				using namespace ::cl::error;
				const auto msg = std::string{code.getCLName().to_string()}
					+ " (" + std::to_string(code.getCLId()) + ") thrown by "
					+ func.getCLName().to_string();

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

		template<typename CLFunctionPtr>
		auto handleError(CLFunctionPtr funcPtr, RetCode const& code) -> bool {
			if (code.isError()) {
				impl::throwException(CLFunction::getByPtr(funcPtr), code);
			}
			return true;
		}

		auto handleError(
			CLFunction const& func, RetCode const& code
		) -> bool {
			if (code.isError()) {
				impl::throwException(func, code);
			}
			return true;
		}

		auto handleError(RetCode const& code) -> bool {
			return handleError(CLFunction::unknown, code);
		}
	}
}

#endif
