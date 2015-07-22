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
	auto KernelArg::getInfo(
		cl_kernel_arg_info infoId
	) const -> T {
		auto error = RetCode::getPreset();
		auto info  = T{};
		error      = clGetKernelArgInfo(
			m_kernel.get(), m_index, infoId, sizeof(T), std::addressof(info), nullptr);
		detail::handleError(detail::CLFunction::clGetKernelArgInfo(), error);
		return info;
	}

	template<typename T>
	auto KernelArg::getInfoVector(
		cl_kernel_arg_info infoId
	) const -> std::vector<T> {
		auto error = RetCode::getPreset();
		auto bufferSize = size_t{0};
		error = clGetKernelArgInfo(
			m_kernel.get(), m_index, infoId, 0, nullptr, std::addressof(bufferSize));
		detail::handleError(detail::CLFunction::clGetKernelArgInfo(), error);
		auto countElems = bufferSize / sizeof(T);
		auto info = std::vector<T>(countElems);
		error = clGetKernelArgInfo(
			m_kernel.get(), m_index, infoId, bufferSize, info.data(), nullptr);
		detail::handleError(detail::CLFunction::clGetKernelArgInfo(), error);
		return info;
	}

	auto inline KernelArg::getInfoString(
		cl_kernel_arg_info infoId
	) const -> std::string {
		const auto info = getInfoVector<char>(infoId);
		return {info.begin(), info.end()};
	}

	//================================================================================
	// Actual information retrival methods.
	//================================================================================

	auto KernelArg::getAddressQualifier() const -> AddressQualifier {
		return static_cast<AddressQualifier>(getInfo<cl_kernel_arg_address_qualifier>(
			CL_KERNEL_ARG_ADDRESS_QUALIFIER));
	}

	auto KernelArg::getAccessQualifier() const -> AccessQualifier {
		return static_cast<AccessQualifier>(getInfo<cl_kernel_arg_access_qualifier>(
			CL_KERNEL_ARG_ACCESS_QUALIFIER));
	}

	auto KernelArg::getTypeName() const -> std::string {
		return getInfoString(CL_KERNEL_ARG_TYPE_NAME);
	}

	auto KernelArg::getTypeQualifier() const -> TypeQualifier {
		return {getInfo<cl_kernel_arg_type_qualifier>(
			CL_KERNEL_ARG_TYPE_QUALIFIER)};
	}

	auto KernelArg::getName() const -> std::string {
		return getInfoString(CL_KERNEL_ARG_NAME);
	}
}

#endif // CLPP_KERNEL_ARG_IPP
#endif // defined(CL_VERSION_1_2)
