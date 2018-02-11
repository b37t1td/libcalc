add_executable(RunTests run-tests.cxx)
target_link_libraries(RunTests libcalc)

add_custom_target(Test COMMAND ./RunTests)
