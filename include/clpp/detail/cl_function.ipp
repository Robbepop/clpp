#ifdef  CLPP_DETAIL_CL_FUNCTION_IPP
	#error "multiple inclusions of the same implementation file"
#else
#define CLPP_DETAIL_CL_FUNCTION_IPP

#ifndef CLPP_DETAIL_CL_FUNCTION_HPP
	#error "header file has not been included; maybe it isn't required anymore ?"
	#include "clpp/detail/cl_function.hpp"
#endif

#include <utility>

namespace cl {
	namespace detail {
		CLFunction::CLFunction(std::experimental::string_view name):
			m_name{std::move(name)}
		{}

		template<typename CLFunctionPtr>
		auto CLFunction::getByPtr(CLFunctionPtr funcPtr) -> CLFunction const& {
			using ptr_t = void*;
			const auto ptr = (ptr_t) funcPtr;
			return
				ptr == (ptr_t) ::clGetPlatformIDs ?
				   CLFunction::clGetPlatformIDs():
				ptr == (ptr_t) ::clGetPlatformInfo ?
				   CLFunction::clGetPlatformInfo():

				ptr == (ptr_t) ::clGetDeviceIDs ?
				   CLFunction::clGetDeviceIDs():
				ptr == (ptr_t) ::clGetDeviceInfo ?
				   CLFunction::clGetDeviceInfo():

				ptr == (ptr_t) ::clCreateSubDevices ?
				   CLFunction::clCreateSubDevices():
				ptr == (ptr_t) ::clRetainDevice ?
				   CLFunction::clRetainDevice():
				ptr == (ptr_t) ::clReleaseDevice ?
				   CLFunction::clReleaseDevice():

				ptr == (ptr_t) ::clCreateContext ?
				   CLFunction::clCreateContext():
				ptr == (ptr_t) ::clCreateContextFromType ?
				   CLFunction::clCreateContextFromType():
				ptr == (ptr_t) ::clRetainContext ?
				   CLFunction::clRetainContext():
				ptr == (ptr_t) ::clReleaseContext ?
				   CLFunction::clReleaseContext():
				ptr == (ptr_t) ::clGetContextInfo ?
				   CLFunction::clGetContextInfo():

				ptr == (ptr_t) ::clCreateCommandQueueWithProperties ?
				   CLFunction::clCreateCommandQueueWithProperties():
				ptr == (ptr_t) ::clRetainCommandQueue ?
				   CLFunction::clRetainCommandQueue():
				ptr == (ptr_t) ::clReleaseCommandQueue ?
				   CLFunction::clReleaseCommandQueue():
				ptr == (ptr_t) ::clGetCommandQueueInfo ?
				   CLFunction::clGetCommandQueueInfo():

				ptr == (ptr_t) ::clCreateBuffer ?
				   CLFunction::clCreateBuffer():
				ptr == (ptr_t) ::clCreateSubBuffer ?
				   CLFunction::clCreateSubBuffer():
				ptr == (ptr_t) ::clEnqueueReadBuffer ?
				   CLFunction::clEnqueueReadBuffer():
				ptr == (ptr_t) ::clEnqueueWriteBuffer ?
				   CLFunction::clEnqueueWriteBuffer():
				ptr == (ptr_t) ::clEnqueueReadBufferRect ?
				   CLFunction::clEnqueueReadBufferRect():
				ptr == (ptr_t) ::clEnqueueWriteBufferRect ?
				   CLFunction::clEnqueueWriteBufferRect():
				ptr == (ptr_t) ::clEnqueueCopyBuffer ?
				   CLFunction::clEnqueueCopyBuffer():
				ptr == (ptr_t) ::clEnqueueCopyBufferRect ?
				   CLFunction::clEnqueueCopyBufferRect():
				ptr == (ptr_t) ::clEnqueueFillBuffer ?
				   CLFunction::clEnqueueFillBuffer():
				ptr == (ptr_t) ::clEnqueueMapBuffer ?
				   CLFunction::clEnqueueMapBuffer():

				ptr == (ptr_t) ::clCreateImage ?
				   CLFunction::clCreateImage():
				ptr == (ptr_t) ::clGetSupportedImageFormats ?
				   CLFunction::clGetSupportedImageFormats():
				ptr == (ptr_t) ::clEnqueueReadImage ?
				   CLFunction::clEnqueueReadImage():
				ptr == (ptr_t) ::clEnqueueWriteImage ?
				   CLFunction::clEnqueueWriteImage():
				ptr == (ptr_t) ::clEnqueueCopyImage ?
				   CLFunction::clEnqueueCopyImage():
				ptr == (ptr_t) ::clEnqueueCopyImageToBuffer ?
				   CLFunction::clEnqueueCopyImageToBuffer():
				ptr == (ptr_t) ::clEnqueueCopyBufferToImage ?
				   CLFunction::clEnqueueCopyBufferToImage():
				ptr == (ptr_t) ::clEnqueueFillImage ?
				   CLFunction::clEnqueueFillImage():
				ptr == (ptr_t) ::clEnqueueMapImage ?
				   CLFunction::clEnqueueMapImage():

				ptr == (ptr_t) ::clEnqueueUnmapMemObject ?
				   CLFunction::clEnqueueUnmapMemObject():
				ptr == (ptr_t) ::clEnqueueMigrateMemObjects ?
				   CLFunction::clEnqueueMigrateMemObjects():
				ptr == (ptr_t) ::clGetImageInfo ?
				   CLFunction::clGetImageInfo():
				ptr == (ptr_t) ::clGetMemObjectInfo ?
				   CLFunction::clGetMemObjectInfo():
				ptr == (ptr_t) ::clRetainMemObject ?
				   CLFunction::clRetainMemObject():
				ptr == (ptr_t) ::clReleaseMemObject ?
				   CLFunction::clReleaseMemObject():
				ptr == (ptr_t) ::clSetMemObjectDestructorCallback ?
				   CLFunction::clSetMemObjectDestructorCallback():

				ptr == (ptr_t) ::clCreateSamplerWithProperties ?
				   CLFunction::clCreateSamplerWithProperties():
				ptr == (ptr_t) ::clRetainSampler ?
				   CLFunction::clRetainSampler():
				ptr == (ptr_t) ::clReleaseSampler ?
				   CLFunction::clReleaseSampler():
				ptr == (ptr_t) ::clGetSamplerInfo ?
				   CLFunction::clGetSamplerInfo():

				ptr == (ptr_t) ::clCreateProgramWithSource ?
				   CLFunction::clCreateProgramWithSource():
				ptr == (ptr_t) ::clCreateProgramWithBinary ?
				   CLFunction::clCreateProgramWithBinary():
				ptr == (ptr_t) ::clCreateProgramWithBuiltInKernels ?
				   CLFunction::clCreateProgramWithBuiltInKernels():
				ptr == (ptr_t) ::clRetainProgram ?
				   CLFunction::clRetainProgram():
				ptr == (ptr_t) ::clReleaseProgram ?
				   CLFunction::clReleaseProgram():
				ptr == (ptr_t) ::clBuildProgram ?
				   CLFunction::clBuildProgram():
				ptr == (ptr_t) ::clCompileProgram ?
				   CLFunction::clCompileProgram():
				ptr == (ptr_t) ::clLinkProgram ?
				   CLFunction::clLinkProgram():
				ptr == (ptr_t) ::clUnloadPlatformCompiler ?
				   CLFunction::clUnloadPlatformCompiler():
				ptr == (ptr_t) ::clGetProgramInfo ?
				   CLFunction::clGetProgramInfo():
				ptr == (ptr_t) ::clGetProgramBuildInfo ?
				   CLFunction::clGetProgramBuildInfo():

				ptr == (ptr_t) ::clCreateKernel ?
				   CLFunction::clCreateKernel():
				ptr == (ptr_t) ::clCreateKernelsInProgram ?
				   CLFunction::clCreateKernelsInProgram():
				ptr == (ptr_t) ::clGetKernelInfo ?
				   CLFunction::clGetKernelInfo():
				ptr == (ptr_t) ::clGetKernelArgInfo ?
				   CLFunction::clGetKernelArgInfo():
				ptr == (ptr_t) ::clGetKernelWorkGroupInfo ?
				   CLFunction::clGetKernelWorkGroupInfo():
				ptr == (ptr_t) ::clRetainKernel ?
				   CLFunction::clRetainKernel():
				ptr == (ptr_t) ::clReleaseKernel ?
				   CLFunction::clReleaseKernel():
				ptr == (ptr_t) ::clSetKernelArg ?
				   CLFunction::clSetKernelArg():
				ptr == (ptr_t) ::clSetKernelArgSVMPointer ?
				   CLFunction::clSetKernelArgSVMPointer():
				ptr == (ptr_t) ::clSetKernelExecInfo ?
				   CLFunction::clSetKernelExecInfo():

				ptr == (ptr_t) ::clEnqueueNDRangeKernel ?
				   CLFunction::clEnqueueNDRangeKernel():
				ptr == (ptr_t) ::clEnqueueNativeKernel ?
				   CLFunction::clEnqueueNativeKernel():

				ptr == (ptr_t) ::clCreateUserEvent ?
				   CLFunction::clCreateUserEvent():
				ptr == (ptr_t) ::clSetUserEventStatus ?
				   CLFunction::clSetUserEventStatus():
				ptr == (ptr_t) ::clWaitForEvents ?
				   CLFunction::clWaitForEvents():
				ptr == (ptr_t) ::clGetEventInfo ?
				   CLFunction::clGetEventInfo():
				ptr == (ptr_t) ::clSetEventCallback ?
				   CLFunction::clSetEventCallback():
				ptr == (ptr_t) ::clRetainEvent ?
				   CLFunction::clRetainEvent():
				ptr == (ptr_t) ::clReleaseEvent ?
				   CLFunction::clReleaseEvent():

				ptr == (ptr_t) ::clEnqueueMarkerWithWaitList ?
				   CLFunction::clEnqueueMarkerWithWaitList():
				ptr == (ptr_t) ::clEnqueueBarrierWithWaitList ?
				   CLFunction::clEnqueueBarrierWithWaitList():

				ptr == (ptr_t) ::clGetEventProfilingInfo ?
				   CLFunction::clGetEventProfilingInfo():
				ptr == (ptr_t) ::clFlush ?
				   CLFunction::clFlush():
				ptr == (ptr_t) ::clFinish ?
				   CLFunction::clFinish():

				ptr == (ptr_t) ::clCreatePipe ?
				   CLFunction::clCreatePipe():
				ptr == (ptr_t) ::clGetPipeInfo ?
				   CLFunction::clGetPipeInfo():

				ptr == (ptr_t) ::clSVMAlloc ?
				   CLFunction::clSVMAlloc():
				ptr == (ptr_t) ::clSVMFree ?
				   CLFunction::clSVMFree():
				ptr == (ptr_t) ::clEnqueueSVMFree ?
				   CLFunction::clEnqueueSVMFree():
				ptr == (ptr_t) ::clEnqueueSVMMemcpy ?
				   CLFunction::clEnqueueSVMMemcpy():
				ptr == (ptr_t) ::clEnqueueSVMMemFill ?
				   CLFunction::clEnqueueSVMMemFill():
				ptr == (ptr_t) ::clEnqueueSVMMap ?
				   CLFunction::clEnqueueSVMMap():
				ptr == (ptr_t) ::clEnqueueSVMUnmap ?
				   CLFunction::clEnqueueSVMUnmap():
				   CLFunction::unknown();
		}

		auto CLFunction::getCLName() const -> std::experimental::string_view const& {
			return m_name;
		}
	}
}

#endif
