#ifndef CLPP_MEM_OBJECT_H
	#error "Do not include this file directly."
#endif

namespace cl {
	MemObject& MemObject::operator=(const MemObject & rhs) {
		if (this != &rhs) {
		    detail::Object<cl_type>::operator=(rhs);
		}
		return *this;
	}

	template<typename Function, typename T>
	auto MemObject::setDestructorCallback(Function callback, T&& data) {
		struct CallbackWrapper {
			Function m_callback;
			T&& m_data;
		};
		auto cbw   = new CallbackWrapper{callback, std::forward(data)};
		auto error = cl_int{CL_INVALID_VALUE};
		error = clSetMemObjectDestructorCallback(
			get(),
			[](cl_mem memobj, void* user_data) {
				auto temp = reinterpret_cast<CallbackWrapper*>(user_data);
				temp->callback({memobj}, temp->data);
				delete temp;
			},
			std::addressof(cbw));
	}

	auto MemObject::getType() -> MemObjectType {
		return static_cast<MemObjectType>(getInfo<cl_mem_object_type>(CL_MEM_TYPE));
	}

	auto MemObject::getFlags() -> MemObjectFlags {
		return {getInfo<cl_mem_flags>(CL_MEM_FLAGS)};
	}

	auto MemObject::getSize() -> size_t {
		return getInfo<size_t>(CL_MEM_SIZE);
	}

	auto MemObject::getHostPtr() -> void* {
		return getInfo<void*>(CL_MEM_HOST_PTR);
	}

	auto MemObject::getMapCount() -> cl_uint {
		return getInfo<cl_uint>(CL_MEM_MAP_COUNT);
	}

	auto MemObject::getReferenceCount() -> cl_uint {
		return getInfo<cl_uint>(CL_MEM_REFERENCE_COUNT);
	}

	auto MemObject::getContext() -> Context {
		return {getInfo<cl_context>(CL_MEM_CONTEXT)};
	}

	auto MemObject::getAssociatedMemObject() -> boost::optional<MemObject> {
		const auto memId = getInfo<cl_device_id>(CL_MEM_ASSOCIATED_MEMOBJECT);
		if (memId == nullptr) {
			return {};
		}
		return {{memId}};
	}

	auto MemObject::getOffset() -> size_t {
		return getInfo<size_t>(CL_MEM_OFFSET);
	}

	auto MemObject::usesSvmPointer() -> cl_bool {
		return getInfo<cl_bool>(CL_MEM_USES_SVM_POINTER);
	}
}