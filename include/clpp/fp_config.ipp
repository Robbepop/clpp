#ifdef  CLPP_FP_CONFIG_IPP
	#error "multiple inclusions of the same implementation file"
#else
#define CLPP_FP_CONFIG_IPP

#ifndef CLPP_FP_CONFIG_HPP
	#error "header file has not been included; maybe it isn't required anymore?"
	#include "clpp/fp_config.hpp"
#endif

namespace cl {
	auto FPConfig::supportsDenorm() const -> bool {
		return readMask<CL_FP_DENORM>();
	}

	auto FPConfig::supportsInfAndNan() const -> bool {
		return readMask<CL_FP_INF_NAN>();
	}

	auto FPConfig::supportsRoundToNearest() const -> bool {
		return readMask<CL_FP_ROUND_TO_NEAREST>();
	}

	auto FPConfig::supportsRoundToZero() const -> bool {
		return readMask<CL_FP_ROUND_TO_ZERO>();
	}

	auto FPConfig::supportsRoundToInf() const -> bool {
		return readMask<CL_FP_ROUND_TO_INF>();
	}

	auto FPConfig::supportsFusedMultiplyAdd() const -> bool {
		return readMask<CL_FP_FMA>();
	}

#if defined(CL_VERSION_1_2)
	auto FPConfig::supportsCorrectlyRoundedDivideSqrt() const -> bool {
		return readMask<CL_FP_CORRECTLY_ROUNDED_DIVIDE_SQRT>();
	}
#endif // defined(CL_VERSION_1_2)

	auto FPConfig::supportsSoftFloat() const -> bool {
		return readMask<CL_FP_SOFT_FLOAT>();
	}
}

#endif
