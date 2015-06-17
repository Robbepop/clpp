#ifndef CLPP_UTILITY_CONCEPTS_HPP
#define CLPP_UTILITY_CONCEPTS_HPP

#include <type_traits>

#define CLPP_REQUIRES(...) typename = std::enable_if_t<__VA_ARGS__>

namespace concept {
	namespace utility {
		template<typename... Ts> struct make_void { using type = void; };
		template<typename... Ts> using void_t = typename make_void<Ts...>::type;
	}

	//====================================================================================
	// Used to check if a template type parameter is a range which checks this via
	// checking for valid begin() and end() methods.
	//====================================================================================
	template<class, class = utility::void_t<>>
	struct is_range : std::false_type{};

	template<typename T>
	struct is_range<T,
		utility::void_t<
			decltype(std::declval<T>().begin()),
			decltype(std::declval<T>().end())>
		>: std::true_type{};
}

#endif // UTILITY_CONCEPTS_H
