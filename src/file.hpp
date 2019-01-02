#ifndef EAOPCUA_FILE_HPP
#define EAOPCUA_FILE_HPP

#include <string>
#include <vector>
#include <map>
#include <fstream>

#include "string_split.hpp"
#include "types.hpp"

std::map<std::string, address> readIODescription(const std::string& path_to_file){
	std::map<std::string, address> ret;

	std::ifstream file(path_to_file);
	if (file.is_open()) {
		std::string line;
		while (getline(file, line)) {
			std::vector<std::string> line_parts = string_split(line, {' ', '\t', '\r', '/'});

			if(line_parts.size() > 2){
				ret.insert({line_parts[0], address(line_parts[1], line_parts[2])});
			}
		}
		file.close();
	}

	return ret;
}

#endif //EAOPCUA_FILE_HPP
