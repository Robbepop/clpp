#ifndef UTILITY_MAKE_ARRAY_H
#define UTILITY_MAKE_ARRAY_H

#include <array>
#include <functional>

namespace utility {

	template <typename... T>
	using common_type_t = typename std::common_type<T...>::type;

	template <typename T>
	using remove_cv_t = typename std::remove_cv<T>::type;

	template <bool, typename T, typename... U>
	struct lazy_conditional_c;

	template <typename T>
	struct lazy_conditional_c<true, T>
	{
		using type = typename T::type;
	};

	template <typename T, typename U>
	struct lazy_conditional_c<true, T, U>
	{
		using type = typename T::type;
	};

	template <typename T, typename U>
	struct lazy_conditional_c<false, T, U>
	{
		using type = typename U::type;
	};

	template <typename V, typename T, typename... U>
	using If = lazy_conditional_c<V::value, T, U...>;

	template <typename V, typename T, typename... U>
	using If_t = typename If<V, T, U...>::type;

	template <typename T>
	struct identity_of
	{
		using type = T;
	};

	template <template <typename> class F, typename... T>
	struct no_type : std::true_type {};

	template <template <typename> class F, typename T1, typename... T2>
	struct no_type<F, T1, T2...> :
		std::integral_constant
		<
			bool,
			not F<T1>::value and no_type<F, T2...>::value
		>
	{};

	template <template <typename> class F, template <typename> class G>
	struct composed
	{
		template <typename T>
		using call = F<typename G<T>::type>;
	};

	template <typename T>
	struct _is_reference_wrapper : std::false_type {};

	template <typename T>
	struct _is_reference_wrapper<std::reference_wrapper<T>> : std::true_type {};

	template <typename T>
	using is_reference_wrapper =
		composed<_is_reference_wrapper, std::remove_cv>::call<T>;

	template <typename V = void, typename... T>
	constexpr auto make_array(T&&... t)
		-> std::array
		<
			If_t
			<
			std::is_void<V>,
			If
			<
				no_type
				<
				composed
				<
					is_reference_wrapper,
					std::remove_reference
				>
				::call,
				T...
				>,
				std::common_type<T...>
			>,
			identity_of<V>
			>,
			sizeof...(T)
		>
	{
		return {{ std::forward<T>(t)... }};
	}

	template <size_t... I>
	struct _indices {};

	template <size_t N, size_t... I>
	struct _build_indices : _build_indices<N - 1, N - 1, I...> {};
	 
	template <size_t... I>
	struct _build_indices<0, I...> : _indices<I...> {};

	template <typename T, size_t N, size_t... I>
	constexpr auto _to_array(T (&arr)[N], _indices<I...>)
		-> std::array<remove_cv_t<T>, N>
	{
		return {{ arr[I]... }};
	}

	template <typename T, size_t N>
	constexpr auto to_array(T (&arr)[N])
		-> std::array<remove_cv_t<T>, N>
	{
		return _to_array(arr, _build_indices<N>());
	}

}

#endif
