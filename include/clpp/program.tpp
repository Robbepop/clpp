#ifndef CLPP_PROGRAM_H
	#error "Do not include this file directly."
#endif

namespace cl {
	//================================================================================
	// Wrapper API for creating Kernel objects
	//================================================================================

	auto Program::createKernel(std::string const& name) const -> Kernel {
		// TODO

// cl_kernel clCreateKernel ( 	cl_program  program,
//  	const char *kernel_name,
//  	cl_int *errcode_ret)
	}

	auto Program::createAllKernels() const -> std::vector<Kernel> {
		// TODO

// cl_int clCreateKernelsInProgram ( 	cl_program  program,
//  	cl_uint num_kernels,
//  	cl_kernel *kernels,
//  	cl_uint *num_kernels_ret)
	}

	//================================================================================
	// Wrapper API for clBuildProgram
	//================================================================================

	template<typename DeviceIterator>
	void build(
		DeviceIterator firstDevice,
		DeviceIterator lastDevice,
		std::string const& options = ""
	) const {
		// TODO
	}

	template<typename DeviceIterator, typename Function, typename T>
	void build(
		DeviceIterator firstDevice,
		DeviceIterator lastDevice,
		std::string const& options,
		Function callback, T&& data
	) const {
		// TODO
	}

	// cl_int clBuildProgram ( 	cl_program program,
	//  	cl_uint num_devices,
	//  	const cl_device_id *device_list,
	//  	const char *options,
	//  	void (CL_CALLBACK *pfn_notify)(cl_program program, void *user_data),
	//  	void *user_data)

	//================================================================================
	// Wrapper API for clCompileProgram
	//================================================================================

	template<typename DeviceIterator>
	void compile(
		DeviceIterator firstDevice,
		DeviceIterator lastDevice,
		std::string const& options = ""
	) const {
		// TODO
	}

	template<typename DeviceIterator, typename Function, typename T>
	void compile(
		DeviceIterator firstDevice,
		DeviceIterator lastDevice,
		std::string const& options,
		Function callback, T&& data
	) const {
		// TODO
	}

// cl_int clCompileProgram ( 	cl_program program,
//  	cl_uint num_devices,
//  	const cl_device_id *device_list,
//  	const char *options,
//  	cl_uint num_input_headers,
//  	const cl_program *input_headers,
//  	const char **header_include_names,
//  	void (CL_CALLBACK *pfn_notify)( cl_program program, void *user_data),
//  	void *user_data)

	//================================================================================
	// Information access helper methods.
	//================================================================================

	auto getReferenceCount() const -> cl_uint {
		// TODO
	}

	auto getContext() const -> Context {
		// TODO
	}

	auto getNumDevices() const -> cl_uint {
		// TODO
	}

	auto getDevices() const -> std::vector<Device> {
		// TODO
	}

	auto getProgramSource() const -> std::string {
		// TODO
	}

	auto getBinarySize() const -> std::vector<size_t> {
		// TODO
	}

//	auto getBinaries() const -> std::vector<std::vector<unsigned char>> {
//		 TODO
//	}

	auto getNumKernels() const -> cl_uint {
		// TODO
	}

	auto getKernelNames() const -> std::vector<std::string>> {
		// TODO
	}

	//================================================================================
	// Information access helper methods for build.
	//================================================================================

	auto getBuildStatus(Device const& device) const -> BuildStatus {
		// TODO
	}

	auto getBuildOptions(Device const& device) const -> std::string {
		// TODO
	}

	auto getBuildLog(Device const& device) const -> std::string {
		// TODO
	}

	auto getBinaryType(Device const& device) const -> BinaryType {
		// TODO
	}

	auto getBuildGlobalVariableTotalSize(Device const& device) const -> size_t {
		// TODO
	}
}
