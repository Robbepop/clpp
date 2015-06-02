#include <iostream>
#include <iomanip>
#include <string>

#include "clpp.hpp"

#include <type_traits>
#include <unordered_map>
#include <map>

auto operator<<(std::ostream & os, const cl::MemoryCacheType & type) -> std::ostream & {
	switch (type) {
		case cl::MemoryCacheType::readOnlyCache:  os << "Read Only";  break;
		case cl::MemoryCacheType::readWriteCache: os << "Read/Write"; break;
		case cl::MemoryCacheType::none:           os << "None";      break;
		default: assert(false);
	}
	return os;
}

auto operator<<(std::ostream & os, const cl::LocalMemoryType & type) -> std::ostream & {
	switch (type) {
		case cl::LocalMemoryType::none:   os << "None";   break;
		case cl::LocalMemoryType::global: os << "Global"; break;
		case cl::LocalMemoryType::local:  os << "Local";  break;
		default: assert(false);
	}
	return os;
}

auto operator<<(std::ostream & os, const cl::DeviceType & type) -> std::ostream & {
	switch (type) {
		case cl::DeviceType::defaultType: os << "Default Type";   break;
		case cl::DeviceType::cpu:         os << "Compute Processing Unit (CPU)"; break;
		case cl::DeviceType::gpu:         os << "Graphical Processing Unit (GPU)";  break;
		case cl::DeviceType::accelerator: os << "Accelerator";  break;
		case cl::DeviceType::all:         os << "All Types";  break;
		default: assert(false);
	}
	return os;
}

auto operator<<(std::ostream & os, const cl::Platform & platform) -> std::ostream & {
	using std::setw;
	os << "Platform\n" << std::left
	   << setw(5) << ' ' << setw(15) << "Name"    << platform.getName()    << '\n'
	   << setw(5) << ' ' << setw(15) << "Profile" << platform.getProfile() << '\n'
	   << setw(5) << ' ' << setw(15) << "Vendor"  << platform.getVendor()  << '\n'
	   << setw(5) << ' ' << setw(15) << "Version" << platform.getVersion() << '\n'
	   << setw(5) << ' '             << "Extensions:\n";
	for (auto&& ext : platform.getExtensions()) {
		os << setw(10) << ' ' << ext << '\n';
	}
	return os;
}

template <typename T>
auto operator<<(std::ostream& out, const std::vector<T>& v) -> std::ostream & {
	if (!v.empty()) {
		out << '[';
		std::copy(v.begin(), v.end(), std::ostream_iterator<T>(out, ", "));
		out << "\b\b]";
	}
	return out;
}

namespace test {
	struct tabular {
		static constexpr auto off = "\n     ";
		tabular(int offset, int width): m_offset{offset}, m_width{width} {}
		auto getWidth() const -> int { return m_width; }
		auto getOffset() const -> int { return m_offset; }
		auto operator()(int scaledOffset, int newWidth = 0) -> tabular {
			return tabular{scaledOffset * m_offset, newWidth};
		}
	private:
		int m_offset;
		int m_width;
	};
}

auto operator<<(std::ostream & os, const test::tabular & tab) -> std::ostream & {
	os << '\n' << std::setw(tab.getOffset()) << ' ' << std::setw(tab.getWidth());
	return os;
}

namespace cast {
	template<typename T, typename V>
	auto to(const V & value) -> T {
		return static_cast<T>(value);
	}

	template<typename T, typename V>
	auto as(const V & value) -> T {
		return reinterpret_cast<T>(value);
	}
}

