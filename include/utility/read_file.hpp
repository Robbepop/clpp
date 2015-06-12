#ifndef CLPP_UTILITY_READ_FILE_H
#define CLPP_UTILITY_READ_FILE_H

#include <string>
#include <fstream>

namespace utility {
	auto readFile(std::string const& filePath) -> std::string {
		std::ifstream ifs{filePath};
		std::string content{
			std::istreambuf_iterator<char>(ifs),
			std::istreambuf_iterator<char>()};
		return content;
	}
}

#endif // CLPP_UTILITY_READ_FILE_H
