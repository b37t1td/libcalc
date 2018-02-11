add_executable(RunTests test-calc.cxx)
target_link_libraries(RunTests calc)

add_custom_target(Test COMMAND ./RunTests)
