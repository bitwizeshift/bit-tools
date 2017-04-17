#ifndef BIT_TOOLS_ARG_PARSER_HPP
#define BIT_TOOLS_ARG_PARSER_HPP

#include "arg_vector.hpp"

#include <bit/stl/utility.hpp>
#include <bit/stl/hashed_string_view.hpp>
#include <bit/stl/casts.hpp>
#include <bit/stl/iterator.hpp>

#include <vector>

namespace bit {
  namespace tools {
    namespace detail {

      template<typename CharT, typename Traits>
      struct basic_arg_node
      {
        enum class node_type
        {
          single, ///< Single argument
          multi,  ///< Multi argument
          option, ///< Optional argument
          alias,  ///< Alias argument
        };

        using string_type = stl::basic_string_view<CharT,Traits>;
        using vector_type = basic_arg_vector<CharT,Traits>;

        struct empty_type{};
        union storage_type {
          string_type     single;
          vector_type     multi;
          bool            option;
          basic_arg_node* alias;
          empty_type      empty;

          storage_type() : empty(){}
        };

        storage_type    storage; ///< The storage for the arg
        basic_arg_node* next;    ///< The next node in the chain
        string_type     flag;    ///< The flag
        node_type       type;    ///< The type of the node
        bool            set;     ///< Whether this node has been set
      };

    } // namespace detail

    //////////////////////////////////////////////////////////////////////////
    /// \brief A set of arguments that can be parsed
    ///
    /// This keeps an intrusively linked list of all arguments
    ///
    /// \tparam CharT the type of the char
    /// \tparam Traits the type of the traits
    //////////////////////////////////////////////////////////////////////////
    template<typename CharT, typename Traits = std::char_traits<CharT>>
    class basic_arg_set
    {
      static_assert( std::is_same<CharT,typename Traits::char_type>::value, "Traits::char_type must be the same as CharT");

      using unmatched_type = std::vector<stl::basic_string_view<CharT,Traits>>;

      //----------------------------------------------------------------------
      // Public Member Types
      //----------------------------------------------------------------------
    public:

      using string_type = stl::basic_string_view<CharT,Traits>;
      using size_type   = std::size_t;

      using unmatched_range = stl::range<typename unmatched_type::iterator,
                                         typename unmatched_type::iterator>;

      //----------------------------------------------------------------------
      // Constructor
      //----------------------------------------------------------------------
    public:

      /// \brief Default-constructs a basic_arg_set
      explicit basic_arg_set() noexcept;

      basic_arg_set( const basic_arg_set& ) = delete;
      basic_arg_set( basic_arg_set&& ) = delete;

      //----------------------------------------------------------------------
      // Observers
      //----------------------------------------------------------------------
    public:

      /// \brief Returns whether or not this basic_arg_set is empty
      ///
      /// \return \c true if this basic_arg_set is empty
      bool empty() const noexcept;

      /// \brief Returns the number of args in this basic_arg_set
      ///
      /// \return the number of arguments
      size_type size() const noexcept;

      /// \brief Returns the range of unmatched arguments
      ///
      /// \return the range of unmatched arguments
      unmatched_range unmatched() const noexcept;

      //----------------------------------------------------------------------
      // Private Member Types
      //----------------------------------------------------------------------
    private:

      using node_type = detail::basic_arg_node<CharT,Traits>;

      //----------------------------------------------------------------------
      // Private Members
      //----------------------------------------------------------------------
    private:

      // todo: Possible optimization: Forego any heap allocation by creating
      //       a custom filter iterator that iterates unmatched arguments

      node_type*     m_head;      ///< The type of the node
      unmatched_type m_unmatched; ///< A vector containing unmatched arguments

      template<typename C, typename T>
      friend bool parse_arguments( basic_arg_set<C,T>* arg_set,
                                   basic_arg_vector<C,T> args );
    };

    //////////////////////////////////////////////////////////////////////////
    ///
    ///
    //////////////////////////////////////////////////////////////////////////
    template<typename CharT, typename Traits = std::char_traits<CharT>>
    class basic_single_arg
    {
      static_assert( std::is_same<CharT,typename Traits::char_type>::value, "Traits::char_type must be the same as CharT");

      //----------------------------------------------------------------------
      // Public Member Types
      //----------------------------------------------------------------------
    public:

      using set_type = basic_arg_set<CharT,Traits>;
      using key_type = stl::basic_string_view<CharT,Traits>;
      using value_type = stl::basic_string_view<CharT,Traits>;

      //----------------------------------------------------------------------
      // Constructors
      //----------------------------------------------------------------------
    public:

      /// \brief Constructs a basic_single_arg with a given parent
      ///
      /// \param parent the parent arg set
      /// \param flag the flag to use
      basic_single_arg( set_type& parent, key_type flag ) noexcept;

