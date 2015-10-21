#ifdef  CLPP_PROGRAM_IPP
	#error "multiple inclusions of the same implementation file"
#else
#define CLPP_PROGRAM_IPP

#ifndef CLPP_PROGRAM_HPP
	#error "header file has not been included; maybe it isn't required anymore?"
	#include "clpp/program.hpp"
#endif

#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>

namespace cl {

	auto Program::operator=(Program const& rhs) -> Program & {
		if (this != &rhs) {
		    detail::Object<cl_type>::operator=(rhs);
		}
		return *this;
	}

	//================================================================================
	// Wrapper API for creating Kernel objects
	//================================================================================

	auto Program::createKernel(std::string const& name) const -> Kernel {
		auto error = cl_int{CL_INVALID_VALUE};
		auto kernelId = clCreateKernel(get(), name.c_str(), std::addressof(error));
		detail::handleError(detail::CLFunction::clCreateKernel(), error);
		return {kernelId};
	}

	auto Program::createAllKernels() const -> std::vector<Kernel> {
		auto countKernels = cl_uint{0};
		auto error = clCreateKernelsInProgram(
			get(), 0, nullptr, std::addressof(countKernels));
		detail::handleError(detail::CLFunction::clCreateKernelsInProgram(), error);
		auto kernels = std::vector<Kernel>(countKernels);
		error = clCreateKernelsInProgram(
			get(), countKernels, reinterpret_cast<cl_kernel*>(kernels.data()), nullptr);
		detail::handleError(detail::CLFunction::clCreateKernelsInProgram(), error);
		return kernels;
	}

	//================================================================================
	// Wrapper API for clBuildProgram
	//================================================================================

	void Program::build(Device const& device) const {
		auto error = clBuildProgram(
			get(), 1u, std::addressof(device.get()), nullptr, nullptr, nullptr);
		detail::handleError(detail::CLFunction::clBuildProgram(), error);
	}

	void Program::build(Device const& device, std::string const& options) const {
		auto error = clBuildProgram(
			get(), 1u, std::addressof(device.get()), options.c_str(), nullptr, nullptr);
		detail::handleError(detail::CLFunction::clBuildProgram(), error);
	}

	template<typename DeviceRange>
	void Program::build(
		DeviceRange const& devices
	) const {
		build(devices.begin(), devices.end());
	}

	template<typename DeviceIterator>
	void Program::build(
		DeviceIterator firstDevice,
		DeviceIterator lastDevice
	) const {
		const auto deviceIt = reinterpret_cast<const cl_device_id*>(
			std::addressof(*firstDevice));
		auto error = clBuildProgram(
			get(), static_cast<cl_uint>(std::distance(firstDevice, lastDevice)), deviceIt,
			nullptr, nullptr, nullptr);
		detail::handleError(detail::CLFunction::clBuildProgram(), error);
	}

	//================================================================================
	// Information access helper methods.
	//================================================================================

	auto Program::getReferenceCount() const -> cl_uint {
		return getInfo<cl_uint>(CL_PROGRAM_REFERENCE_COUNT);
	}

	auto Program::getContext() const -> Context {
		return {getInfo<cl_context>(CL_PROGRAM_CONTEXT)};
	}

	auto Program::getNumDevices() const -> cl_uint {
		return getInfo<cl_uint>(CL_PROGRAM_NUM_DEVICES);
	}

	auto Program::getDevices() const -> std::vector<Device> {
		const auto deviceIds = getInfoVector<cl_device_id>(CL_PROGRAM_DEVICES);
		return {deviceIds.begin(), deviceIds.end()};
	}

	auto Program::getProgramSource() const -> std::string {
		return getInfoString(CL_PROGRAM_SOURCE);
	}

	auto Program::getBinarySizes() const -> std::vector<size_t> {
		return getInfoVector<size_t>(CL_PROGRAM_BINARY_SIZES);
	}

	// auto Program::getBinaries() const
	// 	-> std::unordered_map<Device, std::vector<unsigned char>>
	// {
	// 	// TODO
	// }

#if defined(CL_VERSION_1_2)
	auto Program::getNumKernels() const -> cl_uint {
		return getInfo<cl_uint>(CL_PROGRAM_NUM_KERNELS);
	}

	auto Program::getKernelNames() const -> std::vector<std::string> {
		const auto kernelNamesStr = getInfoString(CL_PROGRAM_KERNEL_NAMES);
		      auto kernelNames    = std::vector<std::string>{};
		boost::split(kernelNames, kernelNamesStr, boost::is_any_of(";"), boost::token_compress_on);
		return kernelNames;
	}
#endif // defined(CL_VERSION_1_2)

	//================================================================================
	// Information access helper methods for build.
	//================================================================================

	template<typename T>
	auto Program::getBuildInfo(
		Device const& device, cl_program_build_info infoId
	) const -> T {
		auto error = RetCode::getPreset();
		auto info  = T{};
		error = clGetProgramBuildInfo(
			get(), device.get(), infoId, sizeof(T), std::addressof(info), nullptr);
		detail::handleError(detail::CLFunction::clGetProgramBuildInfo(), error);
		return info;
	}

	template<typename T>
	auto Program::getBuildInfoVector(
		Device const& device, cl_program_build_info infoId
	) const -> std::vector<T> {
		auto error      = RetCode::getPreset();
		auto bufferSize = size_t{0};
		error = clGetProgramBuildInfo(
			get(), device.get(), infoId, 0, nullptr, std::addressof(bufferSize));
		detail::handleError(detail::CLFunction::clGetProgramBuildInfo(), error);
		auto countElems = bufferSize / sizeof(T);
		auto info = std::vector<T>(countElems);
		error = clGetProgramBuildInfo(
			get(), device.get(), infoId, bufferSize, info.data(), nullptr);
		detail::handleError(detail::CLFunction::clGetProgramBuildInfo(), error);
		return info;
	}

	auto Program::getBuildInfoString(
		Device const& device, cl_program_build_info infoId
	) const -> std::string {
		const auto info = getBuildInfoVector<char>(device, infoId);
		return {info.begin(), info.end()};
	}

	auto Program::getBuildStatus(Device const& device) const -> BuildStatus {
		return static_cast<BuildStatus>(
			getBuildInfo<cl_build_status>(device, CL_PROGRAM_BUILD_STATUS));
	}

	auto Program::getBuildOptions(Device const& device) const -> std::string {
		return getBuildInfoString(device, CL_PROGRAM_BUILD_OPTIONS);
	}

	auto Program::getBuildLog(Device const& device) const -> std::string {
		return getBuildInfoString(device, CL_PROGRAM_BUILD_LOG);
	}

#if defined(CL_VERSION_1_2)
	auto Program::getBinaryType(Device const& device) const -> BinaryType {
		return static_cast<BinaryType>(
			getBuildInfo<cl_program_binary_type>(device, CL_PROGRAM_BINARY_TYPE));
	}
#endif // defined(CL_VERSION_1_2)

#if defined(CL_VERSION_2_0)
	auto Program::getBuildGlobalVariableTotalSize(Device const& device) const -> size_t {
		return getBuildInfo<size_t>(
			device, CL_PROGRAM_BUILD_GLOBAL_VARIABLE_TOTAL_SIZE);
	}
#endif // defined(CL_VERSION_2_0)
}

#endif
