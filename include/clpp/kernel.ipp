#ifdef  CLPP_KERNEL_IPP
	#error "multiple inclusions of the same implementation file"
#else
#define CLPP_KERNEL_IPP

#ifndef CLPP_KERNEL_HPP
	#error "header file has not been included; maybe it isn't required anymore?"
	#include "clpp/kernel.hpp"
#endif

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
		struct SetArgImpl final {
			static auto setArg(Kernel const& kernel, cl_uint index, V&& arg) {
				return clSetKernelArg(
					kernel.get(), index, sizeof(V), std::addressof(std::forward<V>(arg)));
			}
		};

		template<typename V>
		struct SetArgImpl<LocalMemory<V>> final {
			static auto setArg(Kernel const& kernel, cl_uint index, LocalMemory<V> const& arg) {
				return clSetKernelArg(kernel.get(), index, arg.getSizeInBytes(), nullptr);
			}
		};
	}

	template<typename T>
	void Kernel::setArg(cl_uint index, T&& arg) const {
		const auto error = detail::SetArgImpl<T>::setArg(*this, index, arg);
		detail::handleError(detail::CLFunction::clSetKernelArg(), error);
	}

	template<typename T>
	void Kernel::setArgsHelper(cl_uint index, T&& head) const {
		setArg(index, std::forward<T>(head));
	}

	template<typename T, typename... Args>
	void Kernel::setArgsHelper(cl_uint index, T&& head, Args&&... tail) const {
		setArg(index, std::forward<T>(head));
		setArgsHelper(index + 1, std::forward<Args>(tail)...);
	}

	template<typename... Args>
	void Kernel::setArgs(Args&&... tail) const {
		setArgsHelper(0, std::forward<Args>(tail)...);
	}

//	auto Kernel::getArg(cl_uint index) const -> KernelArg {
//		// TODO
//	}

//	auto Kernel::getWorkGroup(Device const& device) const -> KernelWorkGroup {
//		// TODO
//	}

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

	auto Kernel::getAttributes() const -> std::vector<std::string> {
			  auto attributes = std::vector<std::string>{};
		const auto attrStr    = getInfoString(CL_KERNEL_ATTRIBUTES);
		boost::split(attributes, attrStr, boost::is_any_of("\t "), boost::token_compress_on);
		return attributes;
	}
}

#endif
