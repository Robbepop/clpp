#ifndef CLPP_KERNEL_H
#define CLPP_KERNEL_H

#include "clpp/detail/object.hpp"

namespace cl {
	namespace detail {
		template<>
		struct ObjectHandler<cl_kernel> {
			using cl_type        = cl_kernel;
			using info_type      = cl_kernel_info;

			static auto release(cl_type id) { clReleaseKernel(id); }

			static auto retain(cl_type id) { clRetainKernel(id); }

			static auto getInfo(
				cl_type   kernel,
				info_type param_name,
				size_t    param_value_size,
				void *    param_value,
				size_t *  param_value_size_ret
			) {
				return clGetKernelInfo(
					kernel, param_name, param_value_size, param_value, param_value_size_ret);
			}
		};
	}

	class Context;
	class Program;

	class Kernel final : public detail::Object<cl_kernel> {
	public:
		//================================================================================
		// Constructor and Assignment
		//================================================================================
	public:

		using detail::Object<cl_type>::Object;

		auto operator=(Kernel const& rhs) -> Kernel&;

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
		// Used to retrieve information about kernel arguments and kernel work groups.
		//================================================================================
	public:

//		auto getArg(cl_uint index) const              -> KernelArg;
//		auto getWorkGroup(Device const& device) const -> KernelWorkGroup;

		//================================================================================
		// Information access profiling helper methods.
		//================================================================================
	public:

		auto getFunctionName() const   -> std::string;
		auto getNumArgs() const        -> cl_uint;
		auto getReferenceCount() const -> cl_uint;
		auto getContext() const        -> std::unique_ptr<Context>;
		auto getProgram() const        -> std::unique_ptr<Program>;
		auto getAttributes() const     -> std::vector<std::string>;
	};
}

#include "clpp/kernel.tpp"
#endif
