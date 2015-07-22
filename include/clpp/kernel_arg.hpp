#if defined(CL_VERSION_1_2)

#ifndef CLPP_KERNEL_ARG_HPP
#define CLPP_KERNEL_ARG_HPP

#include "clpp/detail/common.hpp"

namespace cl {
	class Kernel;

	class KernelArg final {

		//================================================================================
		// Private constructor that can only be called from the friend class
		// 'cl::Kernel' which should be the only way to create instances of this class.
		//================================================================================
	private:

		friend class Kernel;

		KernelArg(Kernel const& kernel, cl_uint index);

		//================================================================================
		// Deleted functions in order to disable ways to create lvalue instances.
		//================================================================================
	private:

		KernelArg()                 = delete;
		KernelArg(KernelArg const&) = delete;
		KernelArg(KernelArg &&)     = delete;

		auto inline operator=(KernelArg const&) -> KernelArg& = delete;
		auto inline operator=(KernelArg &&)     -> KernelArg& = delete;

		//================================================================================
		// Information retrival functions.
		//================================================================================
	public:
		auto inline getArgAddressQualifier(cl_uint index) const -> AddressQualifier;
		auto inline getArgAccessQualifier(cl_uint index) const  -> AccessQualifier;
		auto inline getArgTypeName(cl_uint index) const         -> std::string;
		auto inline getArgTypeQualifier(cl_uint index) const    -> TypeQualifier;
		auto inline getArgName(cl_uint index) const             -> std::string;

		//================================================================================
		// Helper functions used to retrieve information.
		//================================================================================
	private:
		template<typename T>
		auto getArgInfo(
			cl_uint index, cl_kernel_arg_info info
		) const -> T;

		template<typename T>
		auto getArgInfoVector(
			cl_uint index, cl_kernel_arg_info info
		) const -> std::vector<T>;

		auto inline getArgInfoString(
			cl_uint index, cl_kernel_arg_info info
		) const -> std::string;


	private:
		Kernel const& m_kernel;
		cl_uint       m_index;
	};
}

#endif // CLPP_KERNEL_ARG_HPP
#endif // defined(CL_VERSION_1_2)
