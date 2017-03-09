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

#include "detail/arg_vector.inl"

#endif
