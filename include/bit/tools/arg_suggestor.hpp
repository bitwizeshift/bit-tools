#ifndef BIT_TOOLS_ARG_SUGGESTOR_HPP
#define BIT_TOOLS_ARG_SUGGESTOR_HPP

#include <bit/stl/string_view.hpp>

#include <initializer_list>
#include <string>
#include <vector>
#include <map>
#include <bitset>

namespace bit {
  namespace tools {

    std::size_t levenshtein_distance( stl::string_view lhs, stl::string_view rhs ) noexcept;
    std::size_t damerau_levenshtien_distance( stl::string_view lhs, stl::string_view rhs ) noexcept;

    template<typename CharT, typename Traits = std::char_traits<char>>
    class arg_suggestor
    {
      //----------------------------------------------------------------------
      // Public Member Types
      //----------------------------------------------------------------------
    public:

      using size_type        = std::size_t;
      using distance_fn_type = std::size_t(*)(stl::string_view,stl::string_view);

      //----------------------------------------------------------------------
      // Constructors
      //----------------------------------------------------------------------
    public:

      ///
      ///
      /// \param first
      /// \param last
      template<typename InputIt>
      explicit arg_suggestor( InputIt first, InputIt last );

      /// \brief
      ///
      /// \param ilist
      explicit arg_suggestor( std::initializer_list<std::string> ilist );

      //----------------------------------------------------------------------
      // Capacity
      //----------------------------------------------------------------------
    public:

      bool empty() const noexcept;
      size_type size() const noexcept;

      //----------------------------------------------------------------------
      // Observers
      //----------------------------------------------------------------------
    public:

      stl::string_view suggest( stl::string_view input ) const;

      std::vector<stl::string_view> suggestions( stl::string_view input ) const;

    private:

      using bits            = std::bitset<27>;
      using match_container = std::vector<std::string>;


      distance_fn_type m_distance_fn; ///< The function used for computing distance
      std::map<bits,match_container> m_args;
    };

  } // namespace tools
} // namespace bit

#endif // BIT_TOOLS_ARG_SUGGESTOR_HPP
