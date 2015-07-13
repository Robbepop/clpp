// This is the only file a project should actually include as this is a header-only
// library that requires correct inclusion order of its header and header implementation
// files in order to work.

#ifndef CLPP_HPP
#define CLPP_HPP

#include "clpp/detail/common.hpp"

#include "clpp/detail/cl_function.hpp"

#include "clpp/platform.hpp"
#include "clpp/device.hpp"
#include "clpp/context.hpp"

//===========================================================
// Include implementations of already included header files.
// This is required as the header files themselve must not
// include their own implementation since this causes
// problems with circular dependencise between them.
//===========================================================

#include "clpp/detail/cl_function.ipp"
#include "clpp/detail/error_handler.ipp"
#include "clpp/detail/command_queue_executor.ipp"
#include "clpp/detail/information_accessor.ipp"
#include "clpp/detail/mask_wrapper.ipp"
#include "clpp/detail/object.ipp"
#include "clpp/detail/property_list_wrapper.ipp"

#include "clpp/affinity_domain_capabilities.ipp"
#include "clpp/buffer.ipp"
#include "clpp/command_queue.ipp"
#include "clpp/command_queue_flags.ipp"
#include "clpp/command_queue_properties.ipp"
#include "clpp/context.ipp"
#include "clpp/context_properties.ipp"
#include "clpp/device.ipp"
#include "clpp/event.ipp"
#include "clpp/execution_capabilities.ipp"
#include "clpp/fp_config.ipp"
#include "clpp/kernel.ipp"
#include "clpp/local_memory.ipp"
#include "clpp/mapped_memory.ipp"
#include "clpp/mem_object.ipp"
#include "clpp/mem_object_flags.ipp"
#include "clpp/nd_range.ipp"
#include "clpp/partition.ipp"
#include "clpp/partition_capabilities.ipp"
#include "clpp/platform.ipp"
#include "clpp/program.ipp"
#include "clpp/ret_code.ipp"
#include "clpp/svm_capabilities.ipp"

//===========================================================
// Undefine defined macros to not invalidate other macros
// from other libraries and/or components.
//===========================================================

#undef CLPP_REQUIRES // defined in "utility/type_traits.hpp"

#endif
