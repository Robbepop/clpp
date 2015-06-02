#ifndef CLPP_EXCEPTION_H
	#error "Do not include this file directly!"
#endif

namespace cl {
	AnyError::AnyError(
		RetCode code,
		std::string info
	):
		std::runtime_error{nullptr},
		m_code{code},
		m_info{std::move(info)}
	{}

	auto AnyError::what() const noexcept -> const char * {
		return m_info.c_str();
		//return "Hello, World!"; // test
	}

	auto AnyError::code() const {
		return m_code;
	}
}
