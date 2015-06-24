#ifdef  CLPP_EVENT_IPP
	#error "multiple inclusions of the same implementation file"
#else
#define CLPP_EVENT_IPP

#ifndef CLPP_EVENT_HPP
	#error "header file has not been included; maybe it isn't required anymore?"
	#include "clpp/event.hpp"
#endif

#include "utility/to_underlying.hpp"

#include <memory>

namespace cl {
	template<typename EventRange>
	void Event::wait(EventRange const& waitList) {
		auto error = clWaitForEvents(
			waitList.size(),
			reinterpret_cast<const cl_type*>(waitList.data()));
		detail::error::handle(error);
	}

	template<typename... Events>
	void Event::wait(Events&&... events) {
		wait(utility::make_array<Event>(events...));
	}

	void Event::wait() const {
		detail::error::handle(
			clWaitForEvents(1, reinterpret_cast<const cl_type*>(this)));
	}

	auto Event::operator=(const Event & rhs) -> Event & {
        if (this != &rhs) {
            detail::Object<cl_type>::operator=(rhs);
        }
        return *this;
	}

	void Event::setStatus(cl_int status) const {
		auto error = clSetUserEventStatus(get(), status);
		detail::error::handle(error);
	}

	void Event::setStatusComplete() const {
		setStatus(CL_COMPLETE);
	}

	void Event::setStatusError() const {
		setStatus(-1);
	}

	template<typename Function, typename T>
	auto Event::setCallback(ExecutionStatus status, Function callback, T&& data) const {
		struct CallbackWrapper {
			Function callback;
			T&& data;
		};
		auto cbw   = new CallbackWrapper{callback, std::forward(data)};
		auto error = cl_int{CL_INVALID_VALUE};
		error = clSetEventCallback(
			get(), utility::to_underlying(status),
			[](cl_event event, cl_int event_command_exec_status, void* user_data) {
				auto cbw    = reinterpret_cast<CallbackWrapper*>(user_data);
				auto status = static_cast<ExecutionStatus>(event_command_exec_status);
				cbw->callback({event}, status, cbw->data);
				delete cbw;
			},
			std::addressof(cbw)
		);
	}

	auto Event::getCommandQueue() const -> boost::optional<CommandQueue> {
		const auto queueId = getInfo<cl_command_queue>(CL_EVENT_COMMAND_QUEUE);
		if (queueId == nullptr) {
			return {};
		}
		return {{queueId}};
	}

	auto Event::getContext() const -> Context {
		return {getInfo<cl_context>(CL_EVENT_CONTEXT)};
	}

	auto Event::getCommand() const -> Command {
		using command_t = std::underlying_type<Command>::type;
		return static_cast<Command>(getInfo<command_t>(CL_EVENT_COMMAND_TYPE));
	}

	auto Event::getStatus() const -> ExecutionStatus {
		using exec_status_t = std::underlying_type<ExecutionStatus>::type;
		auto state = getInfo<exec_status_t>(CL_EVENT_COMMAND_EXECUTION_STATUS);
		return static_cast<ExecutionStatus>(state);
	}

	auto Event::getReferenceCount() const -> cl_uint {
		return getInfo<cl_uint>(CL_EVENT_REFERENCE_COUNT);
	}

	auto Event::getProfilingQueued() const -> cl_ulong {
		return getInfo<cl_ulong>(CL_PROFILING_COMMAND_QUEUED);
	}

	auto Event::getProfilingSubmit() const -> cl_ulong {
		return getInfo<cl_ulong>(CL_PROFILING_COMMAND_SUBMIT);
	}

	auto Event::getProfilingStart() const -> cl_ulong {
		return getInfo<cl_ulong>(CL_PROFILING_COMMAND_START);
	}

	auto Event::getProfilingEnd() const -> cl_ulong {
		return getInfo<cl_ulong>(CL_PROFILING_COMMAND_END);
	}

	auto Event::getProfilingComplete() const -> cl_ulong {
		return getInfo<cl_ulong>(CL_PROFILING_COMMAND_COMPLETE);
	}
}

#endif
