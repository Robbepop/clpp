#ifndef CLPP_PROGRAM_H
#define CLPP_PROGRAM_H

namespace cl {
	class Program final : public detail::Object<cl_program> {
		//================================================================================
		// Constructor and Assignment
		//================================================================================
	public:

		using detail::Object<cl_type>::Object;

		auto operator=(Program const& rhs) -> Program&;

		//================================================================================
		// Wrapper API for creating Kernel objects
		//================================================================================
	public:

		auto createKernel(std::string const& name) const -> Kernel;
		auto createAllKernels() const                    -> std::vector<Kernel>;

		//================================================================================
		// Wrapper API for clBuildProgram
		//================================================================================
	public:

		template<typename DeviceIterator>
		void build(
			DeviceIterator firstDevice,
			DeviceIterator lastDevice,
			std::string const& options = ""
		) const;

		template<typename DeviceIterator, typename Function, typename T>
		void build(
			DeviceIterator firstDevice,
			DeviceIterator lastDevice,
			std::string const& options,
			Function callback, T&& data
		) const;

		//================================================================================
		// Wrapper API for clCompileProgram
		//================================================================================
	public:

		template<typename DeviceIterator>
		void compile(
			DeviceIterator firstDevice,
			DeviceIterator lastDevice,
			std::string const& options = ""
		) const;

		template<typename DeviceIterator, typename Function, typename T>
		void compile(
			DeviceIterator firstDevice,
			DeviceIterator lastDevice,
			std::string const& options,
			Function callback, T&& data
		) const;

		//================================================================================
		// Information access helper methods.
		//================================================================================
	public:

		auto getReferenceCount() const -> cl_uint;
		auto getContext() const        -> Context;
		auto getNumDevices() const     -> cl_uint;
		auto getDevices() const        -> std::vector<Device>;
		auto getProgramSource() const  -> std::string;
		auto getBinarySize() const     -> std::vector<size_t>;
//		auto getBinaries() const       -> std::vector<std::vector<unsigned char>>;
		auto getNumKernels() const     -> cl_uint;
		auto getKernelNames() const    -> std::vector<std::string>>;

		//================================================================================
		// Information access helper methods for build.
		//================================================================================
	public:

		auto getBuildStatus(Device const& device) const                  -> BuildStatus;
		auto getBuildOptions(Device const& device) const                 -> std::string;
		auto getBuildLog(Device const& device) const                     -> std::string;
		auto getBinaryType(Device const& device) const                   -> BinaryType;
		auto getBuildGlobalVariableTotalSize(Device const& device) const -> size_t;
	};
}

#include "clpp/program.tpp"
#endif
