#ifndef BIT_TOOLS_DETAIL_PROCESSOR_INL
#define BIT_TOOLS_DETAIL_PROCESSOR_INL

inline bit::stl::string_view bit::tools::processor::cpu_vendor()
  const noexcept
{
  return m_vendor_string;
}

inline bit::stl::string_view bit::tools::processor::cpu_brand()
  const noexcept
{
  return m_brand_string;
}

//---------------------------------------------------------------------------

inline bool bit::tools::processor::is_RDTSC_supported()
  const noexcept
{
  return m_has_RDTSC;
}

inline bool bit::tools::processor::is_CMOV_supported()
  const noexcept
{
  return m_has_CMOV;
}

inline bool bit::tools::processor::is_FCMOV_supported()
  const noexcept
{
  return m_has_FCMOV;
}

inline bool bit::tools::processor::is_mmx_supported()
  const noexcept
{
  return m_has_MMX;
}

inline bool bit::tools::processor::is_sse_supported()
  const noexcept
{
  return m_has_SSE;
}

inline bool bit::tools::processor::is_sse2_supported()
  const noexcept
{
  return m_has_SSE2;
}

inline bool bit::tools::processor::is_sse3_supported()
  const noexcept
{
  return m_has_SSE3;
}

inline bool bit::tools::processor::is_sse4_1_supported()
  const noexcept
{
  return m_has_SSE4_1;
}

inline bool bit::tools::processor::is_sse4_2_supported()
  const noexcept
{
  return m_has_SSE4_2;
}

inline bool bit::tools::processor::is_avx_supported()
  const noexcept
{
  return m_has_AVX;
}

inline bool bit::tools::processor::is_f16c_supported()
  const noexcept
{
  return m_has_f16c;
}

inline bool bit::tools::processor::is_rdrand_supported()
  const noexcept
{
  return m_has_rdrand;
}

inline bool bit::tools::processor::is_3dnow_supported()
  const noexcept
{
  return m_is_amd && m_has_3DNow; // (3DNow is an AMD Extension)
}

inline bool bit::tools::processor::is_hyper_threading_supported()
  const noexcept
{
  return m_has_HT;
}

//---------------------------------------------------------------------------

inline std::size_t bit::tools::processor::logical_processors()
  const noexcept
{
  return m_logical_cores;
}

#endif /* BIT_TOOLS_DETAIL_PROCESSOR_INL */
