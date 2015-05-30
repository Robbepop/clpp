#ifndef CLPP_EXCEPTION_H
	#error "Do not include this file directly!"
#endif

namespace cl {
	AnyError::AnyError(
		ErrorCode code,
		std::string info
	):
		m_code{code},
		m_info{std::move(info)}
	{}

	AnyError::AnyError(
		ErrorCode code,
		std::experimental::string_view info
	):
		m_code{code},
		m_info{info.begin(), info.end()}
	{}

	virtual auto AnyError::what() const noexcept {
		return m_info.c_str();
	}

	auto AnyError::code() const {
		return m_code;
	}
}
