#if defined(CL_VERSION_2_0)

#ifdef  CLPP_TYPE_QUALIFIER_IPP
	#error "multiple inclusions of the same implementation file"
#else
#define CLPP_TYPE_QUALIFIER_IPP

#ifndef CLPP_TYPE_QUALIFIER_HPP
	#error "header file has not been included; maybe it isn't required anymore?"
	#include "clpp/type_qualifier.hpp"
#endif

namespace cl {
	auto TypeQualifier::isConst() const -> bool {
		return readMask<CL_KERNEL_ARG_TYPE_CONST>();
	}

	auto TypeQualifier::isRestrict() const -> bool {
		return readMask<CL_KERNEL_ARG_TYPE_RESTRICT>();
	}

	auto TypeQualifier::isVolatile() const -> bool {
		return readMask<CL_KERNEL_ARG_TYPE_VOLATILE>();
	}

	auto TypeQualifier::isPipe() const -> bool {
		return readMask<CL_KERNEL_ARG_TYPE_PIPE>();
	}
}

#endif // CLPP_TYPE_QUALIFIER_IPP
#endif // defined(CL_VERSION_2_0)
