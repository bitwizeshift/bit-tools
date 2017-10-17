cmake_minimum_required(VERSION 3.1)

enable_testing()

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake/modules")

include(AddHeaderSelfContainmentTest)
include(GitBuildInformation)
include(MakeVersionHeader)

find_package(Bit 1.1 EXACT REQUIRED QUIET COMPONENTS Stl)

#-----------------------------------------------------------------------------
# Project Setup
#-----------------------------------------------------------------------------

option(BIT_TOOLS_COMPILE_HEADER_SELF_CONTAINMENT_TESTS "Include each header independently in a .cpp file to determine header self-containment tests" off)
option(BIT_TOOLS_COMPILE_UNIT_TESTS "Compile and run the unit tests for this library" off)

project("BitTools")

if( CMAKE_BUILD_TYPE STREQUAL "" )
  message(STATUS "CMAKE_BUILD_TYPE not set; defaulting to 'Debug'")
  set(CMAKE_BUILD_TYPE DEBUG)
endif()

#-----------------------------------------------------------------------------
# Version Info
#-----------------------------------------------------------------------------

set(BIT_TOOLS_VERSION_MAJOR 0 CACHE STRING "major version of bit::tools" FORCE)
set(BIT_TOOLS_VERSION_MINOR 5 CACHE STRING "minor version of bit::tools" FORCE)
set(BIT_TOOLS_VERSION_PATCH 1 CACHE STRING "patch version of bit::tools" FORCE)
set(BIT_TOOLS_VERSION "${BIT_TOOLS_VERSION_MAJOR}.${BIT_TOOLS_VERSION_MINOR}.${BIT_TOOLS_VERSION_PATCH}" CACHE STRING "version of bit::tools" FORCE)

message(STATUS "bit::tools ${BIT_TOOLS_VERSION}")

#-----------------------------------------------------------------------------
# bit::tools
#-----------------------------------------------------------------------------

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED true)

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
  include/bit/tools/args/arg_parser.hpp
  include/bit/tools/config/type_loader.hpp
)

set(sources
  src/bit/tools/args/arg_suggestor.cpp
)

add_library(bit_tools ${sources})
add_library(bit::tools ALIAS bit_tools)
target_link_libraries(bit_tools PUBLIC bit::stl)

target_include_directories(bit_tools INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>
  $<INSTALL_INTERFACE:include>
)
target_compile_definitions(bit_tools INTERFACE
  $<$<CONFIG:DEBUG>:DEBUG>
  $<$<CONFIG:RELEASE>:DEBUG RELEASE>
)

#-----------------------------------------------------------------------------
# bit::tools : Independence Tests
#-----------------------------------------------------------------------------

if( BIT_TOOLS_COMPILE_HEADER_SELF_CONTAINMENT_TESTS )

  add_header_self_containment_test(bit_tools_header_self_containment_test ${headers})
  add_library(bit::tools::header_self_containment_test ALIAS bit_tools_header_self_containment_test)

  target_include_directories(bit_tools_header_self_containment_test PRIVATE
    $<TARGET_PROPERTY:bit_tools,INCLUDE_DIRECTORIES>
  )
  target_compile_options(bit_tools_header_self_containment_test PRIVATE
    $<$<CONFIG:DEBUG>:-DDEBUG>
    $<$<CONFIG:RELEASE>:-DNDEBUG -DRELEASE>
  )

  if( "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    target_compile_options(bit_stl_header_self_containment_test PRIVATE -Wall -pedantic)
  elseif( "${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" )
    target_compile_options(bit_stl_header_self_containment_test PRIVATE -Wall -pedantic)
  elseif( "${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC" )
    # TODO: Determine MSVC necessary compiler flags
  endif()

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

export_library( TARGETS bit_tools
                PACKAGE Tools
                VERSION ${BIT_TOOLS_VERSION}
                MAJOR_VERSION ${BIT_TOOLS_VERSION_MAJOR}
                MINOR_VERSION ${BIT_TOOLS_VERSION_MINOR}
                INCLUDE_PATHS "${CMAKE_CURRENT_LIST_DIR}/include"
                              "${CMAKE_CURRENT_BINARY_DIR}/include"
                NAMESPACE "bit::"
                PREFIX_PACKAGE )
