#ifndef CLPP_FP_CONFIG_H
	#error "Do not include this file directly."
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

	auto FPConfig::supportsCorrectlyRoundedDivideSqrt() const -> bool {
		return readMask<CL_FP_CORRECTLY_ROUNDED_DIVIDE_SQRT>();
	}

	auto FPConfig::supportsSoftFloat() const -> bool {
		return readMask<CL_FP_SOFT_FLOAT>();
	}
}
