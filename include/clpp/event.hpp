#ifndef CLPP_EVENT_HPP
#define CLPP_EVENT_HPP

#include "clpp/execution_status.hpp"
#include "clpp/command.hpp"

namespace cl {
	namespace detail {
		template<>
		struct ObjectHandler<cl_event> final {
			using cl_type        = cl_event;
			using info_type      = cl_event_info;

			static auto release(cl_type id) { return clReleaseEvent(id); }

			static auto retain(cl_type id) { return clRetainEvent(id); }

			static auto getInfo(
				cl_type   event,
				info_type param_name,
				size_t    param_value_size,
				void *    param_value,
				size_t *  param_value_size_ret
			) {
				return clGetEventInfo(
					event, param_name, param_value_size, param_value, param_value_size_ret);
			}
		};
	}

	class Event final : public detail::Object<cl_event> {
		//================================================================================
		// Wrapper API for clWaitForEvents
		//================================================================================

		template<typename EventRange>
		static void wait(EventRange const& waitList);

		template<typename... Events>
		static void wait(Events...);

		void wait() const;

		//================================================================================
		// Constructor and Assignment
		//================================================================================
	public:

		using detail::Object<cl_type>::Object;

		auto operator=(const Event & rhs) -> Event &;

		//================================================================================
		// Wrapper API for clSetUserEventStatus
		//================================================================================

		void setStatus(cl_int status) const;
		void setStatusComplete() const;
		void setStatusError() const;

		//================================================================================
		// Wrapper API for clEventSetCallback
		//================================================================================
	public:

		template<typename Function, typename T>
		auto setCallback(ExecutionStatus status, Function callback, T&& data) const;

		//================================================================================
		// Information access helper methods.
		//================================================================================
	public:

		auto getCommandQueue() const   -> boost::optional<CommandQueue>;
		auto getContext() const        -> Context;
		auto getCommand() const        -> Command;
		auto getStatus() const         -> ExecutionStatus;
		auto getReferenceCount() const -> cl_uint;

		//================================================================================
		// Information access profiling helper methods.
		//================================================================================
	public:

		auto getProfilingQueued() const   -> cl_ulong;
		auto getProfilingSubmit() const   -> cl_ulong;
		auto getProfilingStart() const    -> cl_ulong;
		auto getProfilingEnd() const      -> cl_ulong;
		auto getProfilingComplete() const -> cl_ulong;
	};
}

#endif
