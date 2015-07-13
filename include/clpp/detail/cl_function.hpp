#ifndef CLPP_DETAIL_CL_FUNCTION_HPP
#define CLPP_DETAIL_CL_FUNCTION_HPP

#include <string>
#include <experimental/string_view>

namespace cl {
	namespace detail {
		class CLFunction final {
		private:
			CLFunction(std::experimental::string_view name);

		public:
			template<typename CLFunctionPtr>
			static inline auto getByPtr(CLFunctionPtr ptr) -> CLFunction const&;

			inline auto getCLName() const -> std::experimental::string_view const&;

			#define CLPP_FUNC_GETTER(funcName) \
				static inline auto funcName() -> CLFunction const& { \
					static const auto instance = CLFunction{#funcName}; \
					return instance; \
				}

			CLPP_FUNC_GETTER(unknown);

			CLPP_FUNC_GETTER(clGetPlatformIDs);
			CLPP_FUNC_GETTER(clGetPlatformInfo);
			CLPP_FUNC_GETTER(clGetDeviceIDs);
			CLPP_FUNC_GETTER(clGetDeviceInfo);
			CLPP_FUNC_GETTER(clCreateSubDevices);
		#if defined(CL_VERSION_1_2)
			CLPP_FUNC_GETTER(clRetainDevice);
			CLPP_FUNC_GETTER(clReleaseDevice);
		#endif // defined(CL_VERSION_1_2)

			CLPP_FUNC_GETTER(clCreateContext);
			CLPP_FUNC_GETTER(clCreateContextFromType);
			CLPP_FUNC_GETTER(clRetainContext);
			CLPP_FUNC_GETTER(clReleaseContext);
			CLPP_FUNC_GETTER(clGetContextInfo);

		#if defined(CL_VERSION_2_0)
			CLPP_FUNC_GETTER(clCreateCommandQueueWithProperties);
		#else
			CLPP_FUNC_GETTER(clCreateCommandQueue);
		#endif // defined(CL_VERSION_2_0)
			CLPP_FUNC_GETTER(clRetainCommandQueue);
			CLPP_FUNC_GETTER(clReleaseCommandQueue);
			CLPP_FUNC_GETTER(clGetCommandQueueInfo);

			CLPP_FUNC_GETTER(clCreateBuffer);
			CLPP_FUNC_GETTER(clCreateSubBuffer);
			CLPP_FUNC_GETTER(clEnqueueReadBuffer);
			CLPP_FUNC_GETTER(clEnqueueWriteBuffer);
			CLPP_FUNC_GETTER(clEnqueueReadBufferRect);
			CLPP_FUNC_GETTER(clEnqueueWriteBufferRect);
			CLPP_FUNC_GETTER(clEnqueueCopyBuffer);
			CLPP_FUNC_GETTER(clEnqueueCopyBufferRect);
			CLPP_FUNC_GETTER(clEnqueueFillBuffer);
			CLPP_FUNC_GETTER(clEnqueueMapBuffer);

			CLPP_FUNC_GETTER(clCreateImage);
			CLPP_FUNC_GETTER(clGetSupportedImageFormats);
			CLPP_FUNC_GETTER(clEnqueueReadImage);
			CLPP_FUNC_GETTER(clEnqueueWriteImage);
			CLPP_FUNC_GETTER(clEnqueueCopyImage);
			CLPP_FUNC_GETTER(clEnqueueCopyImageToBuffer);
			CLPP_FUNC_GETTER(clEnqueueCopyBufferToImage);
			CLPP_FUNC_GETTER(clEnqueueFillImage);
			CLPP_FUNC_GETTER(clEnqueueMapImage);

			CLPP_FUNC_GETTER(clEnqueueUnmapMemObject);
		#if defined(CL_VERSION_1_2)
			CLPP_FUNC_GETTER(clEnqueueMigrateMemObjects);
		#endif
			CLPP_FUNC_GETTER(clGetImageInfo);
			CLPP_FUNC_GETTER(clGetMemObjectInfo);
			CLPP_FUNC_GETTER(clRetainMemObject);
			CLPP_FUNC_GETTER(clReleaseMemObject);
			CLPP_FUNC_GETTER(clSetMemObjectDestructorCallback);

			CLPP_FUNC_GETTER(clCreateSamplerWithProperties);
			CLPP_FUNC_GETTER(clRetainSampler);
			CLPP_FUNC_GETTER(clReleaseSampler);
			CLPP_FUNC_GETTER(clGetSamplerInfo);

			CLPP_FUNC_GETTER(clCreateProgramWithSource);
			CLPP_FUNC_GETTER(clCreateProgramWithBinary);
			CLPP_FUNC_GETTER(clCreateProgramWithBuiltInKernels);
			CLPP_FUNC_GETTER(clRetainProgram);
			CLPP_FUNC_GETTER(clReleaseProgram);
			CLPP_FUNC_GETTER(clBuildProgram);
			CLPP_FUNC_GETTER(clCompileProgram);
			CLPP_FUNC_GETTER(clLinkProgram);
		#if defined(CL_VERSION_2_0)
			CLPP_FUNC_GETTER(clUnloadPlatformCompiler);
		#else
			CLPP_FUNC_GETTER(clUnloadCompiler);
		#endif
			CLPP_FUNC_GETTER(clGetProgramInfo);
			CLPP_FUNC_GETTER(clGetProgramBuildInfo);

			CLPP_FUNC_GETTER(clCreateKernel);
			CLPP_FUNC_GETTER(clCreateKernelsInProgram);
			CLPP_FUNC_GETTER(clGetKernelInfo);
			CLPP_FUNC_GETTER(clGetKernelArgInfo);
			CLPP_FUNC_GETTER(clGetKernelWorkGroupInfo);
			CLPP_FUNC_GETTER(clRetainKernel);
			CLPP_FUNC_GETTER(clReleaseKernel);
			CLPP_FUNC_GETTER(clSetKernelArg);
			CLPP_FUNC_GETTER(clSetKernelArgSVMPointer);
			CLPP_FUNC_GETTER(clSetKernelExecInfo);

			CLPP_FUNC_GETTER(clEnqueueNDRangeKernel);
			CLPP_FUNC_GETTER(clEnqueueNativeKernel);

			CLPP_FUNC_GETTER(clCreateUserEvent);
			CLPP_FUNC_GETTER(clSetUserEventStatus);
			CLPP_FUNC_GETTER(clWaitForEvents);
			CLPP_FUNC_GETTER(clGetEventInfo);
			CLPP_FUNC_GETTER(clSetEventCallback);
			CLPP_FUNC_GETTER(clRetainEvent);
			CLPP_FUNC_GETTER(clReleaseEvent);

		#if defined(CL_VERSION_1_2)
			CLPP_FUNC_GETTER(clEnqueueMarkerWithWaitList);
			CLPP_FUNC_GETTER(clEnqueueBarrierWithWaitList);
		#else
			CLPP_FUNC_GETTER(clEnqueueMarker);
			CLPP_FUNC_GETTER(clEnqueueBarrier);
			CLPP_FUNC_GETTER(clEnqueueWaitForEvents);
		#endif // defined(CL_VERSION_1_2)

			CLPP_FUNC_GETTER(clGetEventProfilingInfo);
			CLPP_FUNC_GETTER(clFlush);
			CLPP_FUNC_GETTER(clFinish);

			CLPP_FUNC_GETTER(clCreatePipe);
			CLPP_FUNC_GETTER(clGetPipeInfo);

			CLPP_FUNC_GETTER(clSVMAlloc);
			CLPP_FUNC_GETTER(clSVMFree);
			CLPP_FUNC_GETTER(clEnqueueSVMFree);
			CLPP_FUNC_GETTER(clEnqueueSVMMemcpy);
			CLPP_FUNC_GETTER(clEnqueueSVMMemFill);
			CLPP_FUNC_GETTER(clEnqueueSVMMap);
			CLPP_FUNC_GETTER(clEnqueueSVMUnmap);

			#undef CLPP_FUNC_GETTER

		private:
			std::experimental::string_view m_name;
		};
	}
}

#endif
