#ifndef EAOPCUA_EA_HPP
#define EAOPCUA_EA_HPP

#include "piControl.h"
#include "piControlIf.h"

#include "types.hpp"

bool writeValue(const std::uint16_t byte, const std::uint8_t bit, std::uint32_t value){
	int rc;

	rc = piControlWrite(byte, bit, (uint8_t*) &value);

	return rc == 0;
}

bool writeValue(const address& adr, std::uint32_t value){
	return writeValue(adr.byte, adr.bit, value);
}

bool writeBit(const std::uint16_t byte, const std::uint8_t bit, bool value){
	int rc;

	SPIValue sPIValue;
	sPIValue.i16uAddress = byte;
	sPIValue.i8uBit = bit;
	sPIValue.i8uValue = (std::uint8_t)value;
	rc = piControlSetBitValue(&sPIValue);

	return rc == 0;
}

bool writeBit(const address& adr, bool value){
	return writeBit(adr.byte, adr.bit, value);
}

bool readBytes(const std::uint16_t byte, const std::uint8_t length, std::uint8_t* value){
	int rc;

	rc = piControlRead(byte, length, value);

	return rc == length;
}

bool readBytes(const address& adr, const std::uint8_t length, std::uint8_t* value){
	return readBytes(adr.byte, length, value);
}

bool readBytes(const address& adr, std::uint8_t* value){
	return readBytes(adr.byte, 1, value);
}

bool readBit(const std::uint16_t byte, const std::uint8_t bit){
	int rc;

	SPIValue sPIValue;
	sPIValue.i16uAddress = byte;
	sPIValue.i8uBit = bit;
	rc = piControlGetBitValue(&sPIValue);

	//return rc == 0;
	return sPIValue.i8uValue;
}

bool readBit(const address& adr){
	return readBit(adr.byte, adr.bit);
}

#endif //EAOPCUA_EA_HPP
