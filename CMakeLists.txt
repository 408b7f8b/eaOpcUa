cmake_minimum_required(VERSION 2.4)
project(eaOpcUa)

SET(REVPI_DIR ${CMAKE_SOURCE_DIR}/ext/piControl)
SET(OPEN62541_DIR ${CMAKE_SOURCE_DIR}/ext/open62541)
SET(HELFERLEIN_DIR ${CMAKE_SOURCE_DIR}/ext/helferlein)

include_directories(${REVPI_DIR} ${OPEN62541_DIR}/include ${OPEN62541_DIR}/deps ${HELFERLEIN_DIR})
link_directories(${OPEN62541_DIR}/build/bin)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)
SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -z defs")

add_executable(eaOpcUa main.cpp ${REVPI_DIR}/piTest/piControlIf.c)
target_link_libraries(eaOpcUa open62541)

configure_file(${CMAKE_SOURCE_DIR}/example_IO.txt addresses.txt COPYONLY)
configure_file(${CMAKE_SOURCE_DIR}/example_operation.txt operations.txt COPYONLY)