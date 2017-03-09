#ifndef BIT_TOOLS_DETAIL_ARG_VECTOR_INL
#define BIT_TOOLS_DETAIL_ARG_VECTOR_INL

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
