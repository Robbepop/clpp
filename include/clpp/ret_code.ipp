#ifdef  CLPP_RET_CODE_IPP
	#error "multiple inclusions of the same implementation file"
#else
#define CLPP_RET_CODE_IPP

#ifndef CLPP_RET_CODE_HPP
	#error "header file has not been included; maybe it isn't required anymore?"
	#include "clpp/ret_code.hpp"
#endif

namespace cl {
	auto RetCode::getPreset() -> RetCode const& {
		static const auto instance = RetCode{c_presetId};
		return instance;
	}

	RetCode::RetCode(id_type id):
		m_id{id}
	{}

	RetCode::RetCode(RetCode const& other) {
		m_id = other.m_id;
	}

	auto RetCode::operator=(RetCode const& rhs) -> RetCode & {
		m_id = rhs.m_id;
		return *this;
	}

	auto RetCode::operator=(id_type const& rhs) -> RetCode & {
		m_id = rhs;
		return *this;
	}

	constexpr auto RetCode::operator==(RetCode const& rhs) -> bool {
		return m_id == rhs.m_id;
	}

	constexpr auto RetCode::operator!=(RetCode const& rhs) -> bool {
		return m_id != rhs.m_id;
	}

	auto RetCode::data() -> id_type* {
		return std::addressof(m_id);
	}

	constexpr auto RetCode::isError() const -> bool {
		return m_id != CL_SUCCESS;
	}

	constexpr auto RetCode::isSuccess() const -> bool {
		return m_id == CL_SUCCESS;
	}

	constexpr auto RetCode::getCLId() const -> id_type {
		return m_id;
	}

	//====================================================================================
	// getCLName() is coded dynamically instead of static or
	// bound to the instance in order to create the thinnest wrapper object possible.
	// With this API it is easy to implement it in the existing code base and still
	// have all the nice features with it, thus with higher function overhead
	// when calling one of these functions which should happen very seldom.
	//====================================================================================

