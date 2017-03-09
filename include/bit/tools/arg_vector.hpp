#ifndef BIT_TOOLS_ARG_VECTOR_HPP
#define BIT_TOOLS_ARG_VECTOR_HPP

#include <bit/stl/string_view.hpp>

#include <iterator>

namespace bit {
  namespace tools {

    //////////////////////////////////////////////////////////////////////////
    /// \brief An iterator for the \ref arg_vector class.
    ///
    /// This is a random-access iterator which allows simple traversal over
    /// all entries
    //////////////////////////////////////////////////////////////////////////
    class arg_vector_iterator
    {
      //----------------------------------------------------------------------
      // Public Member Types
      //----------------------------------------------------------------------
    public:

      using argc_type         = int;
      using argv_type         = const char* const *;
      using value_type        = stl::string_view;
      using reference         = value_type&;
      using pointer           = value_type*;
      using size_type         = std::size_t;
      using difference_type   = std::ptrdiff_t;
      using iterator_category = std::random_access_iterator_tag;

      //----------------------------------------------------------------------
      // Constructor
      //----------------------------------------------------------------------
    public:

      /// \brief Constructs an arg_vector_iterator from a given argv
      ///
      /// \param argv an arg vector from main
      explicit arg_vector_iterator( argv_type argv ) noexcept;

      //----------------------------------------------------------------------
      // Element Access
      //----------------------------------------------------------------------
    public:

      /// \brief Accesses the underlying string_view
      ///
      /// \return reference to the underlying argument string_view
      reference operator*() noexcept;

      /// \brief Accesses the underlying string_view
      ///
      /// \return pointer to the underlying argument string_view
      pointer operator->() noexcept;

      //----------------------------------------------------------------------
      // Iteration
      //----------------------------------------------------------------------
    public:

      arg_vector_iterator& operator++() noexcept;
      arg_vector_iterator operator++(int) noexcept;
      arg_vector_iterator& operator--() noexcept;
      arg_vector_iterator operator--(int) noexcept;

      arg_vector_iterator& operator+=( difference_type n ) noexcept;
      arg_vector_iterator& operator-=( difference_type n ) noexcept;

      //----------------------------------------------------------------------
      // Private Member Types
      //----------------------------------------------------------------------
    private:

      argv_type        m_current;
      stl::string_view m_view;

      friend bool operator==( const arg_vector_iterator&, const arg_vector_iterator& ) noexcept;
      friend bool operator<( const arg_vector_iterator&, const arg_vector_iterator& ) noexcept;
    };

    //------------------------------------------------------------------------
    // Iteration
    //------------------------------------------------------------------------

    arg_vector_iterator operator+( const arg_vector_iterator& lhs, std::ptrdiff_t n ) noexcept;
    arg_vector_iterator operator+( std::ptrdiff_t n, const arg_vector_iterator& lhs ) noexcept;
    arg_vector_iterator operator-( const arg_vector_iterator& lhs, std::ptrdiff_t n ) noexcept;

    //------------------------------------------------------------------------
    // Comparison
    //------------------------------------------------------------------------

    bool operator==( const arg_vector_iterator& lhs, const arg_vector_iterator& rhs ) noexcept;
    bool operator!=( const arg_vector_iterator& lhs, const arg_vector_iterator& rhs ) noexcept;
    bool operator<( const arg_vector_iterator& lhs, const arg_vector_iterator& rhs ) noexcept;
    bool operator>( const arg_vector_iterator& lhs, const arg_vector_iterator& rhs ) noexcept;
    bool operator<=( const arg_vector_iterator& lhs, const arg_vector_iterator& rhs ) noexcept;
    bool operator>=( const arg_vector_iterator& lhs, const arg_vector_iterator& rhs ) noexcept;

    //////////////////////////////////////////////////////////////////////////
    /// \brief A container class used for managing the \c argc and \c argv
    ///        parameters from main
    ///
    /// This provides a bounds-safe modern mechanism for extracting each
    /// argument as immutable string_view entries. This also adds an iterator
    /// interface, allowing simple iteration over all the arguments
    //////////////////////////////////////////////////////////////////////////
    class arg_vector
    {
      //----------------------------------------------------------------------
      // Public Member Types
      //----------------------------------------------------------------------
    public:

