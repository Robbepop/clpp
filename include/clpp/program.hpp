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

			static auto release(cl_type id) { return clReleaseProgram(id); }

			static auto retain(cl_type id) { return clRetainProgram(id); }

			static auto getInfo(
				cl_type   program,
				info_type param_name,
				size_t    param_value_size,
				void *    param_value,
				size_t *  param_value_size_ret
			) {
				return clGetProgramInfo(
					program, param_name, param_value_size, param_value, param_value_size_ret);
			}
		};
	}

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

		void build(Device const& device) const;

		template<typename DeviceRange>
		void build(
			DeviceRange const& devices
		) const;

		template<typename DeviceIterator>
		void build(
			DeviceIterator firstDevice,
			DeviceIterator lastDevice
		) const;

		template<typename Function, typename T>
		void build(
			Device const& device,
			Function callback, T&& data
		) const;

		template<typename DeviceRange, typename Function, typename T>
		void build(
			DeviceRange const& devices,
			Function callback, T&& data
		) const;

		template<typename DeviceIterator, typename Function, typename T>
		void build(
			DeviceIterator firstDevice,
			DeviceIterator lastDevice,
			Function callback, T&& data
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

		auto getBuildInfoString(
			Device const& device, cl_program_build_info info
		) const -> std::string;

	public:

		auto getReferenceCount() const -> cl_uint;
		auto getContext() const        -> std::unique_ptr<Context>;
		auto getNumDevices() const     -> cl_uint;
		auto getDevices() const        -> std::vector<Device>;
		auto getProgramSource() const  -> std::string;
		auto getBinarySizes() const    -> std::vector<size_t>;
//		auto getBinaries() const       -> std::vector<std::vector<unsigned char>>;
		auto getNumKernels() const     -> cl_uint;
		auto getKernelNames() const    -> std::vector<std::string>;

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

#endif
