#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>

#include "clpp/utility/to_underlying.hpp"
#include "clpp.hpp"

#include <type_traits>
#include <unordered_map>
#include <map>
#include <random>

#include "clpp/detail/cl_function.hpp"

namespace utility {
	auto readFile(std::string const& filePath) -> std::string {
		std::ifstream ifs{filePath};
		std::string content{
			std::istreambuf_iterator<char>(ifs),
			std::istreambuf_iterator<char>()};
		return content;
	}
}

#if defined(CL_VERSION_2_0)

template <typename T>
auto operator<<(std::ostream& out, const std::vector<T>& v) -> std::ostream & {
	if (!v.empty()) {
		out << '[';
		std::copy(v.begin(), v.end(), std::ostream_iterator<T>(out, ", "));
		out << "\b\b]";
	}
	return out;
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

namespace test {
	struct tabular {
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
		case cl::DeviceType::defaultType: os << "Default Type";                     break;
		case cl::DeviceType::cpu:         os << "Compute Processing Unit (CPU)";    break;
		case cl::DeviceType::gpu:         os << "Graphical Processing Unit (GPU)";  break;
		case cl::DeviceType::accelerator: os << "Accelerator";                      break;
		case cl::DeviceType::all:         os << "All Types";                        break;
		default: assert(false);
	}
	return os;
}

auto operator<<(std::ostream & os, const cl::AffinityDomain & domain) -> std::ostream & {
	switch (domain) {
		case cl::AffinityDomain::numa:              os << "NUMA";               break;
		case cl::AffinityDomain::cacheL1:           os << "L1 Cache";           break;
		case cl::AffinityDomain::cacheL2:           os << "L2 Cache";           break;
		case cl::AffinityDomain::cacheL3:           os << "L3 Cache";           break;
		case cl::AffinityDomain::cacheL4:           os << "L4 Cache";           break;
		case cl::AffinityDomain::nextPartitionable: os << "Next Partitionable"; break;
		default: assert(false);
	}
	return os;
}

auto operator<<(std::ostream & os, const cl::AffinityDomainCapabilities & caps) -> std::ostream & {
	using cast::to;
	auto tab = test::tabular{10, 30};
	os << tab << "Has NUMA"           << caps.hasNuma()
	   << tab << "Has L1-Cache"       << caps.hasL1Cache()
	   << tab << "Has L2-Cache"       << caps.hasL2Cache()
	   << tab << "Has L3-Cache"       << caps.hasL3Cache()
	   << tab << "Has L4-Cache"       << caps.hasL4Cache()
	   << tab << "Next Partitionable" << caps.isNextPartitionable();
	return os;
}

auto operator<<(std::ostream & os, const cl::CommandQueueProperties & props) -> std::ostream & {
	using cast::to;
	auto tab = test::tabular{10, 30};
	os << tab << "Out Of Order Exec. Enabled" << props.isOutOfOrderExecModeEnabled()
	   << tab << "Profiling Enabled"          << props.isProfilingEnabled();
	return os;
}

auto operator<<(std::ostream & os, const cl::ExecutionCapabilities & caps) -> std::ostream & {
	using cast::to;
	auto tab = test::tabular{10, 30};
	os << tab << "Execute Kernel"        << caps.canExecuteKernel()
	   << tab << "Execute Native Kernel" << caps.canExecuteNativeKernel();
	return os;
}

auto operator<<(std::ostream & os, const cl::PartitionCapabilities & caps) -> std::ostream & {
	using cast::to;
	auto tab = test::tabular{10, 30};
	os << tab << "Partition Equally"            << caps.supportsPartitionEqually()
	   << tab << "Partition By Counts"          << caps.supportsPartitionByCounts()
	   << tab << "Partition By Affinity Domain" << caps.supportsPartitionByAffinityDomain();
	return os;
}

auto operator<<(std::ostream & os, const cl::SvmCapabilities & caps) -> std::ostream & {
	using cast::to;
	auto tab = test::tabular{10, 30};
	os << tab << "Coarse Grain Buffer" << caps.supportsCoarseGrainBuffer()
	   << tab << "Fine Grain Buffer"   << caps.supportsFineGrainBuffer()
	   << tab << "Fine Grain System"   << caps.supportsFineGrainSystem()
	   << tab << "Atomics"             << caps.supportsAtomics();
	return os;
}

auto operator<<(std::ostream & os, const cl::FPConfig & config) -> std::ostream & {
	using cast::to;
	auto tab = test::tabular{10, 30};
	os << tab << "Denorm"                       << config.supportsDenorm()
	   << tab << "Inf And NaN"                  << config.supportsInfAndNan()
	   << tab << "Round To Nearest"             << config.supportsRoundToNearest()
	   << tab << "Round To Zero"                << config.supportsRoundToZero()
	   << tab << "Round To Infinity"            << config.supportsRoundToInf()
	   << tab << "Fused Multiply Add"           << config.supportsFusedMultiplyAdd()
	   << tab << "Correctly Rounded Div.-Sqrt." << config.supportsCorrectlyRoundedDivideSqrt()
	   << tab << "Soft Float"                   << config.supportsSoftFloat();
	return os;
}

auto operator<<(std::ostream & os, const cl::Partition & partition) -> std::ostream & {
	switch (partition.getKind()) {
		case cl::Partition::Kind::equally:
			os << "Equally: "            << partition.getComputeUnits();
		case cl::Partition::Kind::byCounts:
			os << "By Counts: "          << partition.getCounts();
		case cl::Partition::Kind::byAffinityDomain:
			os << "By Affinity Domain: " << partition.getAffinityDomain();
		case cl::Partition::Kind::none:
			os << "Not Partitioned";
	}
	return os;
}

auto operator<<(std::ostream & os, const cl::Platform & platform) -> std::ostream & {
	auto tab = test::tabular{5, 35};
	os << "Platform" << std::left
	   << tab    << "Name"    << platform.getName()
	   << tab    << "Profile" << platform.getProfile()
	   << tab    << "Vendor"  << platform.getVendor()
	   << tab    << "Version" << platform.getVersion()
	   << tab(1) << "Extensions";
	for (auto&& ext : platform.getExtensions()) {
		os << tab(2) << ext;
	}
	return os;
}

auto operator<<(std::ostream & os, const cl::ContextProperties &) -> std::ostream & {
//	auto tab = test::tabular{10, 30};
//	os << tab << "Platform Name" << properties.getPlatform().getName()
//	   << tab << "InteropUserSync" << properties.getInteropUserSync();
	return os;
}

auto operator<<(std::ostream & os, const cl::Context & context) -> std::ostream & {
	auto tab = test::tabular{5, 35};
	os << "Context" << std::left
	   << tab    << "Reference Count" << context.getReferenceCount()
	   << tab    << "Num Devices"     << context.getNumDevices()
	   << tab(1) << "Devices";
	for (auto&& device : context.getDevices()) {
		os << tab(2) << device.getName();
	}
	os << tab << "Properties" << context.getProperties();
	return os;
}

template<typename T>
auto operator<<(std::ostream & os, const cl::Buffer<T> & buffer) -> std::ostream & {
	auto tab = test::tabular{5, 35};
	os << tab << "Size"              << buffer.getSize()
	   << tab << "Size (in Bytes)"   << buffer.getSizeInBytes()
	   << tab << "Offset"            << buffer.getOffset()
	   << tab << "Host Pointer"      << buffer.getHostPtr()
	   << tab << "Associated Buffer" << (buffer.getAssociatedBuffer() ? "has Parent" : "no Parent");
	return os;
}

auto operator<<(std::ostream & os, const cl::Device & device) -> std::ostream & {
	using cast::to;
	auto tab = test::tabular{5, 35};
	os << "Device" << std::left << std::boolalpha
	   << tab << "Name"                     << device.getName()
	   << tab << "Available"                << to<bool>(device.isAvailable())
	   << tab << "Compiler available"       << to<bool>(device.isCompilerAvailable())
	   << tab << "Address bits"             << device.getAddressBits()
	   << tab << "Little Endian"            << to<bool>(device.isLittleEndian())
	   << tab << "Linker Available"         << to<bool>(device.isLinkerAvailable())
	   << tab << "Error Correction Support" << to<bool>(device.hasErrorCorrectionSupport())
	   << tab << "Execution Capabilities"   << device.getExecutionCapabilities()

	   << '\n'

	   << tab << "Floating Point Config (float)" << device.getFpConfig(cl::FPType::singlePrecision)

	   << '\n'

	   << tab << "Floating Point Config (double)" << device.getFpConfig(cl::FPType::doublePrecision)

	   << '\n'

	   << tab << "Global Memory Cache Size"     << device.getGlobalMemoryCacheSize()
	   << tab << "Global Memory Cache Type"     << device.getGlobalMemoryCacheType()
	   << tab << "Global Memory Cacheline Size" << device.getGlobalMemoryCachelineSize()
	   << tab << "Global Memory Size"           << device.getGlobalMemorySize()
	   << tab << "Global Var. Pref. Total Size" << device.getGlobalVariablePreferredTotalSize()
	   << tab << "Max Work Item Sizes"         << device.getMaxWorkItemSizes()

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
	   << tab << "Name"                      << device.getName()

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
	   << tab << "Partition Affinity Domain" << device.getPartitionAffinityDomain()
	   << tab << "Partition Max Sub Devices" << device.getPartitionMaxSubDevices()
	   << tab << "Partition Properties"      << device.getPartitionProperties()
	   << tab << "Partition Type"            << device.getPartition()

	   << '\n'

	   << tab << "Pipe Max Active Reservations" << device.getPipeMaxActiveReservations()
	   << tab << "Pipe Max Packet Size"         << device.getPipeMaxPacketSize()
	   << tab << "Platform Name"                << device.getPlatform().getName()

	   << '\n'

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

	   << '\n'

	   << tab << "Print Buffer Size"          << device.getPrintfBufferSize()
	   << tab << "Profile"                    << device.getProfile()
	   << tab << "Profiling Timer Resolution" << device.getProfilingTimerResolution()

	   << '\n'

	   << tab << "Queue on Device Max Size"   << device.getQueueOnDeviceMaxSize()
	   << tab << "Queue on Device Pref. Size" << device.getQueueOnDevicePreferredSize()
	   << tab << "Queue on Device Properties" << device.getQueueOnDeviceProperties()
	   << tab << "Queue on Host Properties"   << device.getQueueOnHostProperties()

	   << '\n'

	   << tab << "Reference Count"  << device.getReferenceCount()
	   << tab << "SVM Capabilities" << device.getSvmCapabilities()
	   << tab << "Type"             << device.getType()
	   << tab << "Vendor"           << device.getVendor()
	   << tab << "Vendor ID"        << device.getVendorID()
	   << tab << "Version"          << device.getVersion()
	   << tab << "Driver Version"   << device.getDriverVersion();

	os << '\n';
	os << tab(1) << "Extensions";
	for (auto&& ext : device.getExtensions()) {
		os << tab(2) << ext;
	}
	os << '\n';

	return os;
}

#endif // defined(CL_VERSION_2_0)

void test_01() {
//	auto platforms = cl::Platform::getPlatforms();
//	std::cout << "Count platforms: " << platforms.size() << '\n';
//	for (auto&& platform : platforms) {
//		std::cout << platform;
//	}
//	std::cout << '\n';
//	auto platform = platforms[0];

//	auto devices = platform.getDevices();
//	std::cout << "Count devices: " << devices.size() << '\n';
//	for (auto&& device : devices) {
//		std::cout << device;
//	}
//	auto defaultDevice = devices[0];

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

//	auto properties = cl::ContextProperties().setPlatform(platform);
//	std::cout << "Context properties created successfully!\n";

	auto context = cl::Context::createBest();
	auto defaultDevice = context.getDevices().front();
//	auto context = cl::Context::createForType(properties, cl::DeviceType::cpu);
//	auto context = cl::Context::createForDevices(defaultDevice);
//	auto context = cl::Context::createDefault();
	std::cout << "Context created successfully!\n";
//	std::cout << context << "\n\n";

	constexpr auto vectorSize = 1000000;

	auto vectorA = std::array<std::vector<cl_int>, 2>{{
		std::vector<cl_int>(vectorSize),
		std::vector<cl_int>(vectorSize)}};
	auto vectorB = std::array<std::vector<cl_int>, 2>{{
		std::vector<cl_int>(vectorSize),
		std::vector<cl_int>(vectorSize)}};
	auto vectorC = std::array<std::vector<cl_int>, 2>{{
		std::vector<cl_int>(vectorSize),
		std::vector<cl_int>(vectorSize)}};

	std::random_device seeder;
	auto dist   = std::uniform_int_distribution<cl_int>{-9999, 9999};
	auto engine = std::default_random_engine{seeder()};
	for (auto&& elem : vectorA[0]) { elem = dist(engine); }
	for (auto&& elem : vectorB[0]) { elem = dist(engine); }
	for (auto i = 0ul; i < vectorSize; ++i) {
		vectorC[0][i] = vectorA[0][i] + vectorB[0][i];
	}

//	std::cout << "Host Buffers [0]:\n\n";
//	std::cout << "vectorA[0] = " << vectorA[0] << '\n';
//	std::cout << "vectorB[0] = " << vectorB[0] << '\n';
//	std::cout << "vectorC[0] = " << vectorC[0] << '\n';

	auto queue = context.createCommandQueue(defaultDevice);

	auto bufferA = context.createBuffer<cl_int>(vectorSize);
	auto bufferB = context.createBuffer<cl_int>(vectorSize);
	auto bufferC = context.createBuffer<cl_int>(vectorSize);

	queue.writeBufferBlocked(bufferA, vectorA[0].begin(), vectorA[0].end());
	queue.writeBufferBlocked(bufferB, vectorB[0].begin(), vectorB[0].end());

//	queue.writeBufferBlocked(bufferA, vectorA); // API does not exist by now
//	queue.writeBufferBlocked(bufferB, vectorB); // API does not exist by now

//	std::cout << "OpenCL Buffers:\n\n";
//	std::cout << "bufferA" << bufferA << "\n\n";
//	std::cout << "bufferB" << bufferB << "\n\n";
//	std::cout << "bufferC" << bufferC << "\n\n";

	auto programSource = utility::readFile("../test/kernel_add.cl");
	auto program = context.createProgramWithSource(programSource);

	program.build(defaultDevice);

	auto kernel = program.createKernel("vectorAdd");

	kernel.setArgs(bufferA, bufferB, bufferC, vectorSize, cl::LocalMemory<cl_int>(10));

	queue.execute1DRange(kernel, vectorSize);

	queue.finish();

	queue.readBufferBlocked(bufferA, vectorA[1].begin(), vectorA[1].end());
	queue.readBufferBlocked(bufferB, vectorB[1].begin(), vectorB[1].end());
	queue.readBufferBlocked(bufferC, vectorC[1].begin(), vectorC[1].end());

//	std::cout << "Host Buffers [1]:\n\n";
//	std::cout << "vectorA[1] = " << vectorA[1] << '\n';
//	std::cout << "vectorB[1] = " << vectorB[1] << '\n';
//	std::cout << "vectorC[1] = " << vectorC[1] << '\n';

	auto isEqual = true;
	for (auto i = 0ul; i < vectorSize; ++i) {
		isEqual = isEqual && (
		       vectorA[0][i] == vectorA[1][i]
		    && vectorB[0][i] == vectorB[1][i]
		    && vectorC[0][i] == vectorC[1][i]);
	}
	std::cout << "are vectors equal? " << std::boolalpha << isEqual << '\n';

//	std::ignore = context;
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
	try {
		test_01();
	}
	catch (cl::error::AnyError & e) {
		std::cout << "what(): " << e.what() << '\n';
	}
}
