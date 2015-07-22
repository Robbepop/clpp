#ifdef  CLPP_KERNEL_WORK_GROUP_IPP
	#error "multiple inclusions of the same implementation file"
#else
#define CLPP_KERNEL_WORK_GROUP_IPP

#ifndef CLPP_KERNEL_WORK_GROUP_HPP
	#error "header file has not been included; maybe it isn't required anymore?"
	#include "clpp/kernel_work_group.hpp"
#endif

namespace cl {
	KernelWorkGroup::KernelWorkGroup(Kernel const& kernel, Device const& device):
		m_kernel{kernel},
		m_device{device}
	{}

#if defined(CL_VERSION_1_2)
	auto KernelWorkGroup::getGlobalWorkSize() const -> NDRange<3> {
		auto range = getInfoVector<size_t>(CL_KERNEL_GLOBAL_WORK_SIZE);
		return {range[0], range[1], range[2]};
	}
#endif // defined(CL_VERSION_1_2)

	auto KernelWorkGroup::getSize() const -> size_t {
		return getInfo<size_t>(CL_KERNEL_WORK_GROUP_SIZE);
	}

	auto KernelWorkGroup::getCompileSize() const -> NDRange<3> {
		auto range = getInfoVector<size_t>(CL_KERNEL_COMPILE_WORK_GROUP_SIZE);
		return {range[0], range[1], range[2]};
	}

	auto KernelWorkGroup::getKernelLocalMemorySize() const -> cl_ulong {
		return getInfo<cl_ulong>(CL_KERNEL_LOCAL_MEM_SIZE);
	}

	auto KernelWorkGroup::getPreferredSizeMultiple() const -> size_t {
		return getInfo<size_t>(CL_KERNEL_PREFERRED_WORK_GROUP_SIZE_MULTIPLE);
	}

	auto KernelWorkGroup::getKernelPrivateMemorySize() const -> cl_ulong {
		return getInfo<cl_ulong>(CL_KERNEL_PRIVATE_MEM_SIZE);
	}

	//================================================================================
	// Helper functions used to retrieve information.
	//================================================================================

	template<typename T>
	auto getInfo(
		cl_uint index, cl_kernel_work_group_info info
	) const -> T {
		auto error = RetCode::getPreset();
		auto info  = T{};
		error      = clGetKernelWorkGroupInfo(
			m_kernel.get(), m_device.get(), infoId, sizeof(T), std::addressof(info), nullptr);
		detail::handleError(detail::CLFunction::clGetKernelWorkGroupInfo(), error);
		return info;
	}

	template<typename T>
	auto getInfoVector(
		cl_uint index, cl_kernel_work_group_info info
	) const -> std::vector<T> {
		auto error = RetCode::getPreset();
		auto bufferSize = size_t{0};
		error = clGetKernelWorkGroupInfo(
			m_kernel.get(), m_device.get(), infoId, 0, nullptr, std::addressof(bufferSize));
		detail::handleError(detail::CLFunction::clGetKernelWorkGroupInfo(), error);
		auto countElems = bufferSize / sizeof(T);
		auto info = std::vector<T>(countElems);
		error = clGetKernelArgInfo(
			m_kernel.get(), m_device.get(), infoId, bufferSize, info.data(), nullptr);
		detail::handleError(detail::CLFunction::clGetKernelWorkGroupInfo(), error);
		return info;
	}
}

#endif // CLPP_KERNEL_WORK_GROUP_IPP
