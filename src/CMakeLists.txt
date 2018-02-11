# To build components as shared libraries use SHARED keyword
# add_library(ADDLIB SHARED add.cpp)
#add_library(ADDLIB add.cpp)
#add_executable(libcalc libcalc.cxx)

add_library(libcalc SHARED libcalc.cxx)
target_link_libraries(libcalc)

