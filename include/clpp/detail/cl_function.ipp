#ifdef  CLPP_DETAIL_CL_FUNCTION_IPP
	#error "multiple inclusions of the same implementation file"
#else
#define CLPP_DETAIL_CL_FUNCTION_IPP

#ifndef CLPP_DETAIL_CL_FUNCTION_HPP
	#error "header file has not been included; maybe it isn't required anymore ?"
	#include "clpp/detail/cl_function.hpp"
#endif

#include <utility>
#include <cstdint>

namespace cl {
	namespace detail {
		CLFunction::CLFunction(std::experimental::string_view name):
			m_name{std::move(name)}
		{}

		template<typename CLFunctionPtr>
		auto CLFunction::getByPtr(CLFunctionPtr fp) -> CLFunction const& {
			using clf   = CLFunction;
			const auto equals = [fp](auto other) {
				return fp == reinterpret_cast<decltype(fp)>(other);
			};
			return
				equals(::clGetPlatformIDs) ?
				    clf::clGetPlatformIDs():
				equals(::clGetPlatformInfo) ?
				    clf::clGetPlatformInfo():

				equals(::clGetDeviceIDs) ?
				    clf::clGetDeviceIDs():
				equals(::clGetDeviceInfo) ?
				    clf::clGetDeviceInfo():

			#if defined(CL_VERSION_1_2)
				equals(::clCreateSubDevices) ?
				    clf::clCreateSubDevices():
				equals(::clRetainDevice) ?
				    clf::clRetainDevice():
				equals(::clReleaseDevice) ?
				    clf::clReleaseDevice():
			#endif // defined(CL_VERSION_1_2)

				equals(::clCreateContext) ?
				    clf::clCreateContext():
				equals(::clCreateContextFromType) ?
				    clf::clCreateContextFromType():
				equals(::clRetainContext) ?
				    clf::clRetainContext():
				equals(::clReleaseContext) ?
				    clf::clReleaseContext():
				equals(::clGetContextInfo) ?
				    clf::clGetContextInfo():

			#if defined(CL_VERSION_2_0)
				equals(::clCreateCommandQueueWithProperties) ?
				    clf::clCreateCommandQueueWithProperties():
			#else
				equals(::clCreateCommandQueue) ?
				    clf::clCreateCommandQueue():
			#endif // defined(CL_VERSION_2_0)
				equals(::clRetainCommandQueue) ?
				    clf::clRetainCommandQueue():
				equals(::clReleaseCommandQueue) ?
				    clf::clReleaseCommandQueue():
				equals(::clGetCommandQueueInfo) ?
				    clf::clGetCommandQueueInfo():

				equals(::clCreateBuffer) ?
				    clf::clCreateBuffer():
				equals(::clCreateSubBuffer) ?
				    clf::clCreateSubBuffer():
				equals(::clEnqueueReadBuffer) ?
				    clf::clEnqueueReadBuffer():
				equals(::clEnqueueWriteBuffer) ?
				    clf::clEnqueueWriteBuffer():
				equals(::clEnqueueReadBufferRect) ?
				    clf::clEnqueueReadBufferRect():
				equals(::clEnqueueWriteBufferRect) ?
				    clf::clEnqueueWriteBufferRect():
				equals(::clEnqueueCopyBuffer) ?
				    clf::clEnqueueCopyBuffer():
				equals(::clEnqueueCopyBufferRect) ?
				    clf::clEnqueueCopyBufferRect():
			#if defined(CL_VERSION_1_2)
				equals(::clEnqueueFillBuffer) ?
				    clf::clEnqueueFillBuffer():
			#endif // defined(CL_VERSION_1_2)
				equals(::clEnqueueMapBuffer) ?
				    clf::clEnqueueMapBuffer():

			#if defined(CL_VERSION_1_2)
				equals(::clCreateImage) ?
				    clf::clCreateImage():
			#else
				equals(::clCreateImage2D) ?
				    clf::clCreateImage2D():
				equals(::clCreateImage3D) ?
				    clf::clCreateImage3D():
			#endif // defined(CL_VERSION_1_2)

				equals(::clGetSupportedImageFormats) ?
				    clf::clGetSupportedImageFormats():
				equals(::clEnqueueReadImage) ?
				    clf::clEnqueueReadImage():
				equals(::clEnqueueWriteImage) ?
				    clf::clEnqueueWriteImage():
				equals(::clEnqueueCopyImage) ?
				    clf::clEnqueueCopyImage():
				equals(::clEnqueueCopyImageToBuffer) ?
				    clf::clEnqueueCopyImageToBuffer():
				equals(::clEnqueueCopyBufferToImage) ?
				    clf::clEnqueueCopyBufferToImage():
			#if defined(CL_VERSION_1_2)
				equals(::clEnqueueFillImage) ?
				    clf::clEnqueueFillImage():
			#endif // defined(CL_VERSION_1_2)
				equals(::clEnqueueMapImage) ?
				    clf::clEnqueueMapImage():

				equals(::clEnqueueUnmapMemObject) ?
				    clf::clEnqueueUnmapMemObject():
			#if defined(CL_VERSION_1_2)
				equals(::clEnqueueMigrateMemObjects) ?
				    clf::clEnqueueMigrateMemObjects():
			#endif // defined(CL_VERSION_1_2)
				equals(::clGetImageInfo) ?
				    clf::clGetImageInfo():
				equals(::clGetMemObjectInfo) ?
				    clf::clGetMemObjectInfo():
				equals(::clRetainMemObject) ?
				    clf::clRetainMemObject():
				equals(::clReleaseMemObject) ?
				    clf::clReleaseMemObject():
				equals(::clSetMemObjectDestructorCallback) ?
				    clf::clSetMemObjectDestructorCallback():

			#if defined(CL_VERSION_2_0)
				equals(::clCreateSamplerWithProperties) ?
				    clf::clCreateSamplerWithProperties():
			#else
				equals(::clCreateSampler) ?
				    clf::clCreateSampler():
			#endif // defined(CL_VERSION_2_0)
				equals(::clRetainSampler) ?
				    clf::clRetainSampler():
				equals(::clReleaseSampler) ?
				    clf::clReleaseSampler():
				equals(::clGetSamplerInfo) ?
				    clf::clGetSamplerInfo():

				equals(::clCreateProgramWithSource) ?
				    clf::clCreateProgramWithSource():
				equals(::clCreateProgramWithBinary) ?
				    clf::clCreateProgramWithBinary():
			#if defined(CL_VERSION_1_2)
				equals(::clCreateProgramWithBuiltInKernels) ?
				    clf::clCreateProgramWithBuiltInKernels():
			#endif // defined(CL_VERSION_1_2)
				equals(::clRetainProgram) ?
				    clf::clRetainProgram():
				equals(::clReleaseProgram) ?
				    clf::clReleaseProgram():
				equals(::clBuildProgram) ?
				    clf::clBuildProgram():
			#if defined(CL_VERSION_1_2)
				equals(::clCompileProgram) ?
				    clf::clCompileProgram():
				equals(::clLinkProgram) ?
				    clf::clLinkProgram():
			#endif // defined(CL_VERSION_1_2)
			#if defined(CL_VERSION_2_0)
				equals(::clUnloadPlatformCompiler) ?
				    clf::clUnloadPlatformCompiler():
			#endif // defined(CL_VERSION_2_0)
				equals(::clGetProgramInfo) ?
				    clf::clGetProgramInfo():
				equals(::clGetProgramBuildInfo) ?
				    clf::clGetProgramBuildInfo():

				equals(::clCreateKernel) ?
				    clf::clCreateKernel():
				equals(::clCreateKernelsInProgram) ?
				    clf::clCreateKernelsInProgram():
				equals(::clGetKernelInfo) ?
				    clf::clGetKernelInfo():
			#if defined(CL_VERSION_1_2)
				equals(::clGetKernelArgInfo) ?
				    clf::clGetKernelArgInfo():
			#endif // defined(CL_VERSION_1_2)
				equals(::clGetKernelWorkGroupInfo) ?
				    clf::clGetKernelWorkGroupInfo():
				equals(::clRetainKernel) ?
				    clf::clRetainKernel():
				equals(::clReleaseKernel) ?
				    clf::clReleaseKernel():
				equals(::clSetKernelArg) ?
				    clf::clSetKernelArg():
			#if defined(CL_VERSION_2_0)
				equals(::clSetKernelArgSVMPointer) ?
				    clf::clSetKernelArgSVMPointer():
				equals(::clSetKernelExecInfo) ?
				    clf::clSetKernelExecInfo():
			#endif // defined(CL_VERSION_2_0)

				equals(::clEnqueueNDRangeKernel) ?
				    clf::clEnqueueNDRangeKernel():
				equals(::clEnqueueNativeKernel) ?
				    clf::clEnqueueNativeKernel():

				equals(::clCreateUserEvent) ?
				    clf::clCreateUserEvent():
				equals(::clSetUserEventStatus) ?
				    clf::clSetUserEventStatus():
				equals(::clWaitForEvents) ?
				    clf::clWaitForEvents():
				equals(::clGetEventInfo) ?
				    clf::clGetEventInfo():
				equals(::clSetEventCallback) ?
				    clf::clSetEventCallback():
				equals(::clRetainEvent) ?
				    clf::clRetainEvent():
				equals(::clReleaseEvent) ?
				    clf::clReleaseEvent():

			#if defined(CL_VERSION_1_2)
				equals(::clEnqueueMarkerWithWaitList) ?
				    clf::clEnqueueMarkerWithWaitList():
				equals(::clEnqueueBarrierWithWaitList) ?
				    clf::clEnqueueBarrierWithWaitList():
			#else
				equals(::clEnqueueMarker) ?
				    clf::clEnqueueMarker():
				equals(::clEnqueueBarrier) ?
				    clf::clEnqueueBarrier():
				equals(::clEnqueueWaitForEvents) ?
				    clf::clEnqueueWaitForEvents():
			#endif // defined(CL_VERSION_1_2)

				equals(::clGetEventProfilingInfo) ?
				    clf::clGetEventProfilingInfo():
				equals(::clFlush) ?
				    clf::clFlush():
				equals(::clFinish) ?
				    clf::clFinish():

			#if defined(CL_VERSION_2_0)
				equals(::clCreatePipe) ?
				    clf::clCreatePipe():
				equals(::clGetPipeInfo) ?
				    clf::clGetPipeInfo():
			#endif // defined(CL_VERSION_2_0)

			#if defined(CL_VERSION_2_0)
				equals(::clSVMAlloc) ?
				    clf::clSVMAlloc():
				equals(::clSVMFree) ?
				    clf::clSVMFree():
				equals(::clEnqueueSVMFree) ?
				    clf::clEnqueueSVMFree():
				equals(::clEnqueueSVMMemcpy) ?
				    clf::clEnqueueSVMMemcpy():
				equals(::clEnqueueSVMMemFill) ?
				    clf::clEnqueueSVMMemFill():
				equals(::clEnqueueSVMMap) ?
				    clf::clEnqueueSVMMap():
				equals(::clEnqueueSVMUnmap) ?
				    clf::clEnqueueSVMUnmap():
			#endif // defined(CL_VERSION_2_0)

				    clf::unknown(); // default case
		}

		auto CLFunction::getCLName() const -> std::experimental::string_view const& {
			return m_name;
		}
	}
}

#endif
