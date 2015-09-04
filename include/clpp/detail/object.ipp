#ifdef  CLPP_DETAIL_OBJECT_IPP
	#error "multiple inclusions of the same implementation file"
#else
#define CLPP_DETAIL_OBJECT_IPP

#ifndef CLPP_DETAIL_OBJECT_HPP
	#error "header file has not been included; maybe it isn't required anymore?"
	#include "clpp/detail/object.hpp"
#endif

#include "clpp/detail/error_handler.hpp"
#include "clpp/detail/information_accessor.hpp"
#include "clpp/ret_code.hpp"

namespace cl {
	namespace detail {

		template<typename CLType>
		auto Object<CLType>::get() const -> Object<CLType>::cl_type const& {
			return m_object;
		}

		//================================================================================
		// Constructor, Destructor
		//================================================================================

		template<typename CLType>
		Object<CLType>::Object():
			m_object{nullptr}
		{}

		template<typename CLType>
		Object<CLType>::Object(Object<CLType>::cl_type object):
			m_object{object}
		{}

		template<typename CLType>
		Object<CLType>::Object(const Object<CLType> & rhs):
			m_object{rhs.m_object}
		{
			retain();
		}

		template<typename CLType>
		Object<CLType>::~Object() {
			release();
		}

		//================================================================================
		// Assigment Operator Overloads
		//================================================================================

		template<typename CLType>
		auto Object<CLType>::operator=(
			const Object<CLType> & rhs
		)
			-> Object<CLType> &
		{
			release();
			m_object = rhs.m_object;
			retain();
			return *this;
		}

		template<typename CLType>
		auto Object<CLType>::operator=(
			const cl_type & rhs
		)
			-> Object<CLType> &
		{
		    release();
		    m_object = rhs;
		    return *this;
		}

		//============================================================================
		// Operators for checking if two objects are equal or unequal.
		//============================================================================

		template<typename CLType>
		auto Object<CLType>::operator==(const Object<CLType> & rhs) const -> bool {
			return m_object == rhs.m_object;
		}

		template<typename CLType>
		auto Object<CLType>::operator!=(const Object<CLType> & rhs) const -> bool {
			return m_object != rhs.m_object;
		}

		//================================================================================
		// Helper methods to access information about the wrapped
		// object. Three forms to allow for best performance in
		// each case and a clean API.
		//================================================================================

		template<typename CLType>
		template<typename T>
		auto Object<CLType>::getInfo(Object<CLType>::info_type infoId) const
			-> T
		{
			return utility::getInfo<T>(get(), infoId, ObjectHandler<cl_type>::getInfo);
		}

		template<typename CLType>
		template<typename T>
		auto Object<CLType>::getInfoVector(Object<CLType>::info_type infoId) const
			-> std::vector<T>
		{
			return utility::getInfoVector<T>(get(), infoId, ObjectHandler<cl_type>::getInfo);
		}

		template<typename CLType>
		auto Object<CLType>::getInfoString(Object<CLType>::info_type infoId) const
			-> std::string
		{
			return detail::utility::getInfoString(
				get(), infoId, ObjectHandler<cl_type>::getInfo);
		}

		//================================================================================
		// Helper methods to wrap call to release and retain of the wrapped OpenCL
		// object in order to provide error handling mechanism.
		//================================================================================

		template<typename CLType>
		void Object<CLType>::release() {
			if (m_object != nullptr) {
				detail::handleError(
					ObjectHandler<CLType>::release,
					ObjectHandler<CLType>::release(m_object));
			}
		}

		template<typename CLType>
		void Object<CLType>::retain() {
			if (m_object != nullptr) {
				detail::handleError(
					ObjectHandler<CLType>::retain,
					ObjectHandler<CLType>::retain(m_object));
			}
		}

		template<typename CLType>
		auto operator==(const cl::detail::Object<CLType> & lhs, std::nullptr_t) -> bool {
			return lhs.get() == nullptr;
		}

		template<typename CLType>
		auto operator!=(const cl::detail::Object<CLType> & lhs, std::nullptr_t) -> bool {
			return lhs.get() != nullptr;
		}

		template<typename CLType>
		auto operator==(const cl::detail::Object<CLType> & lhs, const CLType & rhs) -> bool {
			return lhs.get() == rhs;
		}

		template<typename CLType>
		auto operator!=(const cl::detail::Object<CLType> & lhs, const CLType & rhs) -> bool {
			return lhs.get() != rhs;
		}

		template<typename CLType>
		auto operator==(const CLType & lhs, const cl::detail::Object<CLType> & rhs) -> bool {
			return rhs == lhs;
		}

		template<typename CLType>
		auto operator!=(const CLType & lhs, const cl::detail::Object<CLType> & rhs) -> bool {
			return rhs != lhs;
		}
	}
}

#endif
