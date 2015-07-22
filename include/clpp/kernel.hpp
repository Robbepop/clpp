#ifndef CLPP_KERNEL_HPP
#define CLPP_KERNEL_HPP

#include "clpp/detail/object.hpp"
#include "clpp/address_qualifier.hpp"
#include "clpp/access_qualifier.hpp"
#include "clpp/type_qualifier.hpp"

#include "clpp/kernel_arg.hpp"
#include "clpp/kernel_work_group.hpp"

namespace cl {
	namespace detail {
		template<>
		struct ObjectHandler<cl_kernel> final {
			using cl_type        = cl_kernel;
			using info_type      = cl_kernel_info;

			static constexpr auto retain  = clRetainKernel;
			static constexpr auto release = clReleaseKernel;
			static constexpr auto getInfo = clGetKernelInfo;
		};
	}

	class Context;
	class Program;
	template<typename T> class LocalMemory;

	class Kernel final : public detail::Object<cl_kernel> {
	public:
		//================================================================================
		// Constructor and Assignment
		//================================================================================
	public:

		using detail::Object<cl_type>::Object;

		auto inline operator=(Kernel const& rhs) -> Kernel &;

		//================================================================================
		// Used to set kernel arguments for the next kernel execution.
		//================================================================================
	public:

		template<typename T>
		void setArg(cl_uint index, T&& arg) const;

	private:
		template<typename T>
		void setArgsHelper(cl_uint index, T&& head) const;

		template<typename T, typename... Args>
		void setArgsHelper(cl_uint index, T&& head, Args&&... tail) const;

	public:
		template<typename... Args>
		void setArgs(Args&&... tail) const;

		//================================================================================
		// Used to retrieve information about kernel arguments.
		//================================================================================
	#if defined(CL_VERSION_1_2)
	public:
		auto inline getArg(cl_uint index) const -> KernelArg;
	#endif // defined(CL_VERSION_1_2)

		//================================================================================
		// Used to retrieve information about kernel work groups.
		//================================================================================
	public:
		auto inline getWorkGroup(Device const& device) const -> KernelWorkGroup;

		//================================================================================
		// Information access profiling helper methods.
		//================================================================================
	public:

		auto inline getFunctionName() const   -> std::string;
		auto inline getNumArgs() const        -> cl_uint;
		auto inline getReferenceCount() const -> cl_uint;
		auto inline getContext() const        -> std::unique_ptr<Context>;
		auto inline getProgram() const        -> std::unique_ptr<Program>;
	#if defined(CL_VERSION_1_2)
		auto inline getAttributes() const     -> std::vector<std::string>;
	#endif // defined(CL_VERSION_1_2)
	};
}

#endif
