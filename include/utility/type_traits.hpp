#ifndef UTILITY_HAS_MEMBER_H
#define UTILITY_HAS_MEMBER_H

#include <type_traits>

#define CLPP_REQUIRES(...) typename = std::enable_if_t<__VA_ARGS__>

namespace utility {
	template<typename... Ts> struct make_void { using type = void; };
	template<typename... Ts> using void_t = typename make_void<Ts...>::type;

	//====================================================================================
	// Used to check if a template type parameter has a ::type member.
	//====================================================================================

	template<class, class = void_t<>>
	struct has_type_member : std::false_type{};
 
	template<class T>
	struct has_type_member<T, void_t<typename T::type>> : std::true_type{};

	//====================================================================================
	// Used to check if a template type parameter is a range which checks this via
	// checking for valid begin() and end() methods.
	//====================================================================================

	template<class, class = void_t<>>
	struct is_range : std::false_type{};

	template<typename T>
	struct is_range<T,
		void_t<
			decltype(std::declval<T>().begin()),
			decltype(std::declval<T>().end())>
		>: std::true_type{};
}

#endif // UTILITY_HAS_MEMBER_H
