#ifndef CLPP_PROGRAM_H
#define CLPP_PROGRAM_H

namespace cl {
	class Program final : public detail::Object<cl_program> {
	public:

// cl_int clBuildProgram ( 	cl_program program,
//  	cl_uint num_devices,
//  	const cl_device_id *device_list,
//  	const char *options,
//  	void (CL_CALLBACK *pfn_notify)(cl_program program, void *user_data),
//  	void *user_data)



// cl_int clCompileProgram ( 	cl_program program,
//  	cl_uint num_devices,
//  	const cl_device_id *device_list,
//  	const char *options,
//  	cl_uint num_input_headers,
//  	const cl_program *input_headers,
//  	const char **header_include_names,
//  	void (CL_CALLBACK *pfn_notify)( cl_program program, void *user_data),
//  	void *user_data)



// cl_program clLinkProgram ( 	cl_context context,
//  	cl_uint num_devices,
//  	const cl_device_id *device_list,
//  	const char *options,
//  	cl_uint num_input_programs,
//  	const cl_program *input_programs,
//  	void (CL_CALLBACK *pfn_notify) (cl_program program, void *user_data),
//  	void *user_data,
//  	cl_int *errcode_ret)

		auto getReferenceCount() const -> cl_uint;
		auto getContext() const        -> Context;
		auto getNumDevices() const     -> cl_uint;
		auto getDevices() const        -> std::vector<Device>;
		auto getProgramSource() const  -> std::string;
		auto getBinarySize() const     -> std::vector<size_t>;
		//auto getBinaries() const       -> std::vector<std::vector<unsigned char>>;
		auto getNumKernels() const     -> cl_uint;
		auto getKernelNames() const    -> std::vector<std::string>>;

		auto getBuildStatus(Device const& device) const                  -> BuildStatus;
		auto getBuildOptions(Device const& device) const                 -> std::string;
		auto getBuildLog(Device const& device) const                     -> std::string;
		auto getBinaryType(Device const& device) const                   -> BinaryType;
		auto getBuildGlobalVariableTotalSize(Device const& device) const -> size_t;
	};
}

#endif
