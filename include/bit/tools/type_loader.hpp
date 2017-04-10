/**
 * \file type_loader.hpp
 *
 * \brief Translates types between serialized data and C++ types
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */

#ifndef BIT_TOOLS_TYPE_LOADER_HPP
#define BIT_TOOLS_TYPE_LOADER_HPP

#include <bit/stl/stddef.hpp>

#include <string>  // std::string
#include <vector>  // std::vector
#include <cstddef> // std::size_t

namespace bit {
  namespace tools {

    //////////////////////////////////////////////////////////////////////////
    /// \brief This type is for traits about a given node tpye
    ///
    /// This type requires 3 specializations: cast, has, and at. This will
    /// permit full conversion between different node types, checking node
    /// inclusion, and casting
    ///
    /// \tparam Node the node type
    //////////////////////////////////////////////////////////////////////////
    template<typename Node>
    struct node_traits
    {
      /// \brief Casts a \p node to a given type
      ///
      /// \tparam T the type to cast to
      /// \return the casted type
      template<typename T>
      static T cast( const Node& node );

      /// \brief Checks if a given node exists for the specified \p key
      ///
      /// \param node the node
      /// \param key the key to search for
      /// \return \c true if the node exists
      template<typename Key>
      static bool has( const Node& node, const Key& key );

      /// \brief Accesses the \p node at the specified \p key
      ///
      /// \param node the node to access
      /// \param key the key
      /// \return the node at the specified key
      template<typename Key>
      static Node at( const Node& node, const Key& key );
    };

    inline namespace casts {

      /// \brief Casts a \p node to type \p T
      ///
      /// \param node the node to cast
      /// \return the type being casted to
      template<typename T, typename Node>
      T node_cast( const Node& node );

    } // inline namespace casts

    //////////////////////////////////////////////////////////////////////////
    /// \brief This type is used for loading types between different nodes
    ///        retrieved from serialization/deserialization libraries.
    ///
    /// Loading is done by translating node data to individual members of the
    /// type being loaded.
    //////////////////////////////////////////////////////////////////////////
    template< typename T,
              typename Node,
              typename Key       = std::string,
              typename Allocator = std::allocator<stl::byte> >
    class type_loader
    {
      //----------------------------------------------------------------------
      // Public Member Types
      //----------------------------------------------------------------------
    public:

      using value_type = T;           ///< The type to translate
      using node_type  = Node;        ///< The type of node to translate from
      using key_type   = Key;         ///< The key for the node entries
      using size_type  = std::size_t; ///< The type used for sizes

      //----------------------------------------------------------------------
      // Constructor
      //----------------------------------------------------------------------
    public:

      /// \brief Constructs a type_loader from a given allocator
      ///
      /// \param alloc the allocator to use for the internal data structure
      explicit type_loader( const Allocator& alloc = Allocator() );

      /// \brief Constructs a type_loader, reserving storage
      ///        storage at the same time
      ///
      /// \param reserve the amount of entries to reserve
      /// \param alloc the allocator to use for the internal data structure
      explicit type_loader( size_type reserve,
                            const Allocator& alloc = Allocator() );

      //----------------------------------------------------------------------
      // Member Additions
      //----------------------------------------------------------------------
    public:

      /// \brief Maps a pointer-to-member to a given \p key
      ///
      /// \tparam E the entry type
      /// \tparam member the member pointer
      /// \param key the key to map
      /// \return reference to (*this)
      template<typename E, E (T::*member)>
      type_loader& add_member( key_type key );

      /// \brief Maps a pointer-to-member function to a given \p key
      ///
      /// \tparam E the entry type
      /// \tparam member the member function pointer
      /// \param key the key to map
      /// \return reference to (*this)
      template<typename E, void (T::*member_function)(E)>
      type_loader& add_member( key_type key );

      /// \brief Maps a pointer-to-member function to a given \p key
      ///
      /// \tparam E the entry type
      /// \tparam member the member function pointer
      /// \param key the key to map
      /// \return reference to (*this)
      template<typename E, E (T::*member_function)(const E&)>
      type_loader& add_member( key_type key );

      /// \brief Maps a pointer-to-member function to a given \p key
      ///
      /// \tparam E the entry type
      /// \tparam member the member function pointer
      /// \param key the key to map
      /// \return reference to (*this)
      template<typename E, void (T::*member_function)(E) const>
      type_loader& add_member( key_type key );

