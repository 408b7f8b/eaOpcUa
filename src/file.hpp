#ifndef EAOPCUA_FILE_HPP
#define EAOPCUA_FILE_HPP

#include <string>
#include <vector>
#include <map>
#include <fstream>

#include "string_split.hpp"
#include "types.hpp"

std::map<std::string, address> readIODescription(const std::string &path_to_file) {
    std::map<std::string, address> ret;

    std::ifstream file(path_to_file);
    if (file.is_open()) {
        std::string line;
        while (getline(file, line)) {
            std::vector<std::string> line_parts = string_split(line, {' ', '\t', '\r', '/'});

            if (line_parts.size() > 2) {
                ret.insert({line_parts[0], address(line_parts[1], line_parts[2])});
                if(line_parts[0].substr(0, 2) == "MB") ret[line_parts[0]].schreibbar = true;
            }
        }
        file.close();
    }

    return ret;
}

std::map<std::string, operation>
readOpDescription(const std::string &path_to_file, std::map<std::string, address> *io_addresses) {
    std::map<std::string, operation> ret;

    std::ifstream file(path_to_file);
    if (file.is_open()) {
        std::string line;
        while (getline(file, line)) {
            std::vector<std::string> line_parts = string_split(line, {'#'});

            if (line_parts.size() == 4) {
                std::string name = line_parts[0];
                std::string funktion = line_parts[1];
                std::vector<std::string> input = string_split(line_parts[2], {'|'});
                std::vector<std::string> param = string_split(line_parts[3], {'|'});

                ret.insert({name, operation(funktionenTypen.at(funktion), io_addresses, funktionen.at(funktion), input, param)});
            }
        }
        file.close();
    }

    return ret;
}

#endif //EAOPCUA_FILE_HPP
