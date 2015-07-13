#ifndef CLPP_DETAIL_PROPERTY_LIST_WRAPPER_HPP
#define CLPP_DETAIL_PROPERTY_LIST_WRAPPER_HPP

#include "boost/optional.hpp"

#include <unordered_map>
#include <vector>

namespace cl {
	namespace detail {
		template<typename ListType>
		class PropertyListWrapper {
		public:
			using PropertyMap  = std::unordered_map<ListType, ListType>;
			using cl_list_type = ListType;

			PropertyListWrapper() = default;
			PropertyListWrapper(ListType const* properties);
			PropertyListWrapper(std::initializer_list<typename PropertyMap::value_type> properties);

			constexpr auto getListEnd() const -> ListType;

			auto data() const -> std::vector<ListType>;

			template<typename SetType = ListType>
			void set(ListType property, SetType value);

			template<typename RetType = ListType>
			auto get(ListType property) const -> boost::optional<RetType>;

		protected:
			PropertyMap m_properties;
		};
	}
}

#endif
