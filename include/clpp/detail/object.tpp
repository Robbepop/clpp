#ifndef CPPCL_DETAIL_OBJECT_H
	#error "Do not include this file directly!"
#endif

#include "clpp/detail/error_handler.hpp"
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
		template<typename InfoType>
		auto Object<CLType>::getInfo(Object<CLType>::info_type p_info) const
			-> InfoType
		{
			auto error = cl_int{CL_INVALID_VALUE};
			auto data  = InfoType{};
			error = ObjectHandler<CLType>::getInfo(
				m_object, p_info, sizeof(InfoType), std::addressof(data), nullptr);
			error::handle<Object<CLType>::exception_type>(error);
			return data;
		}

		template<typename CLType>
		template<typename InfoType>
		auto Object<CLType>::getInfoVector(Object<CLType>::info_type p_info) const
			-> std::vector<InfoType>
		{
			auto error    = cl_int{CL_INVALID_VALUE};
			auto req_size = size_t{0};
			error = ObjectHandler<CLType>::getInfo(
				m_object, p_info, 0, nullptr, std::addressof(req_size));
			error::handle<Object<CLType>::exception_type>(error);
			const auto count_elems = req_size / sizeof(InfoType);
				  auto info        = std::vector<InfoType>(count_elems);
			error = ObjectHandler<CLType>::getInfo(m_object, p_info, req_size, info.data(), nullptr);
			error::handle<Object<CLType>::exception_type>(error);
			return info;
		}

		template<typename CLType>
		auto Object<CLType>::getInfoString(Object<CLType>::info_type p_info) const
			-> std::string
		{
			const auto data = getInfoVector<char>(p_info);
			return {data.begin(), data.end()};
		}

		//================================================================================
		// Helper methods to wrap call to release and retain of the wrapped OpenCL
		// object in order to provide error handling mechanism.
		//================================================================================

		template<typename CLType>
		void Object<CLType>::release() {
			if (m_object != nullptr) {
				ObjectHandler<CLType>::release(m_object);
				//error::handle(
				//	ObjectHandler<CLType>::release(m_object));
			}
		}

		template<typename CLType>
		void Object<CLType>::retain() {
			if (m_object != nullptr) {
				ObjectHandler<CLType>::retain(m_object);
//				error::handle(
//					ObjectHandler<CLType>::retain(m_object));
			}
		}
	}
}
