#ifndef CLPP_LOCAL_MEMORY_HPP
#define CLPP_LOCAL_MEMORY_HPP

#include <cstdint>

namespace cl {
	template<typename T>
	class LocalMemory final {
	public:
		using value_type = T;

		explicit LocalMemory(size_t);

		auto size() const -> size_t;
		auto getSize() const -> size_t;
		auto getSizeInBytes() const -> size_t;

	private:
		size_t m_size;
	};
}

#endif
