/**
 * \file cpuid.hpp
 *
 * \brief This header contains utilities for calling cpuid operations.
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */

#ifndef BIT_TOOLS_CPUID_HPP
#define BIT_TOOLS_CPUID_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif

#include <bit/stl/stddef.hpp>
#include <bit/stl/assert.hpp>

// If compiling on MSVC for windows
#if defined(BIT_COMPILER_MSVC) && defined(BIT_PLATFORM_WINDOWS)
#  include <intrin.h>
#endif

namespace bit {
  namespace tools {

    //------------------------------------------------------------------------
    // Enumerations
    //------------------------------------------------------------------------

    /// \enum cpuid_functions
    ///
    /// \brief the function numbers for CPUID calls
    enum cpuid_functions
    {
      vendor_id        = 0,
      processor_info   = 1,
      cache_info       = 2,
      processor_serial = 3,
    };

    //------------------------------------------------------------------------
    // CPUID Structures and Functions
    //------------------------------------------------------------------------

    /// \struct bit::cpuid_result
    ///
    /// \brief the result of a CPUID command
    struct cpuid_info
    {
      stl::u32 EAX, EBX, ECX, EDX;
    };

    /// \brief Checks if the CPU supports cpuid
    ///
    /// \return True if the CPU supports cpuid
    bool is_cpuid_supported() noexcept;

    /// \brief Executes the cpuid instruction, storing the result in \a result
    ///
    /// \param [out] result      Where to store the result of the instruction
    /// \param [in]  function    First parameter to the CPUID instruction
    /// \param [in]  subfunction Second parameter to the CPUID instruction
    void execute_cpuid( cpuid_info* result,
                        stl::u32 function,
                        stl::u32 subfunction = 0 );

  } // namespace tools
} // namespace bit

#endif /* BIT_TOOLS_CPUID_HPP */
