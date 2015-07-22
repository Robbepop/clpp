#if defined(CL_VERSION_1_2)

#ifdef  CLPP_KERNEL_ARG_IPP
	#error "multiple inclusions of the same implementation file"
#else
#define CLPP_KERNEL_ARG_IPP

#ifndef CLPP_KERNEL_ARG_HPP
	#error "header file has not been included; maybe it isn't required anymore?"
	#include "clpp/kernel_arg.hpp"
#endif

#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>

namespace cl {
	//================================================================================
	// Helper methods for information retrival.
	//================================================================================

	template<typename T>
	auto Kernel::getInfo(
		cl_uint index, cl_kernel_arg_info infoId
	) const -> T {
		auto error = RetCode::getPreset();
		auto info  = T{};
		error      = clGetKernelArgInfo(
			get(), index, infoId, sizeof(T), std::addressof(info), nullptr);
		detail::handleError(detail::CLFunction::clGetKernelArgInfo(), error);
		return info;
	}

	template<typename T>
	auto Kernel::getInfoVector(
		cl_uint index, cl_kernel_arg_info infoId
	) const -> std::vector<T> {
		auto error = RetCode::getPreset();
		auto bufferSize = size_t{0};
		error = clGetKernelArgInfo(
			get(), index, infoId, 0, nullptr, std::addressof(bufferSize));
		detail::handleError(detail::CLFunction::clGetKernelArgInfo(), error);
		auto countElems = bufferSize / sizeof(T);
		auto info = std::vector<T>(countElems);
		error = clGetKernelArgInfo(
			get(), index, infoId, bufferSize, info.data(), nullptr);
		detail::handleError(detail::CLFunction::clGetKernelArgInfo(), error);
		return info;
	}

	auto inline Kernel::getInfoString(
		cl_uint index, cl_kernel_arg_info infoId
	) const -> std::string {
		const auto info = getArgInfoVector<char>(index, infoId);
		return {info.begin(), info.end()};
	}

	//================================================================================
	// Actual information retrival methods.
	//================================================================================

	auto Kernel::getArgAddressQualifier(cl_uint index) const -> AddressQualifier {
		return static_cast<AddressQualifier>(getInfo<cl_kernel_arg_address_qualifier>(
			index, CL_KERNEL_ARG_ADDRESS_QUALIFIER));
	}

	auto Kernel::getArgAccessQualifier(cl_uint index) const -> AccessQualifier {
		return static_cast<AccessQualifier>(getInfo<cl_kernel_arg_access_qualifier>(
			index, CL_KERNEL_ARG_ACCESS_QUALIFIER));
	}

	auto Kernel::getArgTypeName(cl_uint index) const -> std::string {
		return getInfoString(index, CL_KERNEL_ARG_TYPE_NAME);
	}

	auto Kernel::getArgTypeQualifier(cl_uint index) const -> TypeQualifier {
		return {getInfo<cl_kernel_arg_type_qualifier>(
			index, CL_KERNEL_ARG_TYPE_QUALIFIER)};
	}

	auto Kernel::getArgName(cl_uint index) const -> std::string {
		return getInfoString(index, CL_KERNEL_ARG_NAME);
	}
}

#endif // CLPP_KERNEL_ARG_IPP
#endif // defined(CL_VERSION_1_2)
