#ifndef BIT_TOOLS_ARGS_DETAIL_ARG_PARSER_INL
#define BIT_TOOLS_ARGS_DETAIL_ARG_PARSER_INL


//============================================================================
// basic_arg_set
//============================================================================

//----------------------------------------------------------------------------
// Constructor
//----------------------------------------------------------------------------

template<typename CharT, typename Traits>
inline bit::tools::basic_arg_set<CharT,Traits>
  ::basic_arg_set()
  noexcept
  : m_head(nullptr)
{

}

//----------------------------------------------------------------------------
// Observers
//----------------------------------------------------------------------------

template<typename CharT, typename Traits>
inline bool bit::tools::basic_arg_set<CharT,Traits>::empty()
  const noexcept
{
  return m_head;
}

template<typename CharT, typename Traits>
inline typename bit::tools::basic_arg_set<CharT,Traits>::size_type
  bit::tools::basic_arg_set<CharT,Traits>::size()
  const noexcept
{
  auto size = 0;

  while(m_head){
    m_head=m_head->next;
    ++size;
  }

  return size;
}

template<typename CharT, typename Traits>
inline typename bit::tools::basic_arg_set<CharT,Traits>::unmatched_range
  bit::tools::basic_arg_set<CharT,Traits>::unmatched()
  const noexcept
{
  return stl::make_range( m_unmatched.begin(), m_unmatched.end() );
}

//============================================================================
// basic_single_args
//============================================================================

//----------------------------------------------------------------------------
// Constructor
//----------------------------------------------------------------------------

template<typename CharT, typename Traits>
inline bit::tools::basic_single_arg<CharT,Traits>
  ::basic_single_arg( set_type& parent, key_type flag )
  noexcept
  : basic_single_arg( parent, flag, "" )
{

}

//----------------------------------------------------------------------------

template<typename CharT, typename Traits>
inline bit::tools::basic_single_arg<CharT,Traits>
  ::basic_single_arg( set_type& parent, key_type flag, value_type default_value )
  noexcept
{
  auto& head = reinterpret_cast<node_type*&>(parent);

  m_node.flag = flag;
  m_node.set  = false;
  m_node.type = node_type::node_type::single;
  m_node.storage.single = default_value;
  if(head){
    m_node.next = head->next;
    head->next = &m_node;
  } else {
    m_node.next = nullptr;
    head = &m_node;
  }
}

//----------------------------------------------------------------------------
// Observers
//----------------------------------------------------------------------------

template<typename CharT, typename Traits>
inline typename bit::tools::basic_single_arg<CharT,Traits>::value_type
  bit::tools::basic_single_arg<CharT,Traits>::value()
  const noexcept
{
  return m_node.storage.single;
}

//----------------------------------------------------------------------------

template<typename CharT, typename Traits>
inline bool bit::tools::basic_single_arg<CharT,Traits>::is_set()
  const noexcept
{
  return m_node.set;
}

template<typename CharT, typename Traits>
inline bit::tools::basic_single_arg<CharT,Traits>::operator bool()
  const noexcept
{
  return is_set();
}

//============================================================================
// basic_multi_arg
//============================================================================

//----------------------------------------------------------------------------
// Constructor
//----------------------------------------------------------------------------

template<typename CharT, typename Traits>
inline bit::tools::basic_multi_arg<CharT,Traits>
  ::basic_multi_arg( set_type& parent, key_type flag )
  noexcept
  : basic_multi_arg( parent, flag, value_type{} )
{

}

//----------------------------------------------------------------------------

template<typename CharT, typename Traits>
inline bit::tools::basic_multi_arg<CharT,Traits>
  ::basic_multi_arg( set_type& parent, key_type flag, value_type default_value )
  noexcept
{
  auto& head = reinterpret_cast<node_type*&>(parent);

  m_node.flag = flag;
  m_node.set  = false;
  m_node.type = node_type::node_type::multi;
  m_node.storage.multi = default_value;
  if(head){
    m_node.next = head->next;
    head->next = &m_node;
  } else {
    m_node.next = nullptr;
    head = &m_node;
  }
}

//----------------------------------------------------------------------------
// Observers
//----------------------------------------------------------------------------

template<typename CharT, typename Traits>
inline typename bit::tools::basic_multi_arg<CharT,Traits>::value_type
  bit::tools::basic_multi_arg<CharT,Traits>::value()
  const noexcept
{
  return m_node.storage.multi;
}

//----------------------------------------------------------------------------

template<typename CharT, typename Traits>
inline bool bit::tools::basic_multi_arg<CharT,Traits>::is_set()
  const noexcept
{
  return m_node.set;
}

template<typename CharT, typename Traits>
inline bit::tools::basic_multi_arg<CharT,Traits>::operator bool()
  const noexcept
{
  return is_set();
}

//============================================================================
// basic_option_arg
//============================================================================

//----------------------------------------------------------------------------
// Constructor
//----------------------------------------------------------------------------

template<typename CharT, typename Traits>
inline bit::tools::basic_option_arg<CharT,Traits>
  ::basic_option_arg( set_type& parent, key_type flag )
  noexcept
  : basic_option_arg( parent, flag, false )
{

}

//----------------------------------------------------------------------------

