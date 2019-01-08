cmake_minimum_required(VERSION 2.4)
project(eaOpcUa)

SET(REVPI_DIR ${CMAKE_SOURCE_DIR}/ext/demo)
SET(OPEN62541_DIR ${CMAKE_SOURCE_DIR}/ext/open62541)
SET(HELFERLEIN_DIR ${CMAKE_SOURCE_DIR}/ext/helferlein)

include_directories(${REVPI_DIR} ${OPEN62541_DIR} ${HELFERLEIN_DIR})

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)
SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -z defs")

add_executable(eaOpcUa main.cpp src/EA.hpp src/file.hpp src/server.hpp src/types.hpp ${REVPI_DIR}/piControlIf.c ${REVPI_DIR}/piControlIf.h ${OPEN62541_DIR}/open62541.c ${OPEN62541_DIR}/open62541.h src/operations.hpp)
configure_file(${CMAKE_SOURCE_DIR}/example_IO.txt addresses.txt COPYONLY)
configure_file(${CMAKE_SOURCE_DIR}/example_operation.txt operations.txt COPYONLY)