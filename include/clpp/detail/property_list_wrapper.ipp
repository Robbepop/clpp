#ifdef  CLPP_DETAIL_PROPERTY_LIST_WRAPPER_IPP
	#error "multiple inclusions of the same implementation file"
#else
#define CLPP_DETAIL_PROPERTY_LIST_WRAPPER_IPP

#ifndef CLPP_DETAIL_PROPERTY_LIST_WRAPPER_HPP
	#error "header file has not been included; maybe it isn't required anymore?"
	#include "clpp/detail/property_list_wrapper.hpp"
#endif

#include <memory>
#include <cassert>

namespace cl {
	namespace detail {

		template<typename ListType>
		PropertyListWrapper<ListType>::PropertyListWrapper(
			ListType const* properties
		) {
			auto current      = std::addressof(properties[0]);
			auto extract      = [&]() {
				auto& key   = *(current++);
				auto& value = *(current++);
				m_properties[key] = value;
			};
			while (*current != getListEnd()) {
				extract();
			}
		}

		template<typename ListType>
		PropertyListWrapper<ListType>::PropertyListWrapper(
			std::initializer_list<typename PropertyMap::value_type> properties
		):
			m_properties{properties}
		{}

		template<typename ListType>
		constexpr auto PropertyListWrapper<ListType>::getListEnd() const -> ListType {
			return 0;
		}

		template<typename ListType>
		auto PropertyListWrapper<ListType>::data() const -> std::vector<ListType> {
			auto size = m_properties.size();
			auto list = std::vector<ListType>();
			list.reserve(size + 1);
			for (auto&& property : m_properties) {
				list.push_back(property.first);
				list.push_back(property.second);
			}
			list.push_back(getListEnd());
			return list;
		}

		template<typename ListType>
		void PropertyListWrapper<ListType>::set(
			ListType property,
			ListType value
		) {
			m_properties[property] = value;
		}

		template<typename ListType>
		auto PropertyListWrapper<ListType>::get(
			ListType property
		) const -> ListType {
			return m_properties[property];
		}

		template<typename ListType>
		auto PropertyListWrapper<ListType>::get(
			ListType property
		) -> ListType & {
			return m_properties[property];
		}
	}
}

#endif
