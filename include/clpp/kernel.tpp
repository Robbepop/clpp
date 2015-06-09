#ifndef CLPP_KERNEL_H
	#error "Do not include this file directly."
#endif

namespace cl {
	auto Kernel::operator=(Kernel const& rhs) -> Kernel& {
		// TODO
	}

	template<typename T>
	void Kernel::setArg(cl_uint index, T&& arg) const {
		// TODO
	}

	template<typename T, typename... Args>
	void Kernel::setArgs(T&& head, Args&&... tail) const {
		// TODO
	}

	auto Kernel::getArg(cl_uint index) const -> KernelArg {
		// TODO
	}

	auto Kernel::getWorkGroup(Device const& device) const -> KernelWorkGroup {
		// TODO
	}

	auto Kernel::getFunctionName() const -> std::string {
		// TODO
	}

	auto Kernel::getNumArgs() const -> cl_uint {
		// TODO
	}

	auto Kernel::getReferenceCount() const -> cl_uint {
		// TODO
	}

	auto Kernel::getContext() const -> Context {
		// TODO
	}

	auto Kernel::getProgram() const -> Program {
		// TODO
	}

	auto Kernel::getAttributes() const -> std::vector<std::string>> {
		// TODO
	}
}
