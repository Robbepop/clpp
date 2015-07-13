#ifndef CLPP_DETAIL_PROPERTY_LIST_WRAPPER_HPP
#define CLPP_DETAIL_PROPERTY_LIST_WRAPPER_HPP

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

			void set(ListType property, ListType value);

			auto get(ListType property) const -> ListType;
			auto get(ListType property)       -> ListType &;

		protected:
			PropertyMap m_properties;
		};
	}
}

#endif
