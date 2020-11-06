cmake_minimum_required (VERSION 2.9)
project (Calc)
set(CMAKE_BUILD_TYPE Debug)

file(GLOB SOURCES "src/*.cpp")
include_directories(src)

add_executable(Calc ${SOURCES})

enable_testing()
set(TESTING_TIMEOUT 2)

FILE(GLOB TEST_LISTS "test/*.cpp")
list(FILTER SOURCES EXCLUDE REGEX ".*Main.cpp$")
foreach(X ${TEST_LISTS})
    get_filename_component(CURRENT_NAME ${X} NAME_WE)
    add_executable(${CURRENT_NAME} ${X} ${SOURCES})
    set_target_properties(${CURRENT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/tests")
    add_test(${CURRENT_NAME} "${CMAKE_BINARY_DIR}/tests/${CURRENT_NAME}")

    set_tests_properties(${CURRENT_NAME} PROPERTIES TIMEOUT ${TESTING_TIMEOUT})
endforeach()