auto operator<<(std::ostream & os, const cl::Device & device) -> std::ostream & {
	using cast::to;
	using cast::as;
	using std::setw;
	auto tab = test::tabular{5, 35};
	os << "Device" << std::left << std::boolalpha
	   << tab << "Name"                     << device.getName()
	   << tab << "Available"                << to<bool>(device.isAvailable())
	   << tab << "Compiler available"       << to<bool>(device.isCompilerAvailable())
	   << tab << "Address bits"             << device.getAddressBits()
	   << tab << "Little Endian"            << to<bool>(device.isLittleEndian())
	   << tab << "Linker Available"         << to<bool>(device.isLinkerAvailable())
	   << tab << "Error Correction Support" << to<bool>(device.hasErrorCorrectionSupport())

	   << '\n'

	   << tab << "Global Memory Cache Size"     << device.getGlobalMemoryCacheSize()
	   << tab << "Global Memory Cache Type"     << device.getGlobalMemoryCacheType()
	   << tab << "Global Memory Cacheline Size" << device.getGlobalMemoryCachelineSize()
	   << tab << "Global Memory Size"           << device.getGlobalMemorySize()
	   << tab << "Global Var. Pref. Total Size" << device.getGlobalVariablePreferredTotalSize()
	   << tab << "Max Workt Item Sizes"         << device.getMaxWorkItemSizes()

	   << '\n'

	   << tab << "Image2D Max Height" << device.getImage2DMaxHeight()
	   << tab << "Image2D Max Width"  << device.getImage2DMaxWidth()
	   << tab << "Image3D Max Height" << device.getImage3DMaxHeight()
	   << tab << "Image3D Max Width"  << device.getImage3DMaxWidth()
	   << tab << "Image3D Max Depth"  << device.getImage3DMaxDepth()

	   << '\n'

	   << tab << "Image Base Address Alignment" << device.getImageBaseAddressAlignment()
	   << tab << "Image Max Array Size"         << device.getImageMaxArraySize()
	   << tab << "Image Max Buffer Size"        << device.getImageMaxBufferSize()
	   << tab << "Image Pitch Alignment"        << device.getImagePitchAlignment()
	   << tab << "Image Support"                << to<bool>(device.hasImageSupport())

	   << '\n'

	   << tab << "Linker Available"  << to<bool>(device.isLinkerAvailable())
	   << tab << "Local Memory Size" << device.getLocalMemorySize()
	   << tab << "Local Memory Type" << device.getLocalMemoryType()

	   << '\n'

	   << tab << "Max Clock Frequency"        << device.getMaxClockFrequency()
	   << tab << "Max Compute Units"          << device.getMaxComputeUnits()
	   << tab << "Max Constant Args"          << device.getMaxConstantArgs()
	   << tab << "Max Constant Buffer Size"   << device.getMaxConstantBufferSize()
	   << tab << "Max Global Variable Size"   << device.getMaxGlobalVariableSize()
	   << tab << "Max Memory Allocation Size" << device.getMaxMemoryAllocationSize()
	   << tab << "Max On Device Events"       << device.getMaxOnDeviceEvents()
	   << tab << "Max On Device Queues"       << device.getMaxOnDeviceQueues()
	   << tab << "Max Parameter Size"         << device.getMaxParameterSize()
	   << tab << "Max Pipe Args"              << device.getMaxPipeArgs()
	   << tab << "Max Read Image Args"        << device.getMaxReadImageArgs()
	   << tab << "Max Read Write Image Args"  << device.getMaxReadWriteImageArgs()
	   << tab << "Max Samplers"               << device.getMaxSamplers()
	   << tab << "Max Work Group Size"        << device.getMaxWorkGroupSize()
	   << tab << "Max Work Item Dimensions"   << device.getMaxWorkItemDimensions()
	   << tab << "Max Work Item Sizes"        << device.getMaxWorkItemSizes()
	   << tab << "Max Write Image Args"       << device.getMaxWriteImageArgs()

	   << tab << "Memory Base Address Align" << device.getMemoryBaseAddressAlign()
	   << tab << "Name" << device.getName()

	   << '\n'

	   << tab << "Native Vector Width (char)"   << device.getNativeVectorWidth(cl::ScalarType::charType)
	   << tab << "Native Vector Width (short)"  << device.getNativeVectorWidth(cl::ScalarType::shortType)
	   << tab << "Native Vector Width (int)"    << device.getNativeVectorWidth(cl::ScalarType::intType)
	   << tab << "Native Vector Width (long)"   << device.getNativeVectorWidth(cl::ScalarType::longType)
	   << tab << "Native Vector Width (half)"   << device.getNativeVectorWidth(cl::ScalarType::halfType)
	   << tab << "Native Vector Width (float)"  << device.getNativeVectorWidth(cl::ScalarType::floatType)
	   << tab << "Native Vector Width (double)" << device.getNativeVectorWidth(cl::ScalarType::doubleType)

	   << '\n'

	   << tab << "OpenCL C Version"          << device.getOpenCLCVersion()
	   << tab << "Has Parent Device"         << to<bool>(device.getParentDevice())
	   //<< tab << "Partition Affinity Domain" << device.getPartitionAffinityDomain()
	   << tab << "Partition Max Sub Devices" << device.getPartitionMaxSubDevices()
	   //<< tab << "Partition Properties"      << device.getPartitionProperties()
	   //<< tab << "Partition Type"            << device.getPartition()

	   << '\n'

	   << tab << "Pipe Max Active Reservations" << device.getPipeMaxActiveReservations()
	   << tab << "Pipe Max Packet Size"         << device.getPipeMaxPacketSize()

	   << tab << "Platform"                        << device.getPlatform().getName()
	   << tab << "Pref. Global Atomic Alignment"   << device.getPreferredGlobalAtomicAlignment()
	   << tab << "Pref. Local Atomic Alignment"    << device.getPreferredLocalAtomicAlignment()
	   << tab << "Pref. Platform Atomic Alignment" << device.getPreferredPlatformAtomicAlignment()

	   << '\n'

	   << tab << "Pref. Vector Width (char)"   << device.getPreferredVectorWidth(cl::ScalarType::charType)
	   << tab << "Pref. Vector Width (short)"  << device.getPreferredVectorWidth(cl::ScalarType::shortType)
	   << tab << "Pref. Vector Width (int)"    << device.getPreferredVectorWidth(cl::ScalarType::intType)
	   << tab << "Pref. Vector Width (long)"   << device.getPreferredVectorWidth(cl::ScalarType::longType)
	   << tab << "Pref. Vector Width (half)"   << device.getPreferredVectorWidth(cl::ScalarType::halfType)
	   << tab << "Pref. Vector Width (float)"  << device.getPreferredVectorWidth(cl::ScalarType::floatType)
	   << tab << "Pref. Vector Width (double)" << device.getPreferredVectorWidth(cl::ScalarType::doubleType)

	   << tab << "Print Buffer Size"          << device.getPrintfBufferSize()
	   << tab << "Profile"                    << device.getProfile()
	   << tab << "Profiling Timer Resolution" << device.getProfilingTimerResolution()

	   << '\n'

	   << tab << "Queue on Device Max Size"   << device.getQueueOnDeviceMaxSize()
	   << tab << "Queue on Device Pref. Size" << device.getQueueOnDevicePreferredSize()
	   //<< tab << "" << device.getQueueOnDeviceProperties()
	   //<< tab << "" << device.getQueueOnHostProperties()

	   << '\n'

	   << tab << "Reference Count"  << device.getReferenceCount()
	   //<< tab << "SVM Capabilities" << device.getSvmCapabilities()
	   << tab << "Type"             << device.getType()
	   << tab << "Vendor"           << device.getVendor()
	   << tab << "Vendor ID"        << device.getVendorID()
	   << tab << "Version"          << device.getVersion()
	   << tab << "Driver Version"   << device.getDriverVersion();

	os << '\n';
	os << tab(1) << "Extensions:";
	for (auto&& ext : device.getExtensions()) {
		os << tab(2) << ext;
	}
	os << '\n';

	return os;
}

