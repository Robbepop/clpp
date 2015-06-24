#ifndef CLPP_CONTEXT_PROPERTIES_HPP
#define CLPP_CONTEXT_PROPERTIES_HPP

#include "detail/common.hpp"

#include <unordered_map>
#include <vector>

#include "clpp/utility/concepts.hpp"

#include "boost/optional.hpp"

namespace cl {
	class Platform;

	class ContextProperties final {
	public:
		using key_type = cl_context_properties;
		using val_type = cl_context_properties;

		inline ContextProperties() = default;

		template<typename InputRange,
			CLPP_REQUIRES(concept::is_range<InputRange>::value)>
		ContextProperties(InputRange const& properties);

		auto inline setPlatform(Platform platform)   -> ContextProperties &;
		auto inline setInteropUserSync(cl_bool flag) -> ContextProperties &;

		template<typename Value>
		auto set(key_type property, Value value) -> ContextProperties &;

		auto inline getPlatform() const        -> Platform;
		auto inline getInteropUserSync() const -> bool;

		template<typename RetType>
		auto get(key_type property) const -> boost::optional<RetType>;

		auto inline data() const -> std::vector<cl_context_properties>;

	private:
		std::unordered_map<key_type, val_type> m_properties;
	};
}

#endif
