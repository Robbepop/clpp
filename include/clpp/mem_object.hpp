#ifndef CLPP_MEM_OBJECT_HPP
#define CLPP_MEM_OBJECT_HPP

#include "clpp/detail/object.hpp"
#include "clpp/detail/error_handler.hpp"
#include "clpp/mem_object_type.hpp"
#include "clpp/mem_object_flags.hpp"

#include "boost/optional.hpp"

namespace cl {
	namespace detail {
		template<>
		struct ObjectHandler<cl_mem> final {
			using cl_type        = cl_mem;
			using info_type      = cl_mem_info;

			static constexpr auto retain  = clRetainMemObject;
			static constexpr auto release = clReleaseMemObject;
			static constexpr auto getInfo = clGetMemObjectInfo;
		};
	}

	class Context;

	class MemObject : public detail::Object<cl_mem> {
		//================================================================================
		// Constructor and Assignment
		//================================================================================
	public:

		using detail::Object<cl_type>::Object;

		auto inline operator=(const MemObject & rhs) -> MemObject &;

		//================================================================================
		// OpenCL API wrapper for setMemObjectDestructorCallback()
		//================================================================================

		template<typename Function, typename T>
		void setDestructorCallback(Function callback, T&& data) const;

		//================================================================================
		// Information access helper methods.
		//================================================================================
	public:

		auto inline getType() const                -> MemObjectType;
		auto inline getFlags() const               -> MemoryFlags;
		auto inline getSize()  const               -> size_t;
		auto inline getHostPtr() const             -> void*;
		auto inline getMapCount() const            -> cl_uint;
		auto inline getReferenceCount() const      -> cl_uint;
		auto inline getContext() const             -> std::unique_ptr<Context>;
		auto inline getAssociatedMemObject() const -> boost::optional<std::unique_ptr<MemObject>>;
		auto inline getOffset() const              -> size_t;
		auto inline usesSvmPointer() const         -> cl_bool;
	};
}

#endif
