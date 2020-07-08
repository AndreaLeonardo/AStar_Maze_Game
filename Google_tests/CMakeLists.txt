# 'Google_test' is the subproject name
set(PROJECT_NAME Google_tests)
project(${PROJECT_NAME})


# 'lib' is the folder with Google Test sources
add_subdirectory(lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -static")

set(CMAKE_CXX_STANDARD 14)


set(SOURCE_FILES pathTests.cpp)

#add_executable(Google_Tests_run pathTests.cpp)

#if(CMAKE_BUILD_TYPE STREQUAL "Release")
#    add_executable(${PROJECT_NAME} WIN32 ${SOURCE_FILES} )
#else()
#    add_executable(${PROJECT_NAME} ${SOURCE_FILES} )
#endif()

set(SFML_ROOT ../../Libraries/SFML)
set(SFML_STATIC_LIBRARIES TRUE)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML 2 REQUIRED COMPONENTS audio graphics window system)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(Google_Tests_run ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif()

# 'Google_Tests_run' is the target name
# 'test1.cpp tests2.cpp' are source files with tests

target_link_libraries(Google_Tests_run gtest gtest_main)



