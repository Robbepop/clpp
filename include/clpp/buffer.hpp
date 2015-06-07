#ifndef CLPP_BUFFER_H
#define CLPP_BUFFER_H

#include "clpp/mem_object.hpp"

namespace cl {
	template<typename T>
	class Buffer : public MemObject {
	public:
		using MemObject::MemObject;

		Buffer & operator=(Buffer const& rhs);

		auto size() const       -> size_t;

		auto getSize() const    -> size_t;
		auto getOffset() const  -> size_t;

		auto getHostPtr() const -> T*;
		auto getAssociatedBuffer() const -> boost::optional<Buffer<T>>;
	};
}

#endif
