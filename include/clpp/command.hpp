#ifndef CLPP_COMMAND_HPP
#define CLPP_COMMAND_HPP

#include "clpp/detail/common.hpp"

namespace cl {
	enum class Command : cl_command_type {
		ndRangeKernel     = CL_COMMAND_NDRANGE_KERNEL,
		nativeKernel      = CL_COMMAND_NATIVE_KERNEL,
		readBuffer        = CL_COMMAND_READ_BUFFER,
		writeBuffer       = CL_COMMAND_WRITE_BUFFER,
		copyBuffer        = CL_COMMAND_COPY_BUFFER,
		readImage         = CL_COMMAND_READ_IMAGE,
		writeImage        = CL_COMMAND_WRITE_IMAGE,
		copyImage         = CL_COMMAND_COPY_IMAGE,
		copyBufferToImage = CL_COMMAND_COPY_BUFFER_TO_IMAGE,
		copyImageToBuffer = CL_COMMAND_COPY_IMAGE_TO_BUFFER,
		mapBuffer         = CL_COMMAND_MAP_BUFFER,
		mapImage          = CL_COMMAND_MAP_IMAGE,
		unmapMemObject    = CL_COMMAND_UNMAP_MEM_OBJECT,
		marker            = CL_COMMAND_MARKER,
		acquireGLObjects  = CL_COMMAND_ACQUIRE_GL_OBJECTS,
		releaseGLObjects  = CL_COMMAND_RELEASE_GL_OBJECTS,

		readBufferRect    = CL_COMMAND_READ_BUFFER_RECT,
		writeBufferRect   = CL_COMMAND_WRITE_BUFFER_RECT,
		copyBufferRect    = CL_COMMAND_COPY_BUFFER_RECT,
		user              = CL_COMMAND_USER,
		barrier           = CL_COMMAND_BARRIER,
		migrateMemObjects = CL_COMMAND_MIGRATE_MEM_OBJECTS,
		fillBuffer        = CL_COMMAND_FILL_BUFFER,
		fillImage         = CL_COMMAND_FILL_IMAGE,

		svmFree           = CL_COMMAND_SVM_FREE,
		svmMemCopy        = CL_COMMAND_SVM_MEMCPY,
		svmMemFill        = CL_COMMAND_SVM_MEMFILL,
		svmMap            = CL_COMMAND_SVM_MAP,
		svmUnmap          = CL_COMMAND_SVM_UNMAP
	};
}

#endif
