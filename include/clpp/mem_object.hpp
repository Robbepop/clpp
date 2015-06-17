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

			static auto release(cl_mem id) { return clReleaseMemObject(id); }

			static auto retain(cl_mem id) { return clRetainMemObject(id); }

			static auto getInfo(
				cl_mem      memory_object,
				cl_mem_info param_name,
				size_t      param_value_size,
				void *      param_value,
				size_t *    param_value_size_ret
			) {
				return clGetMemObjectInfo(
					memory_object, param_name, param_value_size, param_value, param_value_size_ret);
			}
		};
	}

	class Context;

	class MemObject : public detail::Object<cl_mem> {
		//================================================================================
		// Constructor and Assignment
		//================================================================================
	public:

		using detail::Object<cl_type>::Object;

		auto operator=(const MemObject & rhs) -> MemObject &;

		//================================================================================
		// OpenCL API wrapper for setMemObjectDestructorCallback()
		//================================================================================

		template<typename Function, typename T>
		void setDestructorCallback(Function callback, T&& data) const;

		//================================================================================
		// Information access helper methods.
		//================================================================================
	public:

		auto getType() const                -> MemObjectType;
		auto getFlags() const               -> MemoryFlags;
		auto getSize()  const               -> size_t;
		auto getHostPtr() const             -> void*;
		auto getMapCount() const            -> cl_uint;
		auto getReferenceCount() const      -> cl_uint;
		auto getContext() const             -> std::unique_ptr<Context>;
		auto getAssociatedMemObject() const -> boost::optional<std::unique_ptr<MemObject>>;
		auto getOffset() const              -> size_t;
		auto usesSvmPointer() const         -> cl_bool;
	};
}

#endif
