#ifndef CLPP_ADDRESS_QUALIFIER_HPP
#define CLPP_ADDRESS_QUALIFIER_HPP

#include "clpp/detail/common.hpp"

namespace cl {
	enum class AddressQualifier : cl_kernel_arg_address_qualifier {
		  global   = CL_KERNEL_ARG_ADDRESS_GLOBAL
		, local    = CL_KERNEL_ARG_ADDRESS_LOCAL
		, constant = CL_KERNEL_ARG_ADDRESS_CONSTANT
		, none     = CL_KERNEL_ARG_ADDRESS_PRIVATE // none is better name since 'private' is a C++ keyword
	};
}

#endif // CLPP_ADDRESS_QUALIFIER_HPP