      /// \brief Maps a pointer-to-member function to a given \p key
      ///
      /// \tparam E the entry type
      /// \tparam member the member function pointer
      /// \param key the key to map
      /// \return reference to (*this)
      template<typename E, void (T::*member_function)(const E&) const>
      type_loader& add_member( key_type key );

      //----------------------------------------------------------------------
      // Capacity
      //----------------------------------------------------------------------
    public:

      /// \brief Returns the number of entries in this type_loader
      ///
      /// \return The number of elements in the container
      size_type size() const noexcept;

      /// \brief Checks if the type_loader has no elements
      ///
      /// \return \c true if the type_loader is empty
      bool empty() const noexcept;

      //----------------------------------------------------------------------
      // Translation
      //----------------------------------------------------------------------
    public:

      /// \brief Loads a single entry from a data node
      ///
      /// \param instance pointer to the instance to translate
      /// \param node     the node to retrieve data from
      size_type load( value_type* instance, const node_type& node ) const;

      /// \brief Loads a sequence of nodes into sequential structures using
      ///        InputIterators
      ///
      /// \param first1 The first entry to translate
      /// \param last1  The last entry to translate
      /// \param first2 The first data node to translate from
      /// \param last2  The last data node to translate from
      /// \return       0 if all entries are translated, or the number of
      ///               untranslated entries.
      ///               The result is positive if there are any unpopulated
      ///               structures (e.g. last1 was reached first)
      ///               The result is negative if there are any untranslated
      ///               nodes (e.g. last2 was reached first)
      template<typename InputIterator1, typename InputIterator2>
      std::ptrdiff_t load_series( InputIterator1 first1, InputIterator1 last1,
                                  InputIterator2 first2, InputIterator2 last2 ) const;

      /// \brief Loads a sequence of nodes into sequential structures
      ///        using InputIterators
      ///
      /// \param first1      The first entry to translate
      /// \param last1       The last entry to translate
      /// \param first2      The first data node to translate from
      /// \param last2       The last data node to translate from
      /// \param accumulator A function-like object that accepts std::size_t;
      ///                    the number of entries not translated per entry
      /// \return       0 if all entries are translated, or the number of
      ///               untranslated entries.
      ///               The result is positive if there are any unpopulated
      ///               structures (e.g. last1 was reached first)
      ///               The result is negative if there are any untranslated
      ///               nodes (e.g. last2 was reached first)
      template<typename InputIterator1, typename InputIterator2, typename Accumulator>
      std::ptrdiff_t translate_series( InputIterator1 first1, InputIterator1 last1,
                                       InputIterator2 first2, InputIterator2 last2,
                                       Accumulator&& accumulator ) const;

      /// \brief Loads a sequence of nodes into a data structure using
      ///        OutputIterators
      ///
      /// \note For consistency with other overloads, this function returns
      ///       the number of untranslated entries, which is always 0 since
      ///       it stores to an unbounded output iterator
      ///
      /// \param out   The output iterator to record entries
      /// \param first The first data node to translate from
      /// \param last  The last data node to translate from
      /// \return The number of untranslated entries (always 0)
      template<typename OutputIterator, typename InputIterator>
      std::ptrdiff_t translate_series( OutputIterator out,
                                       InputIterator first, InputIterator last ) const;

      /// \brief Loads a sequence of nodes into a data structure using
      ///        OutputIterators with an additional Accumulator
      ///
      /// \note For consistency with other overloads, this function returns
      ///       the number of untranslated entries, which is always 0 since
      ///       it stores to an unbounded output iterator
      ///
      /// \param out   The output iterator to record entries
      /// \param first The first data node to translate from
      /// \param last  The last data node to translate from
      /// \return The number of untranslated entries (always 0)
      template<typename OutputIterator, typename InputIterator, typename Accumulator>
      std::ptrdiff_t translate_series( OutputIterator out,
                                       InputIterator first, InputIterator last,
                                       Accumulator&& accumulator ) const;

      //----------------------------------------------------------------------
      // Private Member Types
      //----------------------------------------------------------------------
    private:

      using stub_type      = void(*)(value_type*,const node_type&);
      using entry_type     = std::pair<key_type,stub_type>;
      using allocator_type = typename std::allocator_traits<Allocator>::template rebind_alloc<entry_type>;
      using vector_type    = std::vector<entry_type,allocator_type>;

      //----------------------------------------------------------------------
      // Private Members
      //----------------------------------------------------------------------
    private:

      vector_type m_entries; ///< The entries to translate
    };

  } // namespace tools
} // namespace bit

#include "detail/type_loader.inl"

#endif /* BIT_TOOLS_TYPE_LOADER_HPP */
