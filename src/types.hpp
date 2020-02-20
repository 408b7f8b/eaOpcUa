#ifndef EAOPCUA_TYPES_HPP
#define EAOPCUA_TYPES_HPP

#include <map>
#include <vector>
#include <mutex>
#include "open62541/types.h"
#include <functional>

#include "string_split.hpp"

struct address {
	std::uint16_t byte = 0;
	std::uint8_t bit = 0;

	enum Feldtyp {
	    EIN, AUS, SPE
	};

	Feldtyp ftyp = EIN;

	enum Type {
		BYTE_ADDRESS, BIT_ADDRESS
	};

	Type Typ = BYTE_ADDRESS;

	enum Datatype {
		Bit, Byte, Int16, UInt16
	};

	Datatype datatype;

	bool schreibbar = false;

	static const std::map<std::string, Datatype> DatatypeFromString;
	static const std::map<Datatype, std::string> DataTypeToString;

    static const std::map<std::string, address::Feldtyp> FeldtypFromString;
    static const std::map<address::Feldtyp, std::string> StringFromFeldtyp;

	void* v = nullptr;

	address() = default;

	explicit address(const std::string& adr, const std::string& d){
		std::vector<std::string> s_parts = string_split(adr, {'.', ':'});

        byte = (std::uint16_t)std::stoi(s_parts[1]);

		switch(s_parts.size()){
		    case 2:{

		        break;
		    }
            case 3:{
                Typ = BIT_ADDRESS;
                bit = (std::uint8_t)std::stoi(s_parts[2]);

                break;
            }
            default:{

            }
		}

		ftyp = FeldtypFromString.at(s_parts[0].substr(0, 1));

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
            case address::Datatype::UInt16: {
                v = calloc(1, sizeof(UA_UInt16));

                break;
            }
			default: break;
		}
	}

	std::string toString(){

		std::string r = std::to_string(byte);

		if(Typ == BIT_ADDRESS) r += "." + std::to_string(bit);

		return r;
	}
};

const std::map<std::string, address::Datatype> address::DatatypeFromString = {{"BOOL", Bit}, {"BYTE", Byte}, {"WORD", UInt16}, {"INT", Int16}};
const std::map<address::Datatype, std::string> address::DataTypeToString = {{Bit, "BOOL"}, {Byte, "BYTE"}, {UInt16, "WORD"}, {Int16, "INT"}};

const std::map<std::string, address::Feldtyp> address::FeldtypFromString = {{"I", address::Feldtyp::EIN}, {"Q", address::Feldtyp::AUS}, {"M", address::Feldtyp::SPE}};
const std::map<address::Feldtyp, std::string> address::StringFromFeldtyp = {{address::Feldtyp::EIN, "I"}, {address::Feldtyp::AUS, "Q"}, {address::Feldtyp::SPE, "M"}};

struct operation {
	std::map<std::string, address>* io_addresses;

    enum Type {
        Int32, UInt32, Boolean, Double, String
    };

    Type Typ;

    static const std::map<operation::Type, size_t> SizeFromType;
    std::vector<std::string> input, param;

	void* v = nullptr;

	std::function<void(operation*)> op;

	operation(operation::Type d, std::map<std::string, address>* io, std::function<void(operation*)> op_, std::vector<std::string> input_, std::vector<std::string> param_){
	    io_addresses = io;
        Typ = d;
        op = op_;
		input = input_;
		param = param_;

        v = calloc(1, operation::SizeFromType.at(d));
	}
};

const std::map<operation::Type, size_t> operation::SizeFromType = {{Int32, sizeof(UA_Int32)}, {UInt32, sizeof(UA_UInt32)}, {Boolean, sizeof(UA_Boolean)}, {Double, sizeof(UA_Double)}, {String, sizeof(UA_String)}};

#endif //EAOPCUA_TYPES_HPP
