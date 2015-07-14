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
						throw DeviceNotFound{func, msg};
					case CL_DEVICE_NOT_AVAILABLE:
						throw DeviceNotAvailable{func, msg};
					case CL_COMPILER_NOT_AVAILABLE:
						throw CompilerNotAvailable{func, msg};
					case CL_MEM_OBJECT_ALLOCATION_FAILURE:
						throw MemoryObjectAllocFailure{func, msg};
					case CL_OUT_OF_RESOURCES:
						throw OutOfResources{func, msg};
					case CL_OUT_OF_HOST_MEMORY:
						throw OutOfHostMemory{func, msg};
					case CL_PROFILING_INFO_NOT_AVAILABLE:
						throw ProfilingInfoNotAvailable{func, msg};
					case CL_MEM_COPY_OVERLAP:
						throw MemoryCopyOverlap{func, msg};
					case CL_IMAGE_FORMAT_MISMATCH:
						throw ImageFormatMismatch{func, msg};
					case CL_IMAGE_FORMAT_NOT_SUPPORTED:
						throw ImageFormatNotSupported{func, msg};
					case CL_BUILD_PROGRAM_FAILURE:
						throw BuildProgramFailure{func, msg};
					case CL_MAP_FAILURE:
						throw MapFailure{func, msg};
					case CL_MISALIGNED_SUB_BUFFER_OFFSET:
						throw MisalignedSubBufferOffset{func, msg};
					case CL_EXEC_STATUS_ERROR_FOR_EVENTS_IN_WAIT_LIST:
						throw ExecStatusErrorForEventsInWaitList{func, msg};
				#if defined(CL_VERSION_1_2)
					case CL_COMPILE_PROGRAM_FAILURE:
						throw CompileProgramFailure{func, msg};
					case CL_LINKER_NOT_AVAILABLE:
						throw LinkerNotAvailable{func, msg};
					case CL_LINK_PROGRAM_FAILURE:
						throw LinkProgramFailure{func, msg};
					case CL_DEVICE_PARTITION_FAILED:
						throw DevicePartitionFailure{func, msg};
					case CL_KERNEL_ARG_INFO_NOT_AVAILABLE:
						throw KernelArgInfoNotAvailable{func, msg};
				#endif // defined(CL_VERSION_1_2)

					case CL_INVALID_VALUE:
						throw InvalidValue{func, msg};
					case CL_INVALID_DEVICE_TYPE:
						throw InvalidDeviceType{func, msg};
					case CL_INVALID_PLATFORM:
						throw InvalidPlatform{func, msg};
					case CL_INVALID_DEVICE:
						throw InvalidDevice{func, msg};
					case CL_INVALID_CONTEXT:
						throw InvalidContext{func, msg};
					case CL_INVALID_QUEUE_PROPERTIES:
						throw InvalidQueueProperties{func, msg};
					case CL_INVALID_COMMAND_QUEUE:
						throw InvalidCommandQueue{func, msg};
					case CL_INVALID_HOST_PTR:
						throw InvalidHostPtr{func, msg};
					case CL_INVALID_MEM_OBJECT:
						throw InvalidMemoryObject{func, msg};
					case CL_INVALID_IMAGE_FORMAT_DESCRIPTOR:
						throw InvalidImageFormatDescriptor{func, msg};
					case CL_INVALID_IMAGE_SIZE:
						throw InvalidImageSize{func, msg};
					case CL_INVALID_SAMPLER:
						throw InvalidSampler{func, msg};
					case CL_INVALID_BINARY:
						throw InvalidBinary{func, msg};
					case CL_INVALID_BUILD_OPTIONS:
						throw InvalidBuildOptions{func, msg};
					case CL_INVALID_PROGRAM:
						throw InvalidProgram{func, msg};
					case CL_INVALID_PROGRAM_EXECUTABLE:
						throw InvalidProgramExecutable{func, msg};
					case CL_INVALID_KERNEL_NAME:
						throw InvalidKernelName{func, msg};
					case CL_INVALID_KERNEL_DEFINITION:
						throw InvalidKernelDefinition{func, msg};
					case CL_INVALID_KERNEL:
						throw InvalidKernel{func, msg};
					case CL_INVALID_ARG_INDEX:
						throw InvalidArgIndex{func, msg};
					case CL_INVALID_ARG_VALUE:
						throw InvalidArgValue{func, msg};
					case CL_INVALID_ARG_SIZE:
						throw InvalidArgSize{func, msg};
					case CL_INVALID_KERNEL_ARGS:
						throw InvalidKernelArgs{func, msg};
					case CL_INVALID_WORK_DIMENSION:
						throw InvalidWorkDimension{func, msg};
					case CL_INVALID_WORK_GROUP_SIZE:
						throw InvalidWorkGroupSize{func, msg};
					case CL_INVALID_WORK_ITEM_SIZE:
						throw InvalidWorkItemSize{func, msg};
					case CL_INVALID_GLOBAL_OFFSET:
						throw InvalidGlobalOffset{func, msg};
					case CL_INVALID_EVENT_WAIT_LIST:
						throw InvalidEventWaitList{func, msg};
					case CL_INVALID_EVENT:
						throw InvalidEvent{func, msg};
					case CL_INVALID_OPERATION:
						throw InvalidOperation{func, msg};
					case CL_INVALID_GL_OBJECT:
						throw InvalidGLObject{func, msg};
					case CL_INVALID_BUFFER_SIZE:
						throw InvalidBufferSize{func, msg};
					case CL_INVALID_MIP_LEVEL:
						throw InvalidMipLevel{func, msg};
					case CL_INVALID_GLOBAL_WORK_SIZE:
						throw InvalidGlobalWorkSize{func, msg};
					case CL_INVALID_PROPERTY:
						throw InvalidProperty{func, msg};
				#if defined(CL_VERSION_1_2)
					case CL_INVALID_IMAGE_DESCRIPTOR:
						throw InvalidImageDescriptor{func, msg};
					case CL_INVALID_COMPILER_OPTIONS:
						throw InvalidCompilerOptions{func, msg};
					case CL_INVALID_LINKER_OPTIONS:
						throw InvalidLinkerOptions{func, msg};
					case CL_INVALID_DEVICE_PARTITION_COUNT:
						throw InvalidDevicePartitionCount{func, msg};
				#endif // defined(CL_VERSION_1_2)
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
