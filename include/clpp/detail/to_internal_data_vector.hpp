#ifndef CLPP_DETAIL_TO_INTERNAL_DATA_VECTOR_HPP
#define CLPP_DETAIL_TO_INTERNAL_DATA_VECTOR_HPP

#include <iterator>
#include <type_traits>

#include "clpp/utility/count_elements.hpp"

// This is used to convert ranges of containers or iterator with wrapped OpenCL types
// into a vector of internal OpenCL data types. This is always required when the input
// range isn't contiguous or when the internal representation of a wrapping OpenCL type
// doesn't match the wrapped type.

namespace cl {
	namespace detail {
		namespace util {
			template<typename InputIterator>
			auto to_internal_data_vector(
				InputIterator first, InputIterator last
			){
				using value_type = typename InputIterator::value_type;
				using cl_type    = typename std::decay_t<
					decltype(std::declval<value_type>().get())>;
				std::vector<cl_type> result;
				result.reserve(::utility::count_elements(first, last));
				std::transform(first, last, std::back_inserter(result),
					[](auto obj) { return obj.get(); }
				);
				return result;
			}

			template<typename InputRange>
			auto to_internal_data_vector(
				InputRange const& range
			){
				return to_internal_data_vector(
					std::begin(range), std::end(range));
			}
		}
	}
}

#endif // CLPP_DETAIL_TO_INTERNAL_DATA_VECTOR_HPP