#ifndef CLPP_DETAIL_MASK_WRAPPER_H
#define CLPP_DETAIL_MASK_WRAPPER_H

#include "clpp/detail/common.hpp"

namespace cl {
	namespace detail {
		template<typename MaskType>
		class MaskWrapper {
		public:
			using cl_mask_type = MaskType;

			MaskWrapper(MaskType mask);
			MaskWrapper();

			MaskType mask() const;

		protected:
			MaskType m_mask;

			//================================================================================
			// Helper methods in order to make access to underlying mask more easy.
			//================================================================================

			template<MaskType Option>
			void modifyMask(cl_bool flag);

			template<MaskType Option>
			auto readMask() const -> cl_bool;
		};
	}
}

#include "clpp/detail/mask_wrapper.tpp"
#endif
