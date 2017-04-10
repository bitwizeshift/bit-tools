cmake_minimum_required(VERSION 3.1)

enable_testing()

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake/modules")

include(AddIndependenceCheck)
include(GitBuildInformation)
include(MakeVersionHeader)

find_package(Bit 1.0 EXACT REQUIRED QUIET COMPONENTS Stl)

#-----------------------------------------------------------------------------
# Project Setup
#-----------------------------------------------------------------------------

option(BIT_TOOLS_COMPILE_INDEPENDENCE_TESTS "Include each header independently in a .cpp file to determine header independence" on)
option(BIT_TOOLS_COMPILE_UNIT_TESTS "Compile and run the unit tests for this library" on)

project("BitTools")

if( CMAKE_BUILD_TYPE STREQUAL "" )
  message(STATUS "CMAKE_BUILD_TYPE not set; defaulting to 'Debug'")
  set(CMAKE_BUILD_TYPE DEBUG)
endif()

#-----------------------------------------------------------------------------
# Version Info
#-----------------------------------------------------------------------------

git_build_information( PATCH_VARIABLE BIT_TOOLS_VERSION_PATCH
                       BUILD_VARIABLE BIT_TOOLS_BUILD_NUMBER
                       BRANCH_VARIABLE BIT_TOOLS_BRANCH
                       REF v0.4
                       PATHSPECS ${CMAKE_CURRENT_LIST_DIR}/include
                                 ${CMAKE_CURRENT_LIST_DIR}/src
                                 ${CMAKE_CURRENT_LIST_DIR}/cmake
                                 ${CMAKE_CURRENT_LIST_FILE}
)

set(BIT_TOOLS_VERSION_MAJOR 0 CACHE STRING "major version of bit::tools" FORCE)
set(BIT_TOOLS_VERSION_MINOR 4 CACHE STRING "minor version of bit::tools" FORCE)
set(BIT_TOOLS_VERSION_PATCH ${BIT_TOOLS_VERSION_PATCH} CACHE STRING "patch version of bit::tools" FORCE)
set(BIT_TOOLS_VERSION "${BIT_TOOLS_VERSION_MAJOR}.${BIT_TOOLS_VERSION_MINOR}.${BIT_TOOLS_VERSION_PATCH}" CACHE STRING "version of bit::tools" FORCE)
set(BIT_TOOLS_BUILD_NUMBER "${BIT_TOOLS_BUILD_NUMBER}" CACHE STRING "build number of bit::tools" FORCE)

message(STATUS "bit::tools ${BIT_TOOLS_VERSION} (${BIT_TOOLS_BRANCH} ${BIT_TOOLS_BUILD_NUMBER})")

#-----------------------------------------------------------------------------
# bit::tools
#-----------------------------------------------------------------------------

set(CMAKE_CXX_VERSION 14)

make_version_header("${CMAKE_CURRENT_BINARY_DIR}/include/bit/tools/version.hpp"
  MAJOR ${BIT_TOOLS_VERSION_MAJOR}
  MINOR ${BIT_TOOLS_VERSION_MINOR}
  PATCH ${BIT_TOOLS_VERSION_PATCH}
  BUILD ${BIT_TOOLS_BUILD_NUMBER}
  PREFIX BIT_TOOLS
  SUFFIX "a"
  TAG ${BIT_TOOLS_BRANCH}
)

set(headers
  include/bit/tools/args/arg_vector.hpp
  include/bit/tools/args/arg_suggestor.hpp
  include/bit/tools/config/type_loader.hpp
)

set(sources
  src/bit/tools/args/arg_suggestor.cpp
)

add_library(tools ${sources})
add_library(bit::tools ALIAS tools)
target_link_libraries(tools PUBLIC bit::stl)

target_include_directories(tools PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include> $<INSTALL_INTERFACE:include>)
target_compile_options(tools PUBLIC -std=c++14
  $<$<CONFIG:DEBUG>:-DDEBUG>
  $<$<CONFIG:RELEASE>:-DNDEBUG -DRELEASE>
)

#-----------------------------------------------------------------------------
# bit::tools : Independence Tests
#-----------------------------------------------------------------------------

if( BIT_TOOLS_COMPILE_INDEPENDENCE_TESTS )

  add_independence_check(tools_independence ${headers})
  target_compile_options(tools_independence PRIVATE -std=c++14
    $<$<CONFIG:DEBUG>:-DDEBUG>
    $<$<CONFIG:RELEASE>:-DNDEBUG -DRELEASE>
  )
  target_include_directories(tools_independence PRIVATE $<TARGET_PROPERTY:tools,INCLUDE_DIRECTORIES>)

  add_library(bit::tools::independence ALIAS tools_independence)

endif()

#-----------------------------------------------------------------------------
# bit::tools : Unit Tests
#-----------------------------------------------------------------------------

# if( BIT_TOOLS_COMPILE_UNIT_TESTS )
#
#   add_subdirectory(test)
#
# endif()

#-----------------------------------------------------------------------------
# bit::tools : Export
#-----------------------------------------------------------------------------

include(ExportLibrary)

if( EXISTS "$ENV{BIT_HOME}" )
  set(CMAKE_INSTALL_PREFIX "$ENV{BIT_HOME}")
endif()

export_library( TARGETS tools
                PACKAGE Tools
                VERSION ${BIT_TOOLS_VERSION}
                MAJOR_VERSION ${BIT_TOOLS_VERSION_MAJOR}
                MINOR_VERSION ${BIT_TOOLS_VERSION_MINOR}
                INCLUDE_PATHS "${CMAKE_CURRENT_LIST_DIR}/include"
                              "${CMAKE_CURRENT_BINARY_DIR}/include"
                NAMESPACE "bit::"
                PREFIX_PACKAGE )