void test_01() {
	auto platforms = cl::Platform::getPlatforms();
	std::cout << "Count platforms: " << platforms.size() << '\n';
	for (auto&& platform : platforms) {
		std::cout << platform;
	}
	auto platform = platforms[0];

	auto devices = platform.getDevices(cl::DeviceType::all);
	std::cout << "Count devices: " << devices.size() << '\n';
	for (auto&& device : devices) {
		std::cout << device;
	}

//	auto usr_data = int{5};
//	auto properties = cl::ContextProperties().setPlatform(platform);
//	auto context = cl::Context(
//		properties,
//		devices,
//		[](auto&& error_info, auto&& private_info, auto&& user_data) {
//			std::cout << "error_info: " << error_info << '\n'
//					  << "private_info: " << '\n';
//			for (auto&& t : private_info) std::cout << '\t' << t << '\n';
//			std::cout << "user_data: " << user_data << '\n';		
//		},
//		&usr_data
//	);

	auto properties = cl::ContextProperties().setPlatform(platform);
	std::cout << "Context properties created successfully!\n";

	auto context = cl::Context(properties, cl::DeviceType::cpu);
	std::cout << "Context created successfully!\n";

	std::ignore = context;
	//std::cout << "Context information ...\n";
	//std::cout << "\tReference Count = " << context.referenceCount() << '\n';

	/*
	//auto usr_data = int{5};
	std::cout << "Properties:\n";
	for (auto&& p : properties.get()) {
		std::cout << p << '\n';
	}
	std::cout << "CL_CONTEXT_PLATFORM = " << CL_CONTEXT_PLATFORM << '\n';
	std::cout << "static_cast<size_t>(platform) = " << ((size_t)(platform.id())) << '\n';
	*/

	/*
	auto context = cl::Context(
		properties,
		devices,
		[](std::string const& error_info, std::vector<uint8_t> const& private_info, int user_data) {
			std::cout << "error_info: " << error_info << '\n'
					  << "private_info: " << '\n';
			for (auto&& t : private_info) std::cout << '\t' << t << '\n';
			std::cout << "user_data: " << user_data << '\n';		
		},
		usr_data
	);
	*/
	//auto context = cl::Context(properties, devices);
	/*
	try {
		auto error = cl_int{CL_SUCCESS};
		auto context_id = clCreateContext(
			properties.get().data(),
			devices.size(),
			reinterpret_cast<const cl_device_id*>(devices.data()),
			nullptr,
			nullptr,
			& error
		);
		cl::error::handle<cl::Exception>(error);
		std::ignore = context_id;
	} catch (cl::Exception const& e) {
		std::cout << "cl::Exception caught!\n"
				  << "\twhat() = " << e.what()
				  << "\n\tcode() = " << static_cast<std::underlying_type<cl::ErrorCode>::type>(e.code()) << '\n';
	}
	*/

	//auto tmp = context;
	//std::ignore = tmp;

	//std::ignore = context_id;
}

auto main() -> int {
	test_01();
}
