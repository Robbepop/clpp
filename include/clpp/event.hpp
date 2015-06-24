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

			static constexpr auto retain  = clRetainEvent;
			static constexpr auto release = clReleaseEvent;
			static constexpr auto getInfo = clGetEventInfo;
		};
	}

	class Event final : public detail::Object<cl_event> {
		//================================================================================
		// Wrapper API for clWaitForEvents
		//================================================================================

		template<typename EventRange>
		static void wait(EventRange const& waitList);

		template<typename... Events>
		static void wait(Events&&...);

		void inline wait() const;

		//================================================================================
		// Constructor and Assignment
		//================================================================================
	public:

		using detail::Object<cl_type>::Object;

		auto inline operator=(const Event & rhs) -> Event &;

		//================================================================================
		// Wrapper API for clSetUserEventStatus
		//================================================================================

		void inline setStatus(cl_int status) const;
		void inline setStatusComplete() const;
		void inline setStatusError() const;

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

		auto inline getCommandQueue() const   -> boost::optional<CommandQueue>;
		auto inline getContext() const        -> Context;
		auto inline getCommand() const        -> Command;
		auto inline getStatus() const         -> ExecutionStatus;
		auto inline getReferenceCount() const -> cl_uint;

		//================================================================================
		// Information access profiling helper methods.
		//================================================================================
	public:

		auto inline getProfilingQueued() const   -> cl_ulong;
		auto inline getProfilingSubmit() const   -> cl_ulong;
		auto inline getProfilingStart() const    -> cl_ulong;
		auto inline getProfilingEnd() const      -> cl_ulong;
		auto inline getProfilingComplete() const -> cl_ulong;
	};
}

#endif
