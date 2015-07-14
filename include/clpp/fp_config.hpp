#ifndef CLPP_FP_CONFIG_HPP
#define CLPP_FP_CONFIG_HPP

#include "clpp/detail/common.hpp"
#include "clpp/detail/mask_wrapper.hpp"

namespace cl {
	class FPConfig final : detail::MaskWrapper<cl_device_fp_config> {
	public:
		using detail::MaskWrapper<FPConfig::cl_mask_type>::MaskWrapper;

		auto inline supportsDenorm() const                     -> bool;
		auto inline supportsInfAndNan() const                  -> bool;
		auto inline supportsRoundToNearest() const             -> bool;
		auto inline supportsRoundToZero() const                -> bool;
		auto inline supportsRoundToInf() const                 -> bool;
		auto inline supportsFusedMultiplyAdd() const           -> bool;
	#if defined(CL_VERSION_1_2)
		auto inline supportsCorrectlyRoundedDivideSqrt() const -> bool;
	#endif // defined(CL_VERSION_1_2)
		auto inline supportsSoftFloat() const                  -> bool;
	};
}

#endif
