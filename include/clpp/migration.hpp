#if defined(CL_VERSION_1_2)

#ifndef CLPP_MIGRATION_HPP
#define CLPP_MIGRATION_HPP

#include "clpp/detail/common.hpp"

namespace cl {
	enum class Migration : cl_mem_migration_flags {
		nothing  = CL_MIGRATE_MEM_OBJECT_CONTENT_UNDEFINED,
		contents = 0
	};
}

#endif // CLPP_MIGRATION_HPP
#endif // defined(CL_VERSION_1_2)
