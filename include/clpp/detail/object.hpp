#ifndef CLPP_DETAIL_OBJECT_HPP
#define CLPP_DETAIL_OBJECT_HPP

#include "clpp/detail/information_accessor.hpp"

#include <vector>
#include <string>

namespace cl {
	namespace detail {
		//================================================================================
		// ObjectHandler struct contains several useful information
		// about the wrapping class and its wrapped object,
		// types, states and functions.
		//
		// Types:
		//     cl_type        : the OpenCL type being wrapped
		//     exception_type : the exception type for the object being wrapped
		//     info_type      : the OpenCL type to query information of the object being wrapped
		// 
		// Functions:
		//     retain  : the OpenCL retain function for the object being wrapped
		//     release : the OpenCL release function for the object being wrapped
		//     getInfo : the OpenCL information function for the object being wrapped
		//================================================================================
		template <typename T>
		struct ObjectHandler {};

		//================================================================================
		// Wraps the OpenCL type T of an object with this class and provides basic
		// object oriented operations which can be unified among all OpenCL primitives.
		// Uses ObjectHandler template specialization in order to retrieve information
		// about OpenCL specific details of its types.
		//
		// This is the base class of all OpenCL objects in this wrapper.
		//================================================================================
		template<typename CLType>
		class Object {
		public:
			using info_type      = typename ObjectHandler<CLType>::info_type;
			using cl_type        = typename ObjectHandler<CLType>::cl_type;

			//============================================================================
			// Returns the underlying OpenCL data of the wrapped object.
			//============================================================================
			auto get() const -> cl_type;
		protected:
			cl_type m_object;

			//============================================================================
			// Constructors & Destructor
			//============================================================================

		public:
			Object<CLType>();
			Object<CLType>(cl_type rhs);
			Object<CLType>(const Object<CLType> & rhs);
			Object<CLType>(Object<CLType> && rhs) = default;

		protected:
			~Object<CLType>();

			//============================================================================
			// Copy and move assignment operator overloadings
			//============================================================================

			auto operator=(const Object<CLType> &  rhs) -> Object<CLType> &;
			auto operator=(      Object<CLType> && rhs) -> Object<CLType> & = default;

			//============================================================================
			// Helper methods to access information about the wrapped
			// object. Three forms to allow for best performance in
			// each case and a clean API.
			//============================================================================

			template<typename InfoType>
			auto getInfo(info_type p_info) const -> InfoType;

			template<typename InfoType>
			auto getInfoVector(info_type p_info) const -> std::vector<InfoType>;

			auto getInfoString(info_type p_info) const -> std::string;

		private:
			void release();
			void retain();
		};
	}
}

#endif
