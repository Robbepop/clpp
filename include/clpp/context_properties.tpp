#ifndef CLPP_CONTEXT_PROPERTIES_H
	#error "Do not include this file directly."
#endif

namespace cl {
	template<typename InputRange>
	ContextProperties::ContextProperties(InputRange properties) {
		assert(properties.size() % 2 == 1 && "size of properties must be odd");
		for (auto it = properties.begin(); it != properties.end(); it += 2) {
			const auto key = static_cast<ContextProperties::key_type>(*it);
			const auto val = static_cast<ContextProperties::val_type>(*(it + 1));
			m_properties[key] = val;
		}
	}

	template<typename Value>
	auto ContextProperties::set(key_type property, Value value) -> ContextProperties & {
//		const auto val = static_cast<ContextProperties::val_type>(value);       // doesn't work!
//		const auto val = reinterpret_cast<ContextProperties::val_type>(value);  // doesn't work either!
		const auto val = (ContextProperties::val_type) value;
		m_properties[property] = val;
		return *this;
	}

	auto ContextProperties::setPlatform(Platform platform) -> ContextProperties & {
		return set(CL_CONTEXT_PLATFORM, platform.get());
	}

	auto ContextProperties::setInteropUserSync(cl_bool flag) -> ContextProperties & {
		return set(CL_CONTEXT_INTEROP_USER_SYNC, flag);
	}

	template<typename RetType>
	auto ContextProperties::get(ContextProperties::key_type property) -> RetType {
		const auto val = m_properties[property];
		//return reinterpret_cast<RetType>(val); doesn't work!
		//return static_cast<RetType>(val);      doesn't work either!
		return (RetType) val;
	}

	auto ContextProperties::getPlatform() -> Platform {
		return {get<cl_platform_id>(CL_CONTEXT_PLATFORM)};
	}

	auto ContextProperties::getInteropUserSync() -> bool {
		return get<cl_bool>(CL_CONTEXT_INTEROP_USER_SYNC);
	}

	auto ContextProperties::data() const -> std::vector<cl_context_properties> {
		auto list = std::vector<cl_context_properties>{};
		for (auto&& property : m_properties) {
			list.push_back(property.first);
			list.push_back(property.second);
		}
		list.push_back(static_cast<cl_context_properties>(0));
		return list;
	}

}
