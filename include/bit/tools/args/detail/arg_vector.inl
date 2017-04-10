#ifndef BIT_TOOLS_DETAIL_ARG_VECTOR_INL
#define BIT_TOOLS_DETAIL_ARG_VECTOR_INL

//============================================================================
// arg_vector_iterator
//============================================================================

//----------------------------------------------------------------------------
// Constructors
//----------------------------------------------------------------------------

template<typename CharT, typename Traits>
inline bit::tools::arg_vector_iterator<CharT,Traits>::arg_vector_iterator( argv_type argv )
  noexcept
  : m_current(argv)
{

}

//----------------------------------------------------------------------------
// Element Access
//----------------------------------------------------------------------------

template<typename CharT, typename Traits>
inline typename bit::tools::arg_vector_iterator<CharT,Traits>::reference
  bit::tools::arg_vector_iterator<CharT,Traits>::operator*()
  noexcept
{
  return *m_current;
}

//----------------------------------------------------------------------------

template<typename CharT, typename Traits>
inline typename bit::tools::arg_vector_iterator<CharT,Traits>::pointer
  bit::tools::arg_vector_iterator<CharT,Traits>::operator->()
  noexcept
{
  return stl::make_pointer_wrapper<value_type>( *m_current );
}

//----------------------------------------------------------------------------
// Iteration
//----------------------------------------------------------------------------

template<typename CharT, typename Traits>
inline bit::tools::arg_vector_iterator<CharT,Traits>&
  bit::tools::arg_vector_iterator<CharT,Traits>::operator++()
  noexcept
{
  ++m_current;
  return (*this);
}

template<typename CharT, typename Traits>
inline bit::tools::arg_vector_iterator<CharT,Traits>
  bit::tools::arg_vector_iterator<CharT,Traits>::operator++(int)
  noexcept
{
  auto cur = (*this);
  ++m_current;
  return cur;
}

//----------------------------------------------------------------------------

template<typename CharT, typename Traits>
inline bit::tools::arg_vector_iterator<CharT,Traits>&
  bit::tools::arg_vector_iterator<CharT,Traits>::operator--()
  noexcept
{
  --m_current;
  return (*this);
}

template<typename CharT, typename Traits>
inline bit::tools::arg_vector_iterator<CharT,Traits>
  bit::tools::arg_vector_iterator<CharT,Traits>::operator--(int)
  noexcept
{
  auto cur = (*this);
  --m_current;
  return cur;
}

//----------------------------------------------------------------------------

template<typename CharT, typename Traits>
inline bit::tools::arg_vector_iterator<CharT,Traits>&
  bit::tools::arg_vector_iterator<CharT,Traits>::operator+=( difference_type n )
  noexcept
{
  m_current += n;
  return (*this);
}

template<typename CharT, typename Traits>
inline bit::tools::arg_vector_iterator<CharT,Traits>&
  bit::tools::arg_vector_iterator<CharT,Traits>::operator-=( difference_type n )
  noexcept
{
  m_current -= n;
  return (*this);
}

//----------------------------------------------------------------------------

template<typename CharT, typename Traits>
inline typename bit::tools::arg_vector_iterator<CharT,Traits>::reference
  bit::tools::arg_vector_iterator<CharT,Traits>::operator[]( std::ptrdiff_t n )
  noexcept
{
  return *(m_current + n);
}

//============================================================================
// arg_vector
//============================================================================

template<typename CharT, typename Traits>
inline bit::tools::arg_vector_iterator<CharT,Traits>
  bit::tools::operator+( const arg_vector_iterator<CharT,Traits>& lhs,
                         std::ptrdiff_t rhs )
  noexcept
{
  return arg_vector_iterator<CharT,Traits>(lhs)+=rhs;
}

template<typename CharT, typename Traits>
inline bit::tools::arg_vector_iterator<CharT,Traits>
  bit::tools::operator+( std::ptrdiff_t lhs,
                         const arg_vector_iterator<CharT,Traits>& rhs )
  noexcept
{
  return arg_vector_iterator<CharT,Traits>(rhs)+=lhs;
}

//----------------------------------------------------------------------------

template<typename CharT, typename Traits>
inline bit::tools::arg_vector_iterator<CharT,Traits>
  bit::tools::operator-( const arg_vector_iterator<CharT,Traits>& lhs,
                         std::ptrdiff_t rhs )
  noexcept
{
  return arg_vector_iterator<CharT,Traits>(lhs)-=rhs;
}

//----------------------------------------------------------------------------
// Comparison
//----------------------------------------------------------------------------

template<typename CharT, typename Traits>
inline bool
  bit::tools::operator==( const arg_vector_iterator<CharT,Traits>& lhs,
                          const arg_vector_iterator<CharT,Traits>& rhs )
  noexcept
{
  return lhs.m_current == rhs.m_current;
}

//----------------------------------------------------------------------------

template<typename CharT, typename Traits>
inline bool
  bit::tools::operator!=( const arg_vector_iterator<CharT,Traits>& lhs,
                          const arg_vector_iterator<CharT,Traits>& rhs )
  noexcept
{
  return !(lhs == rhs);
}

//----------------------------------------------------------------------------

template<typename CharT, typename Traits>
inline bool
  bit::tools::operator<( const arg_vector_iterator<CharT,Traits>& lhs,
                         const arg_vector_iterator<CharT,Traits>& rhs )
  noexcept
{
  return (lhs.m_current < rhs.m_current);
}

