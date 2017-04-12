#ifndef BIT_TOOLS_ARGS_DETAIL_ARG_PARSER_INL
#define BIT_TOOLS_ARGS_DETAIL_ARG_PARSER_INL


//============================================================================
// basic_arg_set
//============================================================================

template<typename CharT, typename Traits>
inline bit::tools::basic_arg_set<CharT,Traits>
  ::basic_arg_set()
  noexcept
  : m_head(nullptr)
{

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
  m_node.state = node_type::node_state::unknown;
  m_node.type  = node_type::node_type::single;
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
  return m_node.state == node_type::node_state::set;
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

  m_node.flag  = flag;
  m_node.state = node_type::node_state::unknown;
  m_node.type  = node_type::node_type::multi;
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
  return m_node.storage.single;
}

//----------------------------------------------------------------------------

template<typename CharT, typename Traits>
inline bool bit::tools::basic_multi_arg<CharT,Traits>::is_set()
  const noexcept
{
  return m_node.state == node_type::node_state::set;
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
  : basic_option_arg( parent, flag, {} )
{

}

//----------------------------------------------------------------------------

template<typename CharT, typename Traits>
inline bit::tools::basic_option_arg<CharT,Traits>
  ::basic_option_arg( set_type& parent, key_type flag, value_type default_value )
  noexcept
{
  auto& head = reinterpret_cast<node_type*&>(parent);

  m_node.flag  = flag;
  m_node.state = node_type::node_state::unknown;
  m_node.type  = node_type::node_type::option;
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
  return m_node.storage.single;
}

//----------------------------------------------------------------------------

template<typename CharT, typename Traits>
inline bool bit::tools::basic_option_arg<CharT,Traits>::is_set()
  const noexcept
{
  return m_node.state == node_type::node_state::set;
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
  m_node.flag  = flag;
  m_node.state = node_type::node_state::unknown;
  m_node.type  = node_type::node_type::alias;
  m_node.storage.alias = node;

  // Append the node after the current one
  m_node.next = node->next;
  node->next  = &m_node;
}

//============================================================================
// basic_arg_parser
//============================================================================


#endif /* BIT_TOOLS_ARGS_DETAIL_ARG_PARSER_INL */
