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

				equals(::clCreateSubDevices) ?
				    clf::clCreateSubDevices():
				equals(::clRetainDevice) ?
				    clf::clRetainDevice():
				equals(::clReleaseDevice) ?
				    clf::clReleaseDevice():

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

				equals(::clCreateCommandQueueWithProperties) ?
				    clf::clCreateCommandQueueWithProperties():
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
				equals(::clEnqueueFillBuffer) ?
				    clf::clEnqueueFillBuffer():
				equals(::clEnqueueMapBuffer) ?
				    clf::clEnqueueMapBuffer():

				equals(::clCreateImage) ?
				    clf::clCreateImage():
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
				equals(::clEnqueueFillImage) ?
				    clf::clEnqueueFillImage():
				equals(::clEnqueueMapImage) ?
				    clf::clEnqueueMapImage():

				equals(::clEnqueueUnmapMemObject) ?
				    clf::clEnqueueUnmapMemObject():
				equals(::clEnqueueMigrateMemObjects) ?
				    clf::clEnqueueMigrateMemObjects():
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

				equals(::clCreateSamplerWithProperties) ?
				    clf::clCreateSamplerWithProperties():
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
				equals(::clCreateProgramWithBuiltInKernels) ?
				    clf::clCreateProgramWithBuiltInKernels():
				equals(::clRetainProgram) ?
				    clf::clRetainProgram():
				equals(::clReleaseProgram) ?
				    clf::clReleaseProgram():
				equals(::clBuildProgram) ?
				    clf::clBuildProgram():
				equals(::clCompileProgram) ?
				    clf::clCompileProgram():
				equals(::clLinkProgram) ?
				    clf::clLinkProgram():
				equals(::clUnloadPlatformCompiler) ?
				    clf::clUnloadPlatformCompiler():
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
				equals(::clGetKernelArgInfo) ?
				    clf::clGetKernelArgInfo():
				equals(::clGetKernelWorkGroupInfo) ?
				    clf::clGetKernelWorkGroupInfo():
				equals(::clRetainKernel) ?
				    clf::clRetainKernel():
				equals(::clReleaseKernel) ?
				    clf::clReleaseKernel():
				equals(::clSetKernelArg) ?
				    clf::clSetKernelArg():
				equals(::clSetKernelArgSVMPointer) ?
				    clf::clSetKernelArgSVMPointer():
				equals(::clSetKernelExecInfo) ?
				    clf::clSetKernelExecInfo():

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

				equals(::clEnqueueMarkerWithWaitList) ?
				    clf::clEnqueueMarkerWithWaitList():
				equals(::clEnqueueBarrierWithWaitList) ?
				    clf::clEnqueueBarrierWithWaitList():

				equals(::clGetEventProfilingInfo) ?
				    clf::clGetEventProfilingInfo():
				equals(::clFlush) ?
				    clf::clFlush():
				equals(::clFinish) ?
				    clf::clFinish():

				equals(::clCreatePipe) ?
				    clf::clCreatePipe():
				equals(::clGetPipeInfo) ?
				    clf::clGetPipeInfo():

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

				    clf::unknown(); // default case
		}

		auto CLFunction::getCLName() const -> std::experimental::string_view const& {
			return m_name;
		}
	}
}

#endif