//----------------------------------------------------------------------------

template<typename CharT, typename Traits>
inline bool
  bit::tools::operator>( const arg_vector_iterator<CharT,Traits>& lhs,
                         const arg_vector_iterator<CharT,Traits>& rhs )
  noexcept
{
  return (rhs < lhs);
}

//----------------------------------------------------------------------------

template<typename CharT, typename Traits>
inline bool
  bit::tools::operator<=( const arg_vector_iterator<CharT,Traits>& lhs,
                          const arg_vector_iterator<CharT,Traits>& rhs )
  noexcept
{
  return !(rhs < lhs);
}

//----------------------------------------------------------------------------

template<typename CharT, typename Traits>
inline bool
  bit::tools::operator>=( const arg_vector_iterator<CharT,Traits>& lhs,
                          const arg_vector_iterator<CharT,Traits>& rhs )
  noexcept
{
  return !(lhs < rhs);
}


//----------------------------------------------------------------------------
// Constructors
//----------------------------------------------------------------------------

template<typename CharT, typename Traits>
inline bit::tools::basic_arg_vector<CharT,Traits>::basic_arg_vector( argc_type argc, argv_type argv )
  noexcept
  : m_argv(argv),
    m_argc(argc)
{

}

//----------------------------------------------------------------------------
// Capacity
//----------------------------------------------------------------------------

template<typename CharT, typename Traits>
inline bool bit::tools::basic_arg_vector<CharT,Traits>::empty()
  const noexcept
{
  return m_argc == 0;
}

//----------------------------------------------------------------------------

template<typename CharT, typename Traits>
inline typename bit::tools::basic_arg_vector<CharT,Traits>::size_type
  bit::tools::basic_arg_vector<CharT,Traits>::size()
  const noexcept
{
  return static_cast<size_type>(m_argc);
}

//----------------------------------------------------------------------------
// Element Access
//----------------------------------------------------------------------------

template<typename CharT, typename Traits>
inline typename bit::tools::basic_arg_vector<CharT,Traits>::argv_type
  bit::tools::basic_arg_vector<CharT,Traits>::data()
  const noexcept
{
  return m_argv;
}

//----------------------------------------------------------------------------

template<typename CharT, typename Traits>
inline typename bit::tools::basic_arg_vector<CharT,Traits>::value_type
  bit::tools::basic_arg_vector<CharT,Traits>::at( index_type n )
  const
{
  if( n < 0 || n >= m_argc ) throw std::out_of_range("basic_arg_vector::at: index out of range");

  return m_argv[n];
}

//----------------------------------------------------------------------------

template<typename CharT, typename Traits>
inline typename bit::tools::basic_arg_vector<CharT,Traits>::value_type
  bit::tools::basic_arg_vector<CharT,Traits>::operator[]( index_type n )
  const noexcept
{
  return m_argv[n];
}

//----------------------------------------------------------------------------
// Iterators
//----------------------------------------------------------------------------

template<typename CharT, typename Traits>
inline typename bit::tools::basic_arg_vector<CharT,Traits>::iterator
  bit::tools::basic_arg_vector<CharT,Traits>::begin()
  const noexcept
{
  return iterator{m_argv};
}

//----------------------------------------------------------------------------

template<typename CharT, typename Traits>
inline typename bit::tools::basic_arg_vector<CharT,Traits>::iterator
  bit::tools::basic_arg_vector<CharT,Traits>::end()
  const noexcept
{
  return iterator{m_argv + m_argc};
}

//----------------------------------------------------------------------------

template<typename CharT, typename Traits>
inline typename bit::tools::basic_arg_vector<CharT,Traits>::reverse_iterator
  bit::tools::basic_arg_vector<CharT,Traits>::rbegin()
  const noexcept
{
  return reverse_iterator{iterator{m_argv + m_argc-1}};
}

//----------------------------------------------------------------------------

template<typename CharT, typename Traits>
inline typename bit::tools::basic_arg_vector<CharT,Traits>::reverse_iterator
  bit::tools::basic_arg_vector<CharT,Traits>::rend()
  const noexcept
{
  return reverse_iterator{iterator{m_argv}};
}

//----------------------------------------------------------------------------

template<typename CharT, typename Traits>
inline typename bit::tools::basic_arg_vector<CharT,Traits>::const_iterator
  bit::tools::basic_arg_vector<CharT,Traits>::cbegin()
  const noexcept
{
  return const_iterator{m_argv};
}

//----------------------------------------------------------------------------

template<typename CharT, typename Traits>
inline typename bit::tools::basic_arg_vector<CharT,Traits>::const_iterator
  bit::tools::basic_arg_vector<CharT,Traits>::cend()
  const noexcept
{
  return const_iterator{m_argv + m_argc};
}

//----------------------------------------------------------------------------

template<typename CharT, typename Traits>
inline typename bit::tools::basic_arg_vector<CharT,Traits>::const_reverse_iterator
  bit::tools::basic_arg_vector<CharT,Traits>::crbegin()
  const noexcept
{
  return const_reverse_iterator{const_iterator{m_argv + m_argc - 1}};
}

//----------------------------------------------------------------------------

template<typename CharT, typename Traits>
inline typename bit::tools::basic_arg_vector<CharT,Traits>::const_reverse_iterator
  bit::tools::basic_arg_vector<CharT,Traits>::crend()
  const noexcept
{
  return const_reverse_iterator{const_iterator{m_argv}};
}

#endif
