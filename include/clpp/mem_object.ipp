#ifdef  CLPP_MEM_OBJECT_IPP
	#error "multiple inclusions of the same implementation file"
#else
#define CLPP_MEM_OBJECT_IPP

#ifndef CLPP_MEM_OBJECT_HPP
	#error "header file has not been included; maybe it isn't required anymore?"
	#include "clpp/mem_object.hpp"
#endif

#include <memory>

namespace cl {
	auto MemObject::operator=(const MemObject & rhs) -> MemObject & {
		if (this != &rhs) {
		    detail::Object<cl_type>::operator=(rhs);
		}
		return *this;
	}

	template<typename Function>
	void MemObject::setDestructorCallback(Function callback) const {
		auto error = clSetMemObjectDestructorCallback(
			get(),
			[](cl_mem memobj, void* user_data) {
				const auto temp = reinterpret_cast<Function>(user_data);
				temp({memobj});
			},
			std::addressof(callback));
		detail::handleError(detail::CLFunction::clSetMemObjectDestructorCallback(), error);
	}

	auto MemObject::getType() const -> MemObjectType {
		return static_cast<MemObjectType>(getInfo<cl_mem_object_type>(CL_MEM_TYPE));
	}

	auto MemObject::getFlags() const -> MemoryFlags {
		return {getInfo<cl_mem_flags>(CL_MEM_FLAGS)};
	}

	auto MemObject::getSize() const -> size_t {
		return getInfo<size_t>(CL_MEM_SIZE);
	}

	auto MemObject::getHostPtr() const -> void* {
		return getInfo<void*>(CL_MEM_HOST_PTR);
	}

	auto MemObject::getMapCount() const -> cl_uint {
		return getInfo<cl_uint>(CL_MEM_MAP_COUNT);
	}

	auto MemObject::getReferenceCount() const -> cl_uint {
		return getInfo<cl_uint>(CL_MEM_REFERENCE_COUNT);
	}

	auto MemObject::getContext() const -> Context {
		return {getInfo<cl_context>(CL_MEM_CONTEXT)};
	}

	auto MemObject::getAssociatedMemObject() const -> boost::optional<MemObject> {
		const auto memId = getInfo<cl_mem>(CL_MEM_ASSOCIATED_MEMOBJECT);
		if (memId != nullptr) {
			return boost::make_optional<MemObject>(memId);
		}
		return {};
	}

	auto MemObject::getOffset() const -> size_t {
		return getInfo<size_t>(CL_MEM_OFFSET);
	}

#if defined(CL_VERSION_2_0)
	auto MemObject::usesSvmPointer() const -> cl_bool {
		return getInfo<cl_bool>(CL_MEM_USES_SVM_POINTER);
	}
#endif // defined(CL_VERSION_2_0)
}

#endif
