#ifndef CLPP_FP_CONFIG_H
	#error "Do not include this file directly."
#endif

namespace cl {
	auto FPConfig::supportsDenorm() const -> cl_bool {
		return readMask<CL_FP_DENORM>();
	}

	auto FPConfig::supportsInfAndNan() const -> cl_bool {
		return readMask<CL_FP_INF_NAN>();
	}

	auto FPConfig::supportsRoundToNearest() const -> cl_bool {
		return readMask<CL_FP_ROUND_TO_NEAREST>();
	}

	auto FPConfig::supportsRoundToZero() const -> cl_bool {
		return readMask<CL_FP_ROUND_TO_ZERO>();
	}

	auto FPConfig::supportsRoundToInf() const -> cl_bool {
		return readMask<CL_FP_ROUND_TO_INF>();
	}

	auto FPConfig::supportsFusedMultiplyAdd() const -> cl_bool {
		return readMask<CL_FP_FMA>();
	}

	auto FPConfig::supportsCorrectlyRoundedDivideSqrt() const -> cl_bool {
		return readMask<CL_FP_CORRECTLY_ROUNDED_DIVIDE_SQRT>();
	}

	auto FPConfig::supportsSoftFloat() const -> cl_bool {
		return readMask<CL_FP_SOFT_FLOAT>();
	}
}
