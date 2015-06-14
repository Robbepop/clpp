#ifndef CPPCL_DETAIL_OBJECT_H
	#error "Do not include this file directly!"
#endif

#include "clpp/detail/error_handler.hpp"
#include "clpp/detail/get_info_helper.hpp"
#include "clpp/ret_code.hpp"

namespace cl {
	namespace detail {

		template<typename CLType>
		auto Object<CLType>::get() const -> Object<CLType>::cl_type {
			return m_object;
		}

		//================================================================================
		// Constructor, Destructor, Assignment Operator
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

		template<typename CLType>
		Object<CLType> & Object<CLType>::operator=(const Object<CLType> & rhs) {
			m_object = rhs.m_object;
			retain();
			return *this;
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
				detail::error::handle(
					ObjectHandler<CLType>::release(m_object));
			}
		}

		template<typename CLType>
		void Object<CLType>::retain() {
			if (m_object != nullptr) {
				detail::error::handle(
					ObjectHandler<CLType>::retain(m_object));
			}
		}
	}
}
