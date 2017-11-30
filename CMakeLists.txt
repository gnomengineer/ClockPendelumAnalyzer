cmake_minimum_required (VERSION 2.6)

project (ClockPendulumAnalyzer)
set(CMAKE_CXX_FLAGS "-std=c++11 -lpthread")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

#compile setting for application
set(CLOCKPENDULUM_SOURCE_PATH ${PROJECT_SOURCE_DIR}/src/app)
file(GLOB_RECURSE CLOCKPENDULUM_SOURCE_FILES ${CLOCKPENDULUM_SOURCE_PATH}/*.cpp)
add_executable(clockpendulum_analyzer ${CLOCKPENDULUM_SOURCE_FILES})

#compile setting for unit tests
set(CLOCKPENDULUM_TEST_SOURCE_PATH ${PROJECT_SOURCE_DIR}/src/test)
file(GLOB_RECURSE CLOCKPENDULUM_TEST_SOURCE_FILES ${CLOCKPENDULUM_TEST_SOURCE_PATH}/*.cpp)
add_executable(clockpendulum_analyzer_unit_tests ${CLOCKPENDULUM_TEST_SOURCE_FILES})

#run tests after build
#enable_testing()
#set(BUILD_TESTING ON)
#add_test(NAME unit-tests COMMAND ${PROJECT_BINARY_DIR}/clockpendulum_analyzer_unit_tests)
