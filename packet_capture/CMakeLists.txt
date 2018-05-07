cmake_minimum_required(VERSION 3.0)

project(packet_capture)

set(VERSION_MAJOR "1" CACHE STRING "Major")
set(VERSION_MINOR "0" CACHE STRING "Minor")
set(VERSION_TYPE "0" CACHE STRING "Type")
set(VERSION_BUILD "0" CACHE STRING "Build")

configure_file(
	${CMAKE_CURRENT_SOURCE_DIR}/version.rc.in
	${CMAKE_CURRENT_BINARY_DIR}/version.rc
	@ONLY)
	
configure_file(
	${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}Version.cpp.in
	${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Version.cpp
	@ONLY)

file(GLOB SOURCE_FILES "src/*.c*")
file(GLOB HEADER_FILES "include/*.*h*")

include_directories(./include)
include_directories(${COMMON_INCLUDE_DIR})
include_directories(${TBB_INCLUDE_DIR})
include_directories(${NPCAP_INCLUDE_DIR})
include_directories(${ZEROMQ_INCLUDE_DIR})

if(HAVE_AVX)
	add_definitions(-DUSING_AVX)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /arch:AVX")
endif()

add_definitions(-DPACKET_CAPTURE_EXPORTS)

link_directories(${NPCAP_LIBRARY_DIR})
link_directories(${TBB_LIBRARY_DIR})
link_directories(${ZEROMQ_LIBRARY_DIR})

ADD_LIBRARY(${PROJECT_NAME} SHARED ${SOURCE_FILES} ${HEADER_FILES} ${CMAKE_CURRENT_BINARY_DIR}/version.rc ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Version.cpp)

target_link_libraries(${PROJECT_NAME} debug ${TBB_LINK_DEBUG} optimized ${TBB_LINK_RELEASE})
target_link_libraries(${PROJECT_NAME} debug ${ZEROMQ_LINK_DEBUG} optimized ${ZEROMQ_LINK_RELEASE})
target_link_libraries(${PROJECT_NAME} ${NPCAP_LINK})

set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "API")

set (LIBRARY_NAME ${PROJECT_NAME} PARENT_SCOPE)

install(TARGETS ${PROJECT_NAME} DESTINATION bin)
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.jar" DESTINATION java)