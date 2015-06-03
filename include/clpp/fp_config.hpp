#ifndef CLPP_FP_CONFIG_H
#define CLPP_FP_CONFIG_H

#include "clpp/detail/common.hpp"
#include "clpp/detail/mask_wrapper.hpp"

namespace cl {
	class FPConfig final : detail::MaskWrapper<cl_device_fp_config> {
	public:
		using detail::MaskWrapper<FPConfig::cl_mask_type>::MaskWrapper;

		auto supportsDenorm() const                     -> bool;
		auto supportsInfAndNan() const                  -> bool;
		auto supportsRoundToNearest() const             -> bool;
		auto supportsRoundToZero() const                -> bool;
		auto supportsRoundToInf() const                 -> bool;
		auto supportsFusedMultiplyAdd() const           -> bool;
		auto supportsCorrectlyRoundedDivideSqrt() const -> bool;
		auto supportsSoftFloat() const                  -> bool;
	};
}

#include "clpp/fp_config.tpp"
#endif
