#ifndef CLPP_PROGRAM_HPP
#define CLPP_PROGRAM_HPP

#include "clpp/kernel.hpp"
#include "clpp/build_status.hpp"
#include "clpp/binary_type.hpp"

namespace cl {
	namespace detail {
		template<>
		struct ObjectHandler<cl_program> final {
			using cl_type        = cl_program;
			using info_type      = cl_program_info;

			static constexpr auto retain  = clRetainProgram;
			static constexpr auto release = clReleaseProgram;
			static constexpr auto getInfo = clGetProgramInfo;
		};
	}

	class Context;

	class Program final : public detail::Object<cl_program> {
		//================================================================================
		// Constructor and Assignment
		//================================================================================
	public:

		using detail::Object<cl_type>::Object;

		auto inline operator=(Program const& rhs) -> Program&;

		//================================================================================
		// Wrapper API for creating Kernel objects
		//================================================================================
	public:

		auto inline createKernel(std::string const& name) const -> Kernel;
		auto inline createAllKernels() const                    -> std::vector<Kernel>;

		//================================================================================
		// Wrapper API for clBuildProgram
		//================================================================================
	public:

		void inline
		build(Device const& device) const;

		void inline
		build(Device const& device, std::string const& options) const;

		template<typename DeviceRange>
		void build(
			DeviceRange const& devices
		) const;

		template<typename DeviceRange>
		void build(
			DeviceRange const& devices,
			std::string const& options
		) const;

		template<typename DeviceIterator>
		void build(
			DeviceIterator firstDevice,
			DeviceIterator lastDevice
		) const;

		template<typename DeviceIterator>
		void build(
			DeviceIterator firstDevice,
			DeviceIterator lastDevice,
			std::string const& options
		) const;

		//================================================================================
		// Information access helper methods.
		//================================================================================
	private:
		template<typename T>
		auto getBuildInfo(
			Device const& device, cl_program_build_info info
		) const -> T;

		template<typename T>
		auto getBuildInfoVector(
			Device const& device, cl_program_build_info info
		) const -> std::vector<T>;

		auto inline getBuildInfoString(
			Device const& device, cl_program_build_info info
		) const -> std::string;

	public:

		auto inline getReferenceCount() const -> cl_uint;
		auto inline getContext() const        -> Context;
		auto inline getNumDevices() const     -> cl_uint;
		auto inline getDevices() const        -> std::vector<Device>;
		auto inline getProgramSource() const  -> std::string;
		auto inline getBinarySizes() const    -> std::vector<size_t>;

		// auto inline getBinarySizes() const -> std::unordered_map<Device, size_t>;
		// auto inline getBinaries() const       -> std::unordered_map<Device, std::vector<unsigned char>>;

	#if defined(CL_VERSION_1_2)
		auto inline getNumKernels() const     -> cl_uint;
		auto inline getKernelNames() const    -> std::vector<std::string>;
	#endif // defined(CL_VERSION_1_2)

		//================================================================================
		// Information access helper methods for build.
		//================================================================================
	public:

		auto inline getBuildStatus(Device const& device) const  -> BuildStatus;
		auto inline getBuildOptions(Device const& device) const -> std::string;
		auto inline getBuildLog(Device const& device) const     -> std::string;

	#if defined(CL_VERSION_1_2)
		auto inline getBinaryType(Device const& device) const   -> BinaryType;
	#endif // defined(CL_VERSION_1_2)

	#if defined(CL_VERSION_2_0)
		auto inline getBuildGlobalVariableTotalSize(Device const& device) const -> size_t;
	#endif // defined(CL_VERSION_2_0)
	};
}

#endif