      using argc_type = int;
      using argv_type = const char* const * const;

      using value_type = stl::string_view;

      using size_type = std::size_t;
      using index_type = std::ptrdiff_t;

      using const_iterator = arg_vector_iterator;
      using const_reverse_iterator = std::reverse_iterator<const_iterator>;
      using iterator = const_iterator;
      using reverse_iterator = const_reverse_iterator;

      //----------------------------------------------------------------------
      // Constructors
      //----------------------------------------------------------------------
    public:

      /// \brief Constructs an arg_vector given the \p argc and \p argv
      ///        from main
      ///
      /// \param argc the argument count
      /// \param argv the argument vector
      explicit arg_vector( argc_type argc, argv_type argv ) noexcept;

      /// \brief Copy-constructs an arg_vector from another arg_vector
      ///
      /// \param other the other arg_vector to copy
      arg_vector( const arg_vector& other ) noexcept = default;

      /// \brief Move-constructs an arg_vector from another arg_vector
      ///
      /// \param other the other arg_vector to move
      arg_vector( arg_vector&& other ) noexcept = default;

      /// \brief Copy-assigns an arg_vector from another arg_vector
      ///
      /// \param other the other arg_vector to copy
      /// \return reference to \c (*this)
      arg_vector& operator=( const arg_vector& other ) noexcept = default;

      /// \brief Move-assigns an arg_vector from another arg_vector
      ///
      /// \param other the other arg_vector to move
      /// \return reference to \c (*this)
      arg_vector& operator=( arg_vector&& other ) noexcept = default;

      //----------------------------------------------------------------------
      // Capacity
      //----------------------------------------------------------------------
    public:

      /// \brief Returns whether the arg_vector contains entries
      ///
      /// \return \c true when the arg_vector doesn't contain any entries
      bool empty() const noexcept;

      /// \brief Retrieves the number of entries in this arg_vector
      ///
      /// \return the number of entries in this arg_vector
      size_type size() const noexcept;

      //----------------------------------------------------------------------
      // Element Access
      //----------------------------------------------------------------------
    public:

      /// \brief Gets a pointer to the underlying data of this arg_vector
      ///
      /// \return a pointer to the underlying arg_vector
      argv_type data() const noexcept;

      /// \brief Retrieves the element at index \p n, with bounds checking
      ///
      /// \throws std::out_of_range if index is out of range
      ///
      /// \return a string_view of the entry at index \p n
      value_type at( index_type n ) const;

      /// \brief Retrieves the element at index \p n
      ///
      /// \return a string_view of the entry at index \p n
      value_type operator[]( index_type n ) const noexcept;

      /// \brief Retrieves the program name (argument 0) from the arg vector
      ///
      /// \note In most circumstances arg 0 is the program name, however it
      ///       may also be the argument provided to an execvp call.
      ///
      /// \return the string_view of the program name
      value_type program() const noexcept;

      /// \brief Retrieves the argument and index \p n from the arg vector
      ///
      /// This ignores arg 0 which otherwise will be the program name
      ///
      /// \return a string_view of the argument at index \p n
      value_type arg( index_type n ) const noexcept;

      //----------------------------------------------------------------------
      // Iterators
      //----------------------------------------------------------------------
    public:

      /// \brief Retrieves the begin iterator
      ///
      /// \return the begin iterator
      iterator begin() const noexcept;

      /// \brief Retrieves the end iterator
      ///
      /// \return the end iterator
      iterator end() const noexcept;

      /// \copydoc arg_vector::begin()
      const_iterator cbegin() const noexcept;

      /// \copydoc arg_vector::end()
      const_iterator cend() const noexcept;

      //----------------------------------------------------------------------

      /// \brief Retrieves the beginning reverse iterator
      ///
      /// \return the begin reverse iterator
      reverse_iterator rbegin() const noexcept;

      /// \brief Retrieves the ending reverse iterator
      ///
      /// \return the end reverse iterator
      reverse_iterator rend() const noexcept;

