cmake_minimum_required(VERSION 3.0)

project(test)

SET(tests
	test_paketGonder
	)

include_directories(../${LIBRARY_NAME}/include)
# include_directories(${GTEST_INCLUDE_DIR})
include_directories(${ZEROMQ_INCLUDE_DIR})
include_directories(${TBB_INCLUDE_DIR})

# link_directories(${GTEST_LIB_DIR})
link_directories(${NPCAP_LIBRARY_DIR})
link_directories(${TBB_LIBRARY_DIR})
link_directories(${ZEROMQ_LIBRARY_DIR})

# foreach(test ${tests})
	# add_definitions(-DGTEST_LINKED_AS_SHARED_LIBRARY)
	add_executable(test_paketGonder "test_paketGonder.cpp")
	# add_test(NAME ${test} COMMAND ${test})
	target_link_libraries(test_paketGonder ${LIBRARY_NAME})
	target_link_libraries(test_paketGonder debug ${ZEROMQ_LINK_DEBUG} optimized ${ZEROMQ_LINK_RELEASE})
	# target_link_libraries(${test} debug ${GTEST_LINK_DEBUG} optimized ${GTEST_LINK_RELEASE})
	set_target_properties(test_paketGonder PROPERTIES FOLDER "Tests") 
# endforeach()