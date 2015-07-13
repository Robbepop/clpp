#if defined(CL_VERSION_2_0)

#ifndef CLPP_TYPE_QUALIFIER_HPP
#define CLPP_TYPE_QUALIFIER_HPP

#include "clpp/detail/common.hpp"
#include "clpp/detail/mask_wrapper.hpp"

namespace cl {
	class TypeQualifier final : detail::MaskWrapper<cl_kernel_arg_type_qualifier> {
	public:
		using detail::MaskWrapper<TypeQualifier::cl_mask_type>::MaskWrapper;

		auto inline isConst()    const -> bool;
		auto inline isRestrict() const -> bool;
		auto inline isVolatile() const -> bool;
		auto inline isPipe()     const -> bool;
	};
}

#endif // CLPP_TYPE_QUALIFIER_HPP
#endif // defined(CL_VERSION_2_0)
