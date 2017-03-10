cmake_minimum_required(VERSION 3.1)

enable_testing()

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake/modules")

include(AddIndependenceCheck)
include(GitBuildInformation)
include(MakeVersionHeader)

# find_package(Bit 0.2.0 COMPONENTS Stl Math EXACT REQUIRED QUIET)

# Temporary hack while FindBit.cmake is being tuned
include("$ENV{BIT_HOME}/Stl-0.2/lib/StlTargets.cmake")

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

git_build_information( MINOR_VARIABLE BIT_TOOLS_VERSION_MINOR
                       PATCH_VARIABLE BIT_TOOLS_VERSION_PATCH
                       BUILD_VARIABLE BIT_TOOLS_BUILD_NUMBER
                       BRANCH_VARIABLE BIT_TOOLS_BRANCH
                       HASH 3990dd405eb57b9b06a0d54a7efd567b86c1ed01
)

set(BIT_TOOLS_VERSION_MAJOR 0 CACHE STRING "major version of bit::stl" FORCE)
set(BIT_TOOLS_VERSION_MINOR ${BIT_TOOLS_VERSION_MINOR} CACHE STRING "minor version of bit::stl" FORCE)
set(BIT_TOOLS_VERSION_PATCH ${BIT_TOOLS_VERSION_PATCH} CACHE STRING "patch version of bit::stl" FORCE)
set(BIT_TOOLS_VERSION "${BIT_TOOLS_VERSION_MAJOR}.${BIT_TOOLS_VERSION_MINOR}.${BIT_TOOLS_VERSION_PATCH}" CACHE STRING "version of bit::stl" FORCE)
set(BIT_TOOLS_BUILD_NUMBER "${BIT_TOOLS_BUILD_NUMBER}" CACHE STRING "build number of bit::stl" FORCE)

message(STATUS "bit::stl ${BIT_TOOLS_VERSION} (${BIT_TOOLS_BRANCH} ${BIT_TOOLS_BUILD_NUMBER})")

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

include_directories("${CMAKE_CURRENT_BINARY_DIR}/include")

set(headers
  include/bit/tools/arg_vector.hpp
  include/bit/tools/arg_suggestor.hpp
)

set(sources
  src/bit/tools/arg_suggestor.cpp
)

add_library(tools ${sources})
add_library(bit::tools ALIAS tools)
target_link_libraries(tools PRIVATE bit::stl)

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

# export_library( TARGETS tools
#                 PACKAGE Tools
#                 VERSION ${BIT_TOOLS_VERSION}
#                 MAJOR_VERSION ${BIT_TOOLS_VERSION_MAJOR}
#                 MINOR_VERSION ${BIT_TOOLS_VERSION_MINOR}
#                 INCLUDE_PATHS "${CMAKE_CURRENT_LIST_DIR}/include"
#                               "${CMAKE_CURRENT_BINARY_DIR}/include"
#                 NAMESPACE "bit::"
#                 PREFIX_PACKAGE )