      /// \copydoc arg_vector::rbegin()
      const_reverse_iterator crbegin() const noexcept;

      /// \copydoc arg_vector::rend()
      const_reverse_iterator crend() const noexcept;

      //----------------------------------------------------------------------
      // Private Members
      //----------------------------------------------------------------------
    private:

      argv_type m_argv; ///< The arg vector
      argc_type m_argc; ///< The arg count
    };

  } // namespace tools
} // namespace bit

//============================================================================
// arg_vector_iterator
//============================================================================

//----------------------------------------------------------------------------
// Constructors
//----------------------------------------------------------------------------

inline bit::tools::arg_vector_iterator::arg_vector_iterator( argv_type argv )
  noexcept
  : m_current(argv),
    m_view(*argv)
{

}

//----------------------------------------------------------------------------
// Element Access
//----------------------------------------------------------------------------

inline bit::tools::arg_vector_iterator::reference
  bit::tools::arg_vector_iterator::operator*()
  noexcept
{
  return m_view;
}

//----------------------------------------------------------------------------

inline bit::tools::arg_vector_iterator::pointer
  bit::tools::arg_vector_iterator::operator->()
  noexcept
{
  return &m_view;
}

//----------------------------------------------------------------------------
// Iteration
//----------------------------------------------------------------------------

inline bit::tools::arg_vector_iterator&
  bit::tools::arg_vector_iterator::operator++()
  noexcept
{
  ++m_current;
  m_view = *m_current;
  return (*this);
}

inline bit::tools::arg_vector_iterator
  bit::tools::arg_vector_iterator::operator++(int)
  noexcept
{
  auto cur = (*this);
  ++m_current;
  m_view = *m_current;
  return cur;
}

//----------------------------------------------------------------------------

inline bit::tools::arg_vector_iterator&
  bit::tools::arg_vector_iterator::operator--()
  noexcept
{
  --m_current;
  m_view = *m_current;
  return (*this);
}

inline bit::tools::arg_vector_iterator
  bit::tools::arg_vector_iterator::operator--(int)
  noexcept
{
  auto cur = (*this);
  --m_current;
  m_view = *m_current;
  return cur;
}

//----------------------------------------------------------------------------

inline bit::tools::arg_vector_iterator&
  bit::tools::arg_vector_iterator::operator+=( difference_type n )
  noexcept
{
  m_current += n;
  m_view = *m_current;
  return (*this);
}

inline bit::tools::arg_vector_iterator&
  bit::tools::arg_vector_iterator::operator-=( difference_type n )
  noexcept
{
  m_current -= n;
  m_view = *m_current;
  return (*this);
}

//----------------------------------------------------------------------------

//============================================================================
// arg_vector
//============================================================================

inline bit::tools::arg_vector_iterator
  bit::tools::operator+( const arg_vector_iterator& lhs, std::ptrdiff_t rhs )
  noexcept
{
  return arg_vector_iterator(lhs)+=rhs;
}

inline bit::tools::arg_vector_iterator
  bit::tools::operator+( std::ptrdiff_t lhs, const arg_vector_iterator& rhs )
  noexcept
{
  return arg_vector_iterator(rhs)+=lhs;
}

//----------------------------------------------------------------------------

inline bit::tools::arg_vector_iterator
  bit::tools::operator-( const arg_vector_iterator& lhs, std::ptrdiff_t rhs )
  noexcept
{
  return arg_vector_iterator(lhs)-=rhs;
}

//----------------------------------------------------------------------------
// Comparison
//----------------------------------------------------------------------------

inline bool
  bit::tools::operator==( const arg_vector_iterator& lhs, const arg_vector_iterator& rhs )
  noexcept
{
  return lhs.m_current == rhs.m_current;
}

//----------------------------------------------------------------------------

inline bool
  bit::tools::operator!=( const arg_vector_iterator& lhs, const arg_vector_iterator& rhs )
  noexcept
{
  return !(lhs == rhs);
}

//----------------------------------------------------------------------------

