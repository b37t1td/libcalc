project(libcalc)

cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if ($ENV{RELEASE})
  set (CMAKE_CXX_FLAGS "-O2 -Wall")
else()
  set (CMAKE_CXX_FLAGS "-g -Wall")
endif()

if ($ENV{TRAVIS})
  message(STATUS "Travis-CI build.")
else()
  message(STATUS "Local build")
endif()

include_directories("${PROJECT_SOURCE_DIR}/include")

add_library(calc SHARED
  ./src/libcalc.cxx
  ./src/parser.cxx
  ./src/tokenizer.cxx
  ./src/evaluator.cxx
  )

add_executable(RunTests ./tests/test-calc.cxx)
target_link_libraries(RunTests calc)

add_custom_target(Test COMMAND ./RunTests)
