#include <bit/tools/args/arg_suggestor.hpp>

#include <algorithm>
#include <memory>

//----------------------------------------------------------------------------
// levenshtein distances
//----------------------------------------------------------------------------

std::size_t bit::tools::levenshtein_distance( stl::string_view lhs,
                                              stl::string_view rhs )
  noexcept
{
  // algorithm from https://en.wikipedia.org/wiki/Damerau%E2%80%93Levenshtein_distance

  const auto n = lhs.size();
  const auto m = rhs.size();
  const auto size = (n * m);

  const auto d = std::make_unique<std::size_t[]>(size);

  for(auto i = 0u; i < size; ++i) {
    d[i] = 0;
  }

  for( std::size_t i = 1, im = 0; i < m; ++i, ++im ) {
     for( std::size_t j = 1, jn = 0; j < n; ++j, ++jn ) {
        if (lhs[jn] == rhs[im]) {
           d[(i * n) + j] = d[((i - 1) * n) + (j - 1)];
        } else {
           d[(i * n) + j] = std::min(d[(i - 1) * n + j] + 1, // deletion
                                std::min(d[i * n + (j - 1)] + 1, // insertion
                                    d[(i - 1) * n + (j - 1)] + 1)); // substitution
        }
     }
  }

  return d[n * m - 1];
}

//----------------------------------------------------------------------------

std::size_t bit::tools::damerau_levenshtien_distance( stl::string_view lhs,
                                                      stl::string_view rhs )
  noexcept
{
  // algorithm from https://en.wikipedia.org/wiki/Levenshtein_distance

  const auto n = lhs.size();
  const auto m = rhs.size();
  const auto size = (n * m);

  const auto d = std::make_unique<std::size_t[]>(size);

  for(auto i = 0u; i < size; ++i) {
    d[i] = 0;
  }

  for( std::size_t i = 1, im = 0; i < m; ++i, ++im ) {
     for( std::size_t j = 1, jn = 0; j < n; ++j, ++jn ) {
        if (lhs[jn] == rhs[im]) {
           d[(i * n) + j] = d[((i - 1) * n) + (j - 1)];
        } else {
           d[(i * n) + j] = std::min(d[(i - 1) * n + j] + 1, // deletion
                                std::min(d[i * n + (j - 1)] + 1, // insertion
                                    d[(i - 1) * n + (j - 1)] + 1)); // substitution
        }
        if( i > 1 && j > 1 && lhs[i] == rhs[j-1] && lhs[i-1] == rhs[j] ) {
          d[(i * n) + j] = std::min(d[ (i * n) + j ], d[ (i - 2) * n + j - 2] + 1);
        }
     }
  }

  return d[n * m - 1];
}

