#ifndef EAOPCUA_TYPES_HPP
#define EAOPCUA_TYPES_HPP

#include <map>
#include <mutex>

#include "string_split.hpp"

struct address {
	std::uint16_t byte = 0;
	std::uint8_t bit = 0;

	enum Type {
		BYTE_ADDRESS, BIT_ADDRESS
	};

	Type Typ = BYTE_ADDRESS;

	enum Datatype {
		Bit, Byte, Int16
	};

	Datatype datatype;

	static const std::map<std::string, Datatype> DatatypeFromString;

	address() = default;

	explicit address(const std::string& s, const std::string& d){
		std::vector<std::string> s_parts = string_split(s, {'.'});

		byte = (std::uint16_t)std::stoi(s_parts[0]);

		if(s_parts.size() > 1){
			Typ = BIT_ADDRESS;
			bit = (std::uint8_t)std::stoi(s_parts[1]);
		}

		datatype = address::DatatypeFromString.at(d);
	}
};

const std::map<std::string, address::Datatype> address::DatatypeFromString = {{"BOOL", Bit}, {"BYTE", Byte}, {"INT", Int16}};

#endif //EAOPCUA_TYPES_HPP