      /// \brief Constructs a basic_single_arg with a given parent
      ///
      /// \param parent the parent arg set
      /// \param flag the flag to use
      /// \param default_value the default value to asign
      basic_single_arg( set_type& parent, key_type flag, value_type default_value ) noexcept;

      //----------------------------------------------------------------------
      // Observers
      //----------------------------------------------------------------------
    public:

      /// \brief Gets the set value
      ///
      /// \return the value
      value_type value() const noexcept;

      /// \brief Queries whether this basic_single_arg has been set
      ///
      /// This can be used to determine whether a flag default-asigned or
      /// specified on command-line
      ///
      /// \return \c true if the value was set
      bool is_set() const noexcept;

      /// \brief Queries whether this basic_single_arg has been set
      ///
      /// \return \c true if the value was set
      explicit operator bool() const noexcept;

      //----------------------------------------------------------------------
      // Private Member Types
      //----------------------------------------------------------------------
    private:

      using node_type = detail::basic_arg_node<CharT,Traits>;

      //----------------------------------------------------------------------
      // Private Members
      //----------------------------------------------------------------------
    private:

      node_type m_node;
    };

    //////////////////////////////////////////////////////////////////////////
    ///
    ///
    //////////////////////////////////////////////////////////////////////////
    template<typename CharT, typename Traits = std::char_traits<CharT>>
    class basic_multi_arg
    {
      static_assert( std::is_same<CharT,typename Traits::char_type>::value, "Traits::char_type must be the same as CharT");

      //----------------------------------------------------------------------
      // Public Member Types
      //----------------------------------------------------------------------
    public:

      using set_type = basic_arg_set<CharT,Traits>;
      using key_type = stl::basic_string_view<CharT,Traits>;
      using value_type = basic_arg_vector<CharT,Traits>;

      //----------------------------------------------------------------------
      // Constructors
      //----------------------------------------------------------------------
    public:

      /// \brief Constructs a basic_multi_arg with a given parent
      ///
      /// \param parent the parent arg set
      /// \param flag the flag to use
      basic_multi_arg( set_type& parent, key_type flag ) noexcept;

      /// \brief Constructs a basic_multi_arg with a given parent
      ///
      /// \param parent the parent arg set
      /// \param flag the flag to use
      /// \param default_value the default value to asign
      basic_multi_arg( set_type& parent, key_type flag, value_type default_value ) noexcept;

      //----------------------------------------------------------------------
      // Observers
      //----------------------------------------------------------------------
    public:

      /// \brief Gets the set value
      ///
      /// \return the value
      value_type value() const noexcept;

      /// \brief Queries whether this basic_multi_arg has been set
      ///
      /// This can be used to determine whether a flag default-asigned or
      /// specified on command-line
      ///
      /// \return \c true if the value was set
      bool is_set() const noexcept;

      /// \brief Queries whether this basic_multi_arg has been set
      ///
      /// \return \c true if the value was set
      explicit operator bool() const noexcept;

      //----------------------------------------------------------------------
      // Private Member Types
      //----------------------------------------------------------------------
    private:

      using node_type = detail::basic_arg_node<CharT,Traits>;

      //----------------------------------------------------------------------
      // Private Members
      //----------------------------------------------------------------------
    private:

      node_type m_node;
    };

    //////////////////////////////////////////////////////////////////////////
    ///
    ///
    //////////////////////////////////////////////////////////////////////////
    template<typename CharT, typename Traits = std::char_traits<CharT>>
    class basic_option_arg
    {
      static_assert( std::is_same<CharT,typename Traits::char_type>::value, "Traits::char_type must be the same as CharT");

      //----------------------------------------------------------------------
      // Public Member Types
      //----------------------------------------------------------------------
    public:

      using set_type = basic_arg_set<CharT,Traits>;
      using key_type = stl::basic_string_view<CharT,Traits>;
      using value_type = bool;

      //----------------------------------------------------------------------
      // Constructors
      //----------------------------------------------------------------------
    public:

      /// \brief Constructs a basic_option_arg with a given parent
      ///
      /// \param parent the parent arg set
      /// \param flag the flag to use
      basic_option_arg( set_type& parent, key_type flag ) noexcept;

      /// \brief Constructs a basic_option_arg with a given parent
      ///
      /// \param parent the parent arg set
      /// \param flag the flag to use
      /// \param default_value the default value to asign
      basic_option_arg( set_type& parent, key_type flag, value_type default_value ) noexcept;

      //----------------------------------------------------------------------
      // Observers
      //----------------------------------------------------------------------
    public:

      /// \brief Gets the set value
      ///
      /// \return the value
      value_type value() const noexcept;

      /// \brief Queries whether this basic_option_arg has been set
      ///
      /// This can be used to determine whether a flag default-asigned or
      /// specified on command-line
      ///
      /// \return \c true if the value was set
      bool is_set() const noexcept;

