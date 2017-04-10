#ifndef BIT_TOOLS_DETAIL_TYPE_LOADER_INL
#define BIT_TOOLS_DETAIL_TYPE_LOADER_INL

//------------------------------------------------------------------------
// Node Traits
//------------------------------------------------------------------------

template<typename T, typename Node>
inline T bit::tools::casts::node_cast( const Node& node )
{
  return node_traits<Node>::template cast<T>( node );
}


//------------------------------------------------------------------------
// Constructor
//------------------------------------------------------------------------

template<typename T, typename Node, typename Key, typename Allocator>
inline bit::tools::type_loader<T,Node,Key,Allocator>
  ::type_loader( const Allocator& alloc )
  : m_entries( alloc )
{

}

template<typename T, typename Node, typename Key, typename Allocator>
inline bit::tools::type_loader<T,Node,Key,Allocator>
  ::type_loader( size_type reserve, const Allocator& alloc )
  : m_entries( alloc )
{
  m_entries.reserve( reserve );
}

//------------------------------------------------------------------------
// Member Additions
//------------------------------------------------------------------------

template<typename T, typename Node, typename Key, typename Allocator>
template<typename E, E (T::*member)>
inline bit::tools::type_loader<T,Node,Key,Allocator>&
  bit::tools::type_loader<T,Node,Key,Allocator>::add_member( key_type key )
{
  static const auto stub = []( T* ptr, const node_type& node )
  {
    (ptr->*member) = node_cast<E>( node );
  };
  m_entries.emplace_back(std::make_pair(std::move(key),stub));

  return (*this);
}

//------------------------------------------------------------------------

template<typename T, typename Node, typename Key, typename Allocator>
template<typename E, void (T::*member_function)(E)>
inline bit::tools::type_loader<T,Node,Key,Allocator>&
  bit::tools::type_loader<T,Node,Key,Allocator>::add_member( key_type key )
{
  static const auto stub = []( T* ptr, const node_type& node )
  {
    (ptr->*member_function)( node_cast<E>( node ) );
  };
  m_entries.emplace_back(std::make_pair(std::move(key),stub));

  return (*this);
}

//------------------------------------------------------------------------

template<typename T, typename Node, typename Key, typename Allocator>
template<typename E, E (T::*member_function)(const E&)>
inline bit::tools::type_loader<T,Node,Key,Allocator>&
  bit::tools::type_loader<T,Node,Key,Allocator>::add_member( key_type key )
{
  static const auto stub = []( T* ptr, const node_type& node )
  {
    (ptr->*member_function)( node_cast<E>( node ) );
  };
  m_entries.emplace_back(std::make_pair(std::move(key),stub));

  return (*this);
}

//------------------------------------------------------------------------

template<typename T, typename Node, typename Key, typename Allocator>
template<typename E, void (T::*member_function)(E) const>
inline bit::tools::type_loader<T,Node,Key,Allocator>&
  bit::tools::type_loader<T,Node,Key,Allocator>::add_member( key_type key )
{
  static const auto stub = []( T* ptr, const node_type& node )
  {
    (ptr->*member_function)( node_cast<E>( node ) );
  };
  m_entries.emplace_back(std::make_pair(std::move(key),stub));

  return (*this);
}

//------------------------------------------------------------------------

template<typename T, typename Node, typename Key, typename Allocator>
template<typename E, void (T::*member_function)(const E&) const>
inline bit::tools::type_loader<T,Node,Key,Allocator>&
  bit::tools::type_loader<T,Node,Key,Allocator>::add_member( key_type key )
{
  static const auto stub = []( T* ptr, const node_type& node )
  {
    (ptr->*member_function)( node_cast<E>( node ) );
  };
  m_entries.emplace_back(std::make_pair(std::move(key),stub));

  return (*this);
}

//------------------------------------------------------------------------
// Capacity
//------------------------------------------------------------------------

template<typename T, typename Node, typename Key, typename Allocator>
inline typename bit::tools::type_loader<T,Node,Key,Allocator>::size_type
  bit::tools::type_loader<T,Node,Key,Allocator>::size()
  const noexcept
{
  return m_entries.size();
}

template<typename T, typename Node, typename Key, typename Allocator>
inline bool bit::tools::type_loader<T,Node,Key,Allocator>::empty()
  const noexcept
{
  return m_entries.empty();
}

//------------------------------------------------------------------------
// Translation
//------------------------------------------------------------------------

template<typename T, typename Node, typename Key, typename Allocator>
typename bit::tools::type_loader<T,Node,Key,Allocator>::size_type
  bit::tools::type_loader<T,Node,Key,Allocator>
  ::load( value_type* instance, const node_type& node )
  const
{
  auto not_translated = std::size_t(0);
  for( auto const& entry : m_entries )
  {
    if( node_traits<Node>::has( node, entry.first ) ) {
      entry.second( instance, node_traits<Node>::at( node, entry.first ) );
    } else {
      ++not_translated;
    }
  }
  return not_translated;
}

//------------------------------------------------------------------------

template<typename T, typename Node, typename Key, typename Allocator>
template<typename InputIterator1, typename InputIterator2>
inline std::ptrdiff_t bit::tools::type_loader<T,Node,Key,Allocator>
  ::load_series( InputIterator1 first1, InputIterator1 last1,
                 InputIterator2 first2, InputIterator2 last2 )
  const
{
  return translate_series( first1, last1, first2, last2, [](std::size_t){} );
}

//------------------------------------------------------------------------

template<typename T, typename Node, typename Key, typename Allocator>
template<typename InputIterator1, typename InputIterator2, typename Accumulator>
inline std::ptrdiff_t bit::tools::type_loader<T,Node,Key,Allocator>
  ::translate_series( InputIterator1 first1, InputIterator1 last1,
                      InputIterator2 first2, InputIterator2 last2,
                      Accumulator&& accumulator )
  const
{
  while( first1 != last1 && first2 != last2 )
  {
      std::forward<Accumulator>(accumulator)( load( std::addressof(*first1), *first2 ) );

      ++first1;
      ++first2;
  }

  auto const diff1 = std::distance(first1,last1); // remaining untranslated structures
  auto const diff2 = std::distance(first2,last2); // remaining untranslated nodes;

  return diff1 - diff2;
}

//------------------------------------------------------------------------

template<typename T, typename Node, typename Key, typename Allocator>
template<typename OutputIterator, typename InputIterator>
inline std::ptrdiff_t bit::tools::type_loader<T,Node,Key,Allocator>
  ::translate_series( OutputIterator out,
                      InputIterator first,
                      InputIterator last )
  const
{
    return translate_series(out,first,last,[](std::size_t){});
};


template<typename T, typename Node, typename Key, typename Allocator>
template<typename OutputIterator, typename InputIterator, typename Accumulator>
inline std::ptrdiff_t bit::tools::type_loader<T,Node,Key,Allocator>
  ::translate_series( OutputIterator out,
                      InputIterator first, InputIterator last,
                      Accumulator&& accumulator )
  const
{
    while( first != last )
    {
        entry_type entry; // intentionally uninitialized

        std::forward<Accumulator>(accumulator)( load( std::addressof(entry), *first ) );
        (*out) = std::move(entry);

        ++first;
        ++out;
    }
    return std::ptrdiff_t{0};
};

#endif /* BIT_TOOLS_DETAIL_TYPE_LOADER_INL */
