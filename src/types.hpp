#ifndef EAOPCUA_TYPES_HPP
#define EAOPCUA_TYPES_HPP

#include <map>
#include <mutex>
#include <open62541.h>
#include <functional>

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

	void* v = nullptr;

	address() = default;

	explicit address(const std::string& s, const std::string& d){
		std::vector<std::string> s_parts = string_split(s, {'.'});

		byte = (std::uint16_t)std::stoi(s_parts[0]);

		if(s_parts.size() > 1){
			Typ = BIT_ADDRESS;
			bit = (std::uint8_t)std::stoi(s_parts[1]);
		}

		datatype = address::DatatypeFromString.at(d);

		switch(datatype){
		    case address::Datatype::Bit: {
				v = calloc(1, sizeof(UA_Boolean));

				break;
			}
			case address::Datatype::Byte: {
				v = calloc(1, sizeof(UA_Byte));

				break;
			}
			case address::Datatype::Int16: {
				v = calloc(1, sizeof(UA_Int16));

				break;
			}
			default: break;
		}
	}
};

inline const std::map<std::string, address::Datatype> address::DatatypeFromString = {{"BOOL", Bit}, {"BYTE", Byte}, {"INT", Int16}};

struct operation {
	std::map<std::string, address>* io_addresses;

    enum Type {
        Int32, UInt32, Boolean, Double, String
    };

    Type Typ;

    static const std::map<operation::Type, size_t> SizeFromType;

	void* v = nullptr;

	std::function<void(operation*)> op;

	operation(operation::Type d, std::map<std::string, address>* io, std::function<void(operation*)> op_){
	    io_addresses = io;
        Typ = d;
        op = op_;

        v = calloc(1, operation::SizeFromType.at(d));
	}
};

inline const std::map<operation::Type, size_t> operation::SizeFromType = {{Int32, sizeof(UA_Int32)}, {UInt32, sizeof(UA_UInt32)}, {Boolean, sizeof(UA_Boolean)}, {Double, sizeof(UA_Double)}, {String, sizeof(UA_String)}};

#endif //EAOPCUA_TYPES_HPP
