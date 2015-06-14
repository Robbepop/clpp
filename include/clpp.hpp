// This is the only file a project should actually include as this is a header-only
// library that requires correct inclusion order of its header and header implementation
// files in order to work.

#ifndef CLPP_H
#define CLPP_H

#include "clpp/detail/common.hpp"

#include "clpp/platform.hpp"
#include "clpp/device.hpp"
#include "clpp/context.hpp"

//===========================================================
// Include implementations of already included header files.
// This is required as the header files themselve must not
// include their own implementation since this causes
// problems with circular dependencise between them.
//===========================================================

#include "clpp/detail/error_handler.tpp"
#include "clpp/detail/command_queue_executor.tpp"
#include "clpp/detail/get_info_helper.tpp"
#include "clpp/detail/mask_wrapper.tpp"
#include "clpp/detail/object.tpp"

#include "clpp/affinity_domain_capabilities.tpp"
#include "clpp/buffer.tpp"
#include "clpp/command_queue.tpp"
#include "clpp/command_queue_properties.tpp"
#include "clpp/context.tpp"
#include "clpp/context_properties.tpp"
#include "clpp/device.tpp"
#include "clpp/event.tpp"
#include "clpp/execution_capabilities.tpp"
#include "clpp/fp_config.tpp"
#include "clpp/kernel.tpp"
#include "clpp/mapped_memory.tpp"
#include "clpp/mem_object.tpp"
#include "clpp/mem_object_flags.tpp"
#include "clpp/nd_range.tpp"
#include "clpp/partition.tpp"
#include "clpp/partition_capabilities.tpp"
#include "clpp/platform.tpp"
#include "clpp/program.tpp"
#include "clpp/svm_capabilities.tpp"

//===========================================================
// Undefine defined macros to not invalidate other macros
// from other libraries and/or components.
//===========================================================

#undef CLPP_REQUIRES // defined in "utility/type_traits.hpp"

#endif
