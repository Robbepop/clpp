#ifndef CLPP_KERNEL_H
	#error "Do not include this file directly."
#endif

#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>

namespace cl {
	auto Kernel::operator=(Kernel const& rhs) -> Kernel & {
		if (this != &rhs) {
		    detail::Object<cl_type>::operator=(rhs);
		}
		return *this;
	}

	template<typename T>
	void Kernel::setArg(cl_uint index, T&& arg) const {
		const auto error = clSetKernelArg(
			get(), index, sizeof(T), std::addressof(std::forward<T>(arg)));
		detail::error::handle(error);
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
