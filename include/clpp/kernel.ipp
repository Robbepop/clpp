#ifdef  CLPP_KERNEL_IPP
	#error "multiple inclusions of the same implementation file"
#else
#define CLPP_KERNEL_IPP

#ifndef CLPP_KERNEL_HPP
	#error "header file has not been included; maybe it isn't required anymore?"
	#include "clpp/kernel.hpp"
#endif

#include <type_traits>

#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>

#include "clpp/local_memory.hpp"

namespace cl {
	auto Kernel::operator=(Kernel const& rhs) -> Kernel & {
		if (this != &rhs) {
		    detail::Object<cl_type>::operator=(rhs);
		}
		return *this;
	}

	namespace detail {

		template<typename V>
		auto setArg(Kernel const& kernel, cl_uint index, const V& arg) {
			return clSetKernelArg(
				kernel.get(), index, sizeof(V), std::addressof(arg));
		}
	

		template<typename V>
		auto setArg(Kernel const& kernel, cl_uint index, LocalMemory<V> const& arg) {
			return clSetKernelArg(kernel.get(), index, arg.getSizeInBytes(), NULL);
		}
	}

	template<typename T>
	void Kernel::setArg(cl_uint index, T const& arg) const {
		const auto error = detail::setArg(*this, index, arg);
		detail::handleError(detail::CLFunction::clSetKernelArg(), error);
	}

	template<cl_uint...Indeces, typename... Args>
	void Kernel::setArgsHelper(std::integer_sequence<cl_uint, Indeces...>, Args const&... args) const {
		const auto call_all = [](std::initializer_list<int>){};
		call_all({(setArg(Indeces, args),0)...});
	}

	template<typename... Args>
	void Kernel::setArgs(Args const&... args) const {
		setArgsHelper(std::make_integer_sequence<cl_uint, sizeof...(args)>{}, args...);
	}

	//================================================================================
	// Used to retrieve information about kernel arguments.
	//================================================================================
#if defined(CL_VERSION_1_2)
	auto Kernel::getArg(cl_uint index) const -> KernelArg {
		return {*this, index};
	}
#endif // defined(CL_VERSION_1_2)

	//================================================================================
	// Used to retrieve information about kernel work groups.
	//================================================================================

	auto Kernel::getWorkGroup(Device const& device) const -> KernelWorkGroup {
		return {*this, device};
	}

	//================================================================================
	// Information access profiling helper methods.
	//================================================================================

	auto Kernel::getFunctionName() const -> std::string {
		return getInfoString(CL_KERNEL_FUNCTION_NAME);
	}

	auto Kernel::getNumArgs() const -> cl_uint {
		return getInfo<cl_uint>(CL_KERNEL_NUM_ARGS);
	}

	auto Kernel::getReferenceCount() const -> cl_uint {
		return getInfo<cl_uint>(CL_KERNEL_REFERENCE_COUNT);
	}

	auto Kernel::getContext() const -> std::unique_ptr<Context> {
		return std::make_unique<Context>(
			getInfo<cl_context>(CL_KERNEL_CONTEXT));
	}

	auto Kernel::getProgram() const -> std::unique_ptr<Program> {
		return std::make_unique<Program>(
			getInfo<cl_program>(CL_KERNEL_PROGRAM));
	}

#if defined(CL_VERSION_1_2)
	auto Kernel::getAttributes() const -> std::vector<std::string> {
			  auto attributes = std::vector<std::string>{};
		const auto attrStr    = getInfoString(CL_KERNEL_ATTRIBUTES);
		boost::split(attributes, attrStr, boost::is_any_of("\t "), boost::token_compress_on);
		return attributes;
	}
#endif // defined(CL_VERSION_1_2)
}

#endif
