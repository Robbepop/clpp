#ifndef CLPP_DETAIL_MASK_WRAPPER_HPP
#define CLPP_DETAIL_MASK_WRAPPER_HPP

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
			auto readMask() const -> bool;
		};
	}
}

#endif
