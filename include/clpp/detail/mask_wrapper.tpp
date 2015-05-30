#ifndef CLPP_DETAIL_MASK_WRAPPER_H
	#error "Do not include this file directly."
#endif

namespace cl {
	namespace detail {
		template<typename MaskType>
		MaskWrapper<MaskType>::MaskWrapper(MaskType mask):
			m_mask{mask}
		{}

		template<typename MaskType>
		MaskWrapper<MaskType>::MaskWrapper():
			m_mask{0}
		{}

		template<typename MaskType>
		MaskType MaskWrapper<MaskType>::mask() const {
			return m_mask;
		}

		template<typename MaskType>
		template<MaskType Option>
		void MaskWrapper<MaskType>::modifyMask(cl_bool flag) {
			if (flag) m_mask |=  Option;
			else      m_mask &= ~Option;
		}

		template<typename MaskType>
		template<MaskType Option>
		auto MaskWrapper<MaskType>::readMask() const -> cl_bool{
			return !(m_mask & Option);
		}
	}
}
