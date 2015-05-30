#ifndef CLPP_FP_CONFIG_H
#define CLPP_FP_CONFIG_H

#include "clpp/detail/common.hpp"
#include "clpp/detail/mask_wrapper.hpp"

namespace cl {
	class FPConfig final : detail::MaskWrapper<cl_device_fp_config> {
	public:
		using detail::MaskWrapper<FPConfig::cl_mask_type>::MaskWrapper;

		auto supportsDenorm() const -> cl_bool;
		auto supportsInfAndNan() const -> cl_bool;
		auto supportsRoundToNearest() const -> cl_bool;
		auto supportsRoundToZero() const -> cl_bool;
		auto supportsRoundToInf() const -> cl_bool;
		auto supportsFusedMultiplyAdd() const -> cl_bool;
		auto supportsCorrectlyRoundedDivideSqrt() const -> cl_bool;
		auto supportsSoftFloat() const -> cl_bool;
	};
}

#include "clpp/fp_config.tpp"
#endif