template<typename CharT, typename Traits>
inline bit::tools::basic_option_arg<CharT,Traits>
  ::basic_option_arg( set_type& parent, key_type flag, value_type default_value )
  noexcept
{
  auto& head = reinterpret_cast<node_type*&>(parent);

  m_node.flag = flag;
  m_node.set  = false;
  m_node.type = node_type::node_type::option;
  m_node.storage.option = default_value;
  if(head){
    m_node.next = head->next;
    head->next = &m_node;
  } else {
    m_node.next = nullptr;
    head = &m_node;
  }
}

//----------------------------------------------------------------------------
// Observers
//----------------------------------------------------------------------------

template<typename CharT, typename Traits>
inline typename bit::tools::basic_option_arg<CharT,Traits>::value_type
  bit::tools::basic_option_arg<CharT,Traits>::value()
  const noexcept
{
  return m_node.storage.option;
}

//----------------------------------------------------------------------------

template<typename CharT, typename Traits>
inline bool bit::tools::basic_option_arg<CharT,Traits>::is_set()
  const noexcept
{
  return m_node.set;
}

template<typename CharT, typename Traits>
inline bit::tools::basic_option_arg<CharT,Traits>::operator bool()
  const noexcept
{
  return is_set();
}

//============================================================================
// basic_alias_args
//============================================================================

template<typename CharT, typename Traits>
inline bit::tools::basic_alias_arg<CharT,Traits>
  ::basic_alias_arg( basic_single_arg<CharT,Traits>& value, key_type flag )
  noexcept
  : basic_alias_arg( flag, reinterpret_cast<node_type*>(&value) )
{

}

template<typename CharT, typename Traits>
inline bit::tools::basic_alias_arg<CharT,Traits>
  ::basic_alias_arg( basic_multi_arg<CharT,Traits>& value, key_type flag )
  noexcept
  : basic_alias_arg( flag, reinterpret_cast<node_type*>(&value) )
{

}

template<typename CharT, typename Traits>
inline bit::tools::basic_alias_arg<CharT,Traits>
  ::basic_alias_arg( basic_option_arg<CharT,Traits>& value, key_type flag )
  noexcept
  : basic_alias_arg( flag, reinterpret_cast<node_type*>(&value) )
{

}

template<typename CharT, typename Traits>
inline bit::tools::basic_alias_arg<CharT,Traits>
  ::basic_alias_arg( basic_alias_arg& value, key_type flag )
  noexcept
  : basic_alias_arg( flag, reinterpret_cast<node_type*>(&value) )
{

}

template<typename CharT, typename Traits>
inline bit::tools::basic_alias_arg<CharT,Traits>
  ::basic_alias_arg( key_type flag, node_type* node )
  noexcept
{
  m_node.flag = flag;
  m_node.set  = false;
  m_node.type = node_type::node_type::alias;
  m_node.storage.alias = node;

  // Append the node after the current one
  m_node.next = node->next;
  node->next  = &m_node;
}

//============================================================================
// Argument Parser
//============================================================================

template<typename CharT, typename Traits>
bool bit::tools::parse_arguments( basic_arg_set<CharT,Traits>* arg_set,
                                  basic_arg_vector<CharT,Traits> args )
{
  // Aliases
  using namespace bit::stl::casts;
  using arg_node = detail::basic_arg_node<CharT,Traits>;

  //--------------------------------------------------------------------------

  // Find the argument from the intrinsically-linked list
  const auto find_arg = [&]( auto arg ) -> arg_node*
  {
    auto ptr = arg_set->m_head;

    while(ptr) {
      if( ptr->flag == arg ) {
        // Follow all aliases
        while( ptr->type == arg_node::node_type::alias ) {
          ptr = ptr->storage.alias;
        }
        return ptr;
      }
      ptr = ptr->next;
    }
    return nullptr;
  };

  //--------------------------------------------------------------------------

  if(!arg_set) return false;

  auto i    = std::ptrdiff_t{0};
  auto size = narrow_cast<std::ptrdiff_t>(args.size());

  while( i < args.size() ) {
    auto node = find_arg( args[i] );

    if( !node ) {
      // It's not matched anywhere
      arg_set->m_unmatched.push_back( args[i] );
      ++i;
      continue;
    }

    switch( node->type )
    {
    //------------------------------------------------------------------------
    // Single
    //------------------------------------------------------------------------

    case arg_node::node_type::single:
    {
      if( i+1 < args.size() ) {
        // If the next argument is not a known flag
        if( !find_arg( args[i+1] ) ) {
          node->storage.single = args[i+1];
          ++i;
        }
        ++i;
        node->set = true;
      }
      break;
    }

    //------------------------------------------------------------------------
    // Multi
    //------------------------------------------------------------------------

    case arg_node::node_type::multi:
    {
      auto j = i+1;
      // Find each argument that is not a known flag
      while( j < args.size() && !find_arg( args[j] ) ) {
        ++j;
      }
      node->storage.multi = args.subvec(i+1,j-i-1);
      node->set = true;
      i = j;
      break;
    }

    //------------------------------------------------------------------------
    // Option
    //------------------------------------------------------------------------

    case arg_node::node_type::option:
    {
      node->storage.option = true;
      node->set = true;
      ++i;
      break;
    }

    //------------------------------------------------------------------------

    default:
      break;
    } // switch
  } // while

  return true;
}


#endif /* BIT_TOOLS_ARGS_DETAIL_ARG_PARSER_INL */