      /// \brief Queries whether this basic_option_arg has been set
      ///
      /// \return \c true if the value was set
      explicit operator bool() const noexcept;

      //----------------------------------------------------------------------
      // Private Member Types
      //----------------------------------------------------------------------
    private:

      using node_type = detail::basic_arg_node<CharT,Traits>;

      //----------------------------------------------------------------------
      // Private Members
      //----------------------------------------------------------------------
    private:

      node_type m_node;
    };

    //////////////////////////////////////////////////////////////////////////
    /// \brief Alias argument
    ///
    //////////////////////////////////////////////////////////////////////////
    template<typename CharT, typename Traits = std::char_traits<CharT>>
    class basic_alias_arg
    {
      static_assert( std::is_same<CharT,typename Traits::char_type>::value, "Traits::char_type must be the same as CharT");

      //----------------------------------------------------------------------
      // Public Member Types
      //----------------------------------------------------------------------
    public:

      using set_type = basic_arg_set<CharT,Traits>;
      using key_type = stl::basic_string_view<CharT,Traits>;
      using value_type = basic_alias_arg*;

      //----------------------------------------------------------------------
      // Constructors
      //----------------------------------------------------------------------
    public:

      /// \brief Constructs a basic_alias_arg that aliases another argument
      ///
      /// \param value the argument to alias
      /// \param flag the flag to use
      basic_alias_arg( basic_single_arg<CharT,Traits>& value, key_type flag ) noexcept;

      /// \copydoc basic_alias_arg( basic_single_arg<CharT,Traits>&, key_type flag )
      basic_alias_arg( basic_multi_arg<CharT,Traits>& value, key_type flag ) noexcept;

      /// \copydoc basic_alias_arg( basic_single_arg<CharT,Traits>&, key_type flag)
      basic_alias_arg( basic_option_arg<CharT,Traits>& value, key_type flag ) noexcept;

      /// \copydoc basic_alias_arg( basic_single_arg<CharT,Traits>&, key_type flag )
      basic_alias_arg( basic_alias_arg& value, key_type flag ) noexcept;

      //----------------------------------------------------------------------
      // Private Member Types
      //----------------------------------------------------------------------
    private:

      using node_type = detail::basic_arg_node<CharT,Traits>;

      //----------------------------------------------------------------------
      // Private Members
      //----------------------------------------------------------------------
    private:

      node_type m_node;

      //----------------------------------------------------------------------
      // Private Constructors
      //----------------------------------------------------------------------
    private:

      /// \brief
      ///
      /// \param flag the flag name
      /// \param node the node to point to
      basic_alias_arg( key_type flag, node_type* node ) noexcept;
    };

    //------------------------------------------------------------------------
    // Argument Parsing
    //------------------------------------------------------------------------

    /// \brief Parses all \p args and stores the results in the variable
    ///        pointed to by \p arg_set
    ///
    /// \param arg_set
    /// \param args
    /// \return \c true if parsing was successful
    template<typename CharT, typename Traits>
    bool parse_arguments( basic_arg_set<CharT,Traits>* arg_set,
                          basic_arg_vector<CharT,Traits> args );

    //------------------------------------------------------------------------
    // Type Aliases
    //------------------------------------------------------------------------

    using arg_set    = basic_arg_set<char>;
    using warg_set   = basic_arg_set<wchar_t>;
    using u16arg_set = basic_arg_set<char16_t>;
    using u32arg_set = basic_arg_set<char32_t>;

    //------------------------------------------------------------------------

    using single_arg    = basic_single_arg<char>;
    using wsingle_arg   = basic_single_arg<wchar_t>;
    using u16single_arg = basic_single_arg<char16_t>;
    using u32single_arg = basic_single_arg<char32_t>;

    //------------------------------------------------------------------------

    using multi_arg    = basic_multi_arg<char>;
    using wmulti_arg   = basic_multi_arg<wchar_t>;
    using u16multi_arg = basic_multi_arg<char16_t>;
    using u32multi_arg = basic_multi_arg<char32_t>;

    //------------------------------------------------------------------------

    using option_arg    = basic_option_arg<char>;
    using woption_arg   = basic_option_arg<wchar_t>;
    using u16option_arg = basic_option_arg<char16_t>;
    using u32option_arg = basic_option_arg<char32_t>;

    //------------------------------------------------------------------------

    using alias_arg    = basic_alias_arg<char>;
    using walias_arg   = basic_alias_arg<wchar_t>;
    using u16alias_arg = basic_alias_arg<char16_t>;
    using u32alias_arg = basic_alias_arg<char32_t>;

  } // namespace tools
} // namespace bit

#include "detail/arg_parser.inl"

#endif // BIT_TOOLS_ARG_PARSER_HPP
