#include <sys/types.h>
#include <bits/char_traits.h>
#include <bits/stl_iterator.h>
#include <string>
#include "structdef.hpp"

constexpr size_t MAX_FIXED_SIZE = 2048;

template <typename _CharT, typename _Traits, typename _Alloc>
class _basic_fixed_string {

    typedef typename __gnu_cxx::__alloc_traits<_Alloc>::template rebind<_CharT>::other 
    _Character_allocator_type;

    typedef __gnu_cxx::__alloc_traits<_Character_allocator_type> 
    _Allocator_traits;

public:
    typedef _Traits                                                     traits_type;
    typedef typename _Traits::char_type                                 value_type;
    typedef _Character_allocator_type                                   allocator_type;
    typedef typename _Allocator_traits::size_type                       size_type;
    typedef typename _Allocator_traits::difference_type                 difference_type;
    typedef typename _Allocator_traits::reference                       reference;
    typedef typename _Allocator_traits::const_reference                 const_reference;
    typedef typename _Allocator_traits::pointer                         pointer;
    typedef typename _Allocator_traits::const_pointer                   const_pointer;
    typedef __gnu_cxx::__normal_iterator<pointer, _basic_fixed_string>  iterator;
    typedef __gnu_cxx::__normal_iterator<const_pointer, _basic_fixed_string> const_iterator;
    typedef std::reverse_iterator<iterator>                             reverse_iterator;
    typedef std::reverse_iterator<const_iterator>                       const_reverse_iterator;

    static const size_type npos = static_cast<size_type>(-1);
    
protected:
    typedef const_iterator __const_iterator;

private:

    struct _allocator_hider : allocator_type {

        _allocator_hider(pointer _data, const _Alloc& _alloc) : allocator_type(_alloc), _m_p(_data) {}
        _allocator_hider(pointer _data, _Alloc&& _alloc = _Alloc()) : allocator_type(std::move(_alloc)), _m_p(_data) {}

        pointer _m_p
    };

    _allocator_hider    _m_agg_data;
    size_type           _m_str_len;

    enum { _s_local_cap = 15 / sizeof(_CharT) };

    union {

        _CharT      _m_buffer[_s_local_cap + 1];
        size_type   _m_alloc_cap;

    };

    inline constexpr void _m_data(pointer _p) { _m_agg_data._m_p = _p; }
    inline constexpr void _m_length(size_type _length) { _m_str_len = _length; }


};

template<size_t size>
class fixed_string {

public:



public:

    fixed_string() = default;
    fixed_string(size_t size, const char * str);
    fixed_string(std::string str);
    fixed_string(const fixed_string& other);
    fixed_string(fixed_string&& other);


private:

    char m_buffer[size];
    size_t m_size;

};