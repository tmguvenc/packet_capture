cmake_minimum_required(VERSION 3.0)

project(packet_capture)

find_package(Swig REQUIRED)

if(SWIG_FOUND)
	message(STATUS "SWIG Found")
else()
	message("SWIG NOT FOUND!!!")
endif()

set(DEPENDENCY_DIR "D:/external" CACHE PATH "Dependency folder")

set(COMMON_DIR "${DEPENDENCY_DIR}/common")

include(CheckIncludeFile)
CHECK_INCLUDE_FILE("mmintrin.h" HAVE_AVX)

set(NPCAP_DIR "${DEPENDENCY_DIR}/npcap/npcap-sdk-0.1/" CACHE PATH "npcap dir")
set(NPCAP_INCLUDE_DIR "${NPCAP_DIR}/Include")
set(NPCAP_LIBRARY_DIR "${NPCAP_DIR}/Lib/x64/")
set(NPCAP_LINK wpcap)

set(TBB_DIR "${DEPENDENCY_DIR}/tbb")
set(TBB_INCLUDE_DIR "${TBB_DIR}/include")
set(TBB_LIBRARY_DIR "${TBB_DIR}/lib/intel64/vc12")
set(TBB_BINARY_DIR "${TBB_DIR}/bin/intel64/vc12")
set(TBB_LINK_DEBUG tbb_debug)
set(TBB_LINK_RELEASE tbb)

set(ZEROMQ_DIR ${DEPENDENCY_DIR}/zeromq)
set(ZEROMQ_INCLUDE_DIR ${ZEROMQ_DIR}/include)
set(ZEROMQ_LIBRARY_DIR ${ZEROMQ_DIR}/x64/lib)
set(ZEROMQ_BINARY_DIR ${ZEROMQ_DIR}/x64/bin)
set(ZEROMQ_LINK_DEBUG libzmq-v120-mt-gd-4_0_4)
set(ZEROMQ_LINK_RELEASE libzmq-v120-mt-4_0_4)

set(SWIG "${SWIG_EXECUTABLE}")

set(GTEST_DIR ${DEPENDENCY_DIR}/googletest-distribution)
set(GTEST_INCLUDE_DIR ${GTEST_DIR}/include)
set(GTEST_LIB_DIR ${GTEST_DIR}/lib)
set(GTEST_LINK_DEBUG "gtest-d" )
set(GTEST_LINK_RELEASE "gtest")

enable_testing()

add_subdirectory(packet_capture)
# add_subdirectory(test)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)