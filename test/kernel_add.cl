#pragma OPENCL EXTENSION cl_khr_fp64 : enable

__kernel void vecAdd(
	__global double* bufferA,
	__global double* bufferB,
	__global double* result,
	const unsigned int size
){
	int id = get_global_id(0);
	if (id < size) {
		result[id] = bufferA[id] + bufferB[id];
	}
}