	constexpr auto RetCode::getCLName() const -> std::experimental::string_view {
		switch (m_id) {
			default: assert(false);

			case c_presetId:
				return "c_presetId";

			case CL_SUCCESS:
				return "CL_SUCCESS";

			case CL_DEVICE_NOT_FOUND:
				return "CL_DEVICE_NOT_FOUND";
			case CL_DEVICE_NOT_AVAILABLE:
				return "CL_DEVICE_NOT_AVAILABLE";
			case CL_COMPILER_NOT_AVAILABLE:
				return "CL_COMPILER_NOT_AVAILABLE";
			case CL_MEM_OBJECT_ALLOCATION_FAILURE:
				return "CL_MEM_OBJECT_ALLOCATION_FAILURE";
			case CL_OUT_OF_RESOURCES:
				return "CL_OUT_OF_RESOURCES";
			case CL_OUT_OF_HOST_MEMORY:
				return "CL_OUT_OF_HOST_MEMORY";
			case CL_PROFILING_INFO_NOT_AVAILABLE:
				return "CL_PROFILING_INFO_NOT_AVAILABLE";
			case CL_MEM_COPY_OVERLAP:
				return "CL_MEM_COPY_OVERLAP";
			case CL_IMAGE_FORMAT_MISMATCH:
				return "CL_IMAGE_FORMAT_MISMATCH";
			case CL_IMAGE_FORMAT_NOT_SUPPORTED:
				return "CL_IMAGE_FORMAT_NOT_SUPPORTED";
			case CL_BUILD_PROGRAM_FAILURE:
				return "CL_BUILD_PROGRAM_FAILURE";
			case CL_MAP_FAILURE:
				return "CL_MAP_FAILURE";
			case CL_MISALIGNED_SUB_BUFFER_OFFSET:
				return "CL_MISALIGNED_SUB_BUFFER_OFFSET";
			case CL_EXEC_STATUS_ERROR_FOR_EVENTS_IN_WAIT_LIST:
				return "CL_EXEC_STATUS_ERROR_FOR_EVENTS_IN_WAIT_LIST";
			case CL_COMPILE_PROGRAM_FAILURE:
				return "CL_COMPILE_PROGRAM_FAILURE";
			case CL_LINKER_NOT_AVAILABLE:
				return "CL_LINKER_NOT_AVAILABLE";
			case CL_LINK_PROGRAM_FAILURE:
				return "CL_LINK_PROGRAM_FAILURE";
			case CL_DEVICE_PARTITION_FAILED:
				return "CL_DEVICE_PARTITION_FAILED";
			case CL_KERNEL_ARG_INFO_NOT_AVAILABLE:
				return "CL_KERNEL_ARG_INFO_NOT_AVAILABLE";

			case CL_INVALID_VALUE:
				return "CL_INVALID_VALUE";
			case CL_INVALID_DEVICE_TYPE:
				return "CL_INVALID_DEVICE_TYPE";
			case CL_INVALID_PLATFORM:
				return "CL_INVALID_PLATFORM";
			case CL_INVALID_DEVICE:
				return "CL_INVALID_DEVICE";
			case CL_INVALID_CONTEXT:
				return "CL_INVALID_CONTEXT";
			case CL_INVALID_QUEUE_PROPERTIES:
				return "CL_INVALID_QUEUE_PROPERTIES";
			case CL_INVALID_COMMAND_QUEUE:
				return "CL_INVALID_COMMAND_QUEUE";
			case CL_INVALID_HOST_PTR:
				return "CL_INVALID_HOST_PTR";
			case CL_INVALID_MEM_OBJECT:
				return "CL_INVALID_MEM_OBJECT";
			case CL_INVALID_IMAGE_FORMAT_DESCRIPTOR:
				return "CL_INVALID_IMAGE_FORMAT_DESCRIPTOR";
			case CL_INVALID_IMAGE_SIZE:
				return "CL_INVALID_IMAGE_SIZE";
			case CL_INVALID_SAMPLER:
				return "CL_INVALID_SAMPLER";
			case CL_INVALID_BINARY:
				return "CL_INVALID_BINARY";
			case CL_INVALID_BUILD_OPTIONS:
				return "CL_INVALID_BUILD_OPTIONS";
			case CL_INVALID_PROGRAM:
				return "CL_INVALID_PROGRAM";
			case CL_INVALID_PROGRAM_EXECUTABLE:
				return "CL_INVALID_PROGRAM_EXECUTABLE";
			case CL_INVALID_KERNEL_NAME:
				return "CL_INVALID_KERNEL_NAME";
			case CL_INVALID_KERNEL_DEFINITION:
				return "CL_INVALID_KERNEL_DEFINITION";
			case CL_INVALID_KERNEL:
				return "CL_INVALID_KERNEL";
			case CL_INVALID_ARG_INDEX:
				return "CL_INVALID_ARG_INDEX";
			case CL_INVALID_ARG_VALUE:
				return "CL_INVALID_ARG_VALUE";
			case CL_INVALID_ARG_SIZE:
				return "CL_INVALID_ARG_SIZE";
			case CL_INVALID_KERNEL_ARGS:
				return "CL_INVALID_KERNEL_ARGS";
			case CL_INVALID_WORK_DIMENSION:
				return "CL_INVALID_WORK_DIMENSION";
			case CL_INVALID_WORK_GROUP_SIZE:
				return "CL_INVALID_WORK_GROUP_SIZE";
			case CL_INVALID_WORK_ITEM_SIZE:
				return "CL_INVALID_WORK_ITEM_SIZE";
			case CL_INVALID_GLOBAL_OFFSET:
				return "CL_INVALID_GLOBAL_OFFSET";
			case CL_INVALID_EVENT_WAIT_LIST:
				return "CL_INVALID_EVENT_WAIT_LIST";
			case CL_INVALID_EVENT:
				return "CL_INVALID_EVENT";
			case CL_INVALID_OPERATION:
				return "CL_INVALID_OPERATION";
			case CL_INVALID_GL_OBJECT:
				return "CL_INVALID_GL_OBJECT";
			case CL_INVALID_BUFFER_SIZE:
				return "CL_INVALID_BUFFER_SIZE";
			case CL_INVALID_MIP_LEVEL:
				return "CL_INVALID_MIP_LEVEL";
			case CL_INVALID_GLOBAL_WORK_SIZE:
				return "CL_INVALID_GLOBAL_WORK_SIZE";
			case CL_INVALID_PROPERTY:
				return "CL_INVALID_PROPERTY";
			case CL_INVALID_IMAGE_DESCRIPTOR:
				return "CL_INVALID_IMAGE_DESCRIPTOR";
			case CL_INVALID_COMPILER_OPTIONS:
				return "CL_INVALID_COMPILER_OPTIONS";
			case CL_INVALID_LINKER_OPTIONS:
				return "CL_INVALID_LINKER_OPTIONS";
			case CL_INVALID_DEVICE_PARTITION_COUNT:
				return "CL_INVALID_DEVICE_PARTITION_COUNT";
		}
	}

	//====================================================================================
	// Operator overloads for equal and unequal comparison between RetCode
	// and its wrapped value type.
	//====================================================================================

	constexpr auto operator==(RetCode const& lhs, RetCode::id_type const& rhs) -> bool {
		return lhs.getCLId() == rhs;
	}

	constexpr auto operator!=(RetCode const& lhs, RetCode::id_type const& rhs) -> bool {
		return lhs.getCLId() != rhs;
	}

	constexpr auto operator==(RetCode::id_type const& lhs, RetCode const& rhs) -> bool {
		return rhs == lhs;
	}

	constexpr auto operator!=(RetCode::id_type const& lhs, RetCode const& rhs) -> bool {
		return rhs != lhs;
	}
}

#endif