inline bool
  bit::tools::operator<( const arg_vector_iterator& lhs, const arg_vector_iterator& rhs )
  noexcept
{
  return (lhs.m_current < rhs.m_current);
}

//----------------------------------------------------------------------------

inline bool
  bit::tools::operator>( const arg_vector_iterator& lhs, const arg_vector_iterator& rhs )
  noexcept
{
  return (rhs < lhs);
}

//----------------------------------------------------------------------------

inline bool
  bit::tools::operator<=( const arg_vector_iterator& lhs, const arg_vector_iterator& rhs )
  noexcept
{
  return !(rhs < lhs);
}

//----------------------------------------------------------------------------

inline bool
  bit::tools::operator>=( const arg_vector_iterator& lhs, const arg_vector_iterator& rhs )
  noexcept
{
  return !(lhs < rhs);
}


//----------------------------------------------------------------------------
// Constructors
//----------------------------------------------------------------------------

inline bit::tools::arg_vector::arg_vector( argc_type argc, argv_type argv )
  noexcept
  : m_argv(argv),
    m_argc(argc)
{

}

//----------------------------------------------------------------------------
// Capacity
//----------------------------------------------------------------------------

inline bool bit::tools::arg_vector::empty()
  const noexcept
{
  return m_argc == 0;
}

//----------------------------------------------------------------------------

inline bit::tools::arg_vector::size_type bit::tools::arg_vector::size()
  const noexcept
{
  return m_argc;
}

//----------------------------------------------------------------------------
// Element Access
//----------------------------------------------------------------------------

inline bit::tools::arg_vector::argv_type bit::tools::arg_vector::data()
  const noexcept
{
  return m_argv;
}

//----------------------------------------------------------------------------

inline bit::tools::arg_vector::value_type
  bit::tools::arg_vector::at( index_type n )
  const
{
  if( n < 0 || n >= m_argc ) throw std::out_of_range("arg_vector::at: index out of range");

  return m_argv[n];
}

//----------------------------------------------------------------------------

inline bit::tools::arg_vector::value_type bit::tools::arg_vector::program()
  const noexcept
{
  return m_argv[0];
}

//----------------------------------------------------------------------------

inline bit::tools::arg_vector::value_type
  bit::tools::arg_vector::arg( index_type n )
  const noexcept
{
  return m_argv[1 + n];
}

//----------------------------------------------------------------------------
// Iterators
//----------------------------------------------------------------------------

inline bit::tools::arg_vector::iterator
  bit::tools::arg_vector::begin()
  const noexcept
{
  return iterator{&m_argv[0]};
}

//----------------------------------------------------------------------------

inline bit::tools::arg_vector::iterator
  bit::tools::arg_vector::end()
  const noexcept
{
  return iterator{&m_argv[m_argc]};
}

//----------------------------------------------------------------------------

inline bit::tools::arg_vector::reverse_iterator
  bit::tools::arg_vector::rbegin()
  const noexcept
{
  return reverse_iterator{iterator{&m_argv[m_argc-1]}};
}

//----------------------------------------------------------------------------

inline bit::tools::arg_vector::reverse_iterator
  bit::tools::arg_vector::rend()
  const noexcept
{
  return reverse_iterator{iterator{&m_argv[-1]}};
}

//----------------------------------------------------------------------------

inline bit::tools::arg_vector::const_iterator
  bit::tools::arg_vector::cbegin()
  const noexcept
{
  return const_iterator{&m_argv[0]};
}

//----------------------------------------------------------------------------

inline bit::tools::arg_vector::const_iterator
  bit::tools::arg_vector::cend()
  const noexcept
{
  return const_iterator{&m_argv[m_argc]};
}

//----------------------------------------------------------------------------

inline bit::tools::arg_vector::const_reverse_iterator
  bit::tools::arg_vector::crbegin()
  const noexcept
{
  return const_reverse_iterator{const_iterator{&m_argv[m_argc-1]}};
}

//----------------------------------------------------------------------------

inline bit::tools::arg_vector::const_reverse_iterator
  bit::tools::arg_vector::crend()
  const noexcept
{
  return const_reverse_iterator{const_iterator{&m_argv[-1]}};
}

#endif
