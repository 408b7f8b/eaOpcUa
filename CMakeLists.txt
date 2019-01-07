cmake_minimum_required(VERSION 2.4)
project(eaOpcUa)

SET(REVPI_DIR /home/dbb/Desktop/revpi/demo)
SET(OPEN62541_DIR /home/dbb/Downloads/open62541-open62541-6249bb2/build)
SET(HELFERLEIN_DIR /home/dbb/Desktop/git/helferlein)

include_directories(${REVPI_DIR} ${OPEN62541_DIR} ${HELFERLEIN_DIR})
link_directories(${OPEN62541_DIR}/bin)

set(CMAKE_CXX_STANDARD 11)
SET(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} -z defs")

link_libraries(open62541)

add_executable(eaOpcUa main.cpp src/EA.hpp src/file.hpp src/server.hpp src/types.hpp ${REVPI_DIR}/piControlIf.c ${REVPI_DIR}/piControlIf.h ${OPEN62541_DIR}/open62541.h src/operations.hpp)