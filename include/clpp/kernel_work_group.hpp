#ifndef CLPP_KERNEL_WORK_GROUP_HPP
#define CLPP_KERNEL_WORK_GROUP_HPP

#include "clpp/detail/common.hpp"
#include "clpp/nd_range.hpp"

namespace cl {
	class Kernel;
	class Device;

	class KernelWorkGroup final {

		//================================================================================
		// Private constructor that can only be called from the friend class
		// 'cl::Kernel' which should be the only way to create instances of this class.
		//================================================================================
	private:

		friend class Kernel;

		KernelWorkGroup(Kernel const& kernel, Device const& device);

		//================================================================================
		// Deleted functions in order to disable ways to create lvalue instances.
		//================================================================================
	private:

		KernelWorkGroup()                       = delete;
		KernelWorkGroup(KernelWorkGroup const&) = delete;
		KernelWorkGroup(KernelWorkGroup &&)     = delete;

		auto inline operator=(KernelWorkGroup const&) -> KernelWorkGroup& = delete;
		auto inline operator=(KernelWorkGroup &&)     -> KernelWorkGroup& = delete;

		//================================================================================
		// Information retrival functions.
		//================================================================================
	public:

	#if defined(CL_VERSION_1_2)
		auto inline getGlobalWorkSize() const          -> NDRange<3>;
	#endif // defined(CL_VERSION_1_2)

		auto inline getSize() const                    -> size_t;
		auto inline getCompileSize() const             -> NDRange<3>;
		auto inline getKernelLocalMemorySize() const   -> cl_ulong;
		auto inline getPreferredSizeMultiple() const   -> size_t;
		auto inline getKernelPrivateMemorySize() const -> cl_ulong;

		//================================================================================
		// Helper functions used to retrieve information.
		//================================================================================
	private:
		template<typename T>
		auto getInfo(
			cl_kernel_work_group_info info
		) const -> T;

	private:
		Kernel const& m_kernel;
		Device const& m_device;
	};
}

#endif // CLPP_KERNEL_WORK_GROUP_HPP
