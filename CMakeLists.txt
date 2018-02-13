project(libcalc)

cmake_minimum_required(VERSION 2.8)

set(PROJECT_VERSION, 0.1)

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

if ($ENV{DEBUG})
  message(STATUS "Build tests")
  enable_testing()
  add_subdirectory(${PROJECT_SOURCE_DIR}/tests)
endif()

add_library(calc SHARED
  ./src/libcalc.cxx
  ./src/tokenizer.cxx
  )


include(GNUInstallDirs)

set(PUBLIC_HEADER "${PROJECT_SOURCE_DIR}/include/libcalc.hpp")

set(DEST_DIR "${CMAKE_INSTALL_PREFIX}")
set(PRIVATE_LIBS "${PRIVATE_LIBS} -lcalc")


configure_file(libcalc.pc.in libcalc.pc @ONLY)

target_include_directories(calc PRIVATE .)

install(TARGETS calc LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

install(FILES ${PUBLIC_HEADER} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(FILES ${CMAKE_BINARY_DIR}/libcalc.pc
    DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig)

IF(EXISTS "${CMAKE_ROOT}/Modules/CPack.cmake")
  SET(MAJOR_VERSION 0)
  SET(MINOR_VERSION 1)
  SET(PATCH_VERSION 0)
  INCLUDE(InstallRequiredSystemLibraries)

  SET(CPACK_SET_DESTDIR "on")
  SET(CPACK_PACKAGING_INSTALL_PREFIX "/tmp")
  SET(CPACK_INSTALL_PREFIX "/usr")
  SET(CPACK_GENERATOR "DEB")

  SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "A very basic math expressions(infix) evaluator")
  SET(CPACK_PACKAGE_VENDOR "Svetlana Linuxenko")
  SET(CPACK_PACKAGE_CONTACT "sveta@linuxenko.pro")
  SET(CPACK_PACKAGE_VERSION_MAJOR "${MAJOR_VERSION}")
  SET(CPACK_PACKAGE_VERSION_MINOR "${MINOR_VERSION}")
  SET(CPACK_PACKAGE_VERSION_PATCH "${PATCH_VERSION}")
  SET(CPACK_PACKAGE_FILE_NAME "${CMAKE_PROJECT_NAME}_${MAJOR_VERSION}.${MINOR_VERSION}.${CPACK_PACKAGE_VERSION_PATCH}")
  SET(CPACK_SOURCE_PACKAGE_FILE_NAME "${CMAKE_PROJECT_NAME}_${MAJOR_VERSION}.${MINOR_VERSION}.${CPACK_PACKAGE_VERSION_PATCH}")

  SET(CPACK_DEBIAN_PACKAGE_DEPENDS "")

  SET(CPACK_DEBIAN_PACKAGE_PRIORITY "optional")
  SET(CPACK_DEBIAN_PACKAGE_SECTION "lib")
  SET(CPACK_DEBIAN_ARCHITECTURE ${CMAKE_SYSTEM_PROCESSOR})

  SET(CPACK_COMPONENTS_ALL Libraries ApplicationData)
  INCLUDE(CPack)

ENDIF(EXISTS "${CMAKE_ROOT}/Modules/CPack.cmake")
