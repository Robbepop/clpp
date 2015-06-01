#ifndef CLPP_CONTEXT_PROPERTIES_H
#define CLPP_CONTEXT_PROPERTIES_H

#include "detail/common.hpp"

#include <unordered_map>
#include <vector>

namespace cl {
	class Platform;

	class ContextProperties final {
	public:
		using key_type = cl_context_properties;
		using val_type = cl_context_properties;

		ContextProperties() = default;

		template<typename InputRange>
		ContextProperties(InputRange properties);

		auto setPlatform(Platform platform) -> ContextProperties &;
		auto setInteropUserSync(cl_bool flag) -> ContextProperties &;

		template<typename Value>
		auto set(key_type property, Value value) -> ContextProperties &;

		auto getPlatform() -> Platform;
		auto getInteropUserSync() -> cl_bool;

		template<typename RetType>
		auto get(key_type property) -> RetType;

		auto data() const -> std::vector<cl_context_properties>;

	private:
		std::unordered_map<key_type, val_type> m_properties;
	};
}

#include "clpp/context_properties.tpp"
#endif
