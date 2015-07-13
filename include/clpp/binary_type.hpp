#if defined(CL_VERSION_1_2)

#ifndef CLPP_BINARY_TYPE_HPP
#define CLPP_BINARY_TYPE_HPP

#include "clpp/detail/common.hpp"

namespace cl {
	enum class BinaryType : cl_program_binary_type {
		  none           = CL_PROGRAM_BINARY_TYPE_NONE
		, compiledObject = CL_PROGRAM_BINARY_TYPE_COMPILED_OBJECT
		, library        = CL_PROGRAM_BINARY_TYPE_LIBRARY
		, executable     = CL_PROGRAM_BINARY_TYPE_EXECUTABLE
	};
}

#endif // CLPP_BINARY_TYPE_HPP
#endif // defined(CL_VERSION_1_2)
