#pragma OPENCL EXTENSION cl_khr_fp64 : enable

__kernel void vectorAdd(
	__global int* bufferA,
	__global int* bufferB,
	__global int* result,
	const unsigned int size
){
	size_t id = get_global_id(0);
	if (id < size) {
		result[id] = bufferA[id] + bufferB[id];
	}
}
