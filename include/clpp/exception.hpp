#ifndef CLPP_EXCEPTION_H
#define CLPP_EXCEPTION_H

#include "clpp/detail/common.hpp"

#include <stdexcept>
#include <string>

namespace cl {
	class AnyError : public std::runtime_error {
	private:
		RetCode m_code;
		std::string m_info;

	public:
		AnyError(RetCode p_code, std::string p_info);

		virtual auto what() const noexcept -> const char *;

		auto code() const;
	};

	class PlatformError     final : public AnyError { using AnyError::AnyError; };
	class DeviceError       final : public AnyError { using AnyError::AnyError; };
	class ContextError      final : public AnyError { using AnyError::AnyError; };
	class EventError        final : public AnyError { using AnyError::AnyError; };
	class PartitionError    final : public AnyError { using AnyError::AnyError; };
	class ProgramError      final : public AnyError { using AnyError::AnyError; };
	class MemObjectError    final : public AnyError { using AnyError::AnyError; };
	class KernelError       final : public AnyError { using AnyError::AnyError; };
	class CommandQueueError final : public AnyError { using AnyError::AnyError; };
}

#include "clpp/exception.tpp"
#endif
