#ifndef __U2STLRedefined_H__
#define __U2STLRedefined_H__

#include "U2Prerequisites.h"
// #include "U2MemorySTLAllocator.h"
// #include "U2MemoryAllocatorConfig.h"



namespace U2EG_NAMESPACE_NAME
{
#if U2_STRING_USE_CUSTOM_MEMORY_ALLOCATOR == U2_ON
    
#if U2_WCHAR_T_STRINGS
    typedef std::basic_string< wchar_t, std::char_traits<wchar_t>, STLAllocator<wchar_t, GeneralAllocPolicy> >    _StringBase;
#else
    typedef std::basic_string< char, std::char_traits<char>, STLAllocator<char, GeneralAllocPolicy> >             _StringBase;
#endif
    
#if U2_WCHAR_T_STRINGS
    typedef std::basic_stringstream< wchar_t, std::char_traits<wchar_t>, STLAllocator<wchar_t, GeneralAllocPolicy> >  _StringStreamBase;
#else
    typedef std::basic_stringstream< char, std::char_traits<char>, STLAllocator<char, GeneralAllocPolicy> >           _StringStreamBase;
#endif
    
#define StdStringT(T)            std::basic_string< T, std::char_traits<T>, std::allocator<T> >
#define CustomMemoryStringT(T)   std::basic_string< T, std::char_traits<T>, STLAllocator<T, GeneralAllocPolicy> >
    
    template<typename T>
    bool operator < (const CustomMemoryStringT(T) & l, const StdStringT(T)& o)
    {
        return l.compare(0, l.length(), o.c_str(), o.length()) < 0;
    }
    
    template<typename T>
    bool operator < (const StdStringT(T) & l, const CustomMemoryStringT(T) & o)
    {
        return l.compare(0, l.length(), o.c_str(), o.length()) < 0;
    }
    
    template<typename T>
    bool operator <= (const CustomMemoryStringT(T) & l, const StdStringT(T) & o)
    {
        return l.compare(0, l.length(), o.c_str(), o.length()) <= 0;
    }
    
    template<typename T>
    bool operator <= (const StdStringT(T) & l, const CustomMemoryStringT(T) & o)
    {
        return l.compare(0, l.length(), o.c_str(), o.length()) <= 0;
    }
    
    template<typename T>
    bool operator > (const CustomMemoryStringT(T) & l, const StdStringT(T) & o)
    {
        return l.compare(0, l.length(), o.c_str(), o.length()) > 0;
    }
    
    template<typename T>
    bool operator > (const StdStringT(T) & l, const CustomMemoryStringT(T) & o)
    {
        return l.compare(0, l.length(), o.c_str(), o.length()) > 0;
    }
    
    template<typename T>
    bool operator >= (const CustomMemoryStringT(T) & l, const StdStringT(T) & o)
    {
        return l.compare(0, l.length(), o.c_str(), o.length()) >= 0;
    }
    
    template<typename T>
    bool operator >= (const StdStringT(T) & l, const CustomMemoryStringT(T) & o)
    {
        return l.compare(0, l.length(), o.c_str(), o.length()) >= 0;
    }
    
    template<typename T>
    bool operator == (const CustomMemoryStringT(T) & l, const StdStringT(T) & o)
    {
        return l.compare(0, l.length(), o.c_str(), o.length())==0;
    }
    
    template<typename T>
    bool operator == (const StdStringT(T) & l, const CustomMemoryStringT(T) & o)
    {
        return l.compare(0, l.length(), o.c_str(), o.length()) == 0;
    }
    
    template<typename T>
    bool operator != (const CustomMemoryStringT(T) & l, const StdStringT(T) & o)
    {
        return l.compare(0, l.length(), o.c_str(), o.length()) != 0;
    }
    
    template<typename T>
    bool operator != (const StdStringT(T) & l, const CustomMemoryStringT(T) & o)
    {
        return l.compare(0, l.length(), o.c_str(), o.length()) != 0;
    }
    
    template<typename T>
    CustomMemoryStringT(T) operator += (const CustomMemoryStringT(T) & l, const StdStringT(T) & o)
    {
        return CustomMemoryStringT(T)(l) += o.c_str();
    }
    
    template<typename T>
    CustomMemoryStringT(T) operator += (const StdStringT(T) & l, const CustomMemoryStringT(T) & o)
    {
        return CustomMemoryStringT(T)(l.c_str()) += o.c_str();
    }
    
    template<typename T>
    CustomMemoryStringT(T) operator + (const CustomMemoryStringT(T) & l, const StdStringT(T) & o)
    {
        return CustomMemoryStringT(T)(l) += o.c_str();
    }
    
    template<typename T>
    CustomMemoryStringT(T) operator + (const StdStringT(T) & l, const CustomMemoryStringT(T) & o)
    {
        return CustomMemoryStringT(T)(l.c_str()) += o.c_str();
    }
    
    template<typename T>
    CustomMemoryStringT(T) operator + (const T * l, const CustomMemoryStringT(T) & o)
    {
        return CustomMemoryStringT(T)(l) += o;
    }
    
#   undef StdStringT
#   undef CustomMemoryStringT
    
#else
    
#   if U2_WCHAR_T_STRINGS
    typedef std::wstring            _StringBase;
#   else
    typedef std::string             _StringBase;
#   endif
    
#   if U2_WCHAR_T_STRINGS
    typedef std::basic_stringstream<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >   _StringStreamBase;
#   else
    typedef std::basic_stringstream<char, std::char_traits<char>, std::allocator<char> >            _StringStreamBase;
#   endif
    
#endif
    
    typedef _StringBase             String;
    typedef _StringStreamBase       StringStream;
};



#if U2_STRING_USE_CUSTOM_MEMORY_ALLOCATOR 
namespace std
{
#if (U2_COMPILER == U2_COMPILER_GNUC && U2_COMP_VER >= 430) || U2_COMPILER == U2_COMPILER_CLANG && !defined(STLPORT) && __cplusplus < 201103L
    namespace tr1
    {
#endif
        template <> struct hash < u2::String >
        {
        public:
            size_t operator()(const u2::String &str) const
            {
                size_t _Val = 2166136261U;
                size_t _First = 0;
                size_t _Last = str.size();
                size_t _Stride = 1 + _Last / 10;

                for (; _First < _Last; _First += _Stride)
                    _Val = 16777619U * _Val ^ (size_t)str[_First];
                return (_Val);
            }
        };
#if (U2_COMPILER == U2_COMPILER_GNUC && U2_COMP_VER >= 430) || U2_COMPILER == U2_COMPILER_CLANG && !defined(STLPORT) && __cplusplus < 201103L
    }
#endif
}
#endif



// for stl container
namespace U2EG_NAMESPACE_NAME
{
    template <typename T, typename A = STLAllocator<T, GeneralAllocPolicy> >
    struct deque
    {
#if U2_CONTAINERS_USE_CUSTOM_MEMORY_ALLOCATOR == U2_ON
        typedef typename std::deque<T, A>                       type;
        typedef typename std::deque<T, A>::iterator             iterator;
        typedef typename std::deque<T, A>::const_iterator       const_iterator;
#else
        typedef typename std::deque<T>                          type;
        typedef typename std::deque<T>::iterator                iterator;
        typedef typename std::deque<T>::const_iterator          const_iterator;
#endif
    };
    
    template <typename T, typename A = STLAllocator<T, GeneralAllocPolicy> >
    struct vector
    {
#if U2_CONTAINERS_USE_CUSTOM_MEMORY_ALLOCATOR == U2_ON
        typedef typename std::vector<T, A>                      type;
        typedef typename std::vector<T, A>::iterator            iterator;
        typedef typename std::vector<T, A>::const_iterator      const_iterator;
#else
        typedef typename std::vector<T>                         type;
        typedef typename std::vector<T>::iterator               iterator;
        typedef typename std::vector<T>::const_iterator         const_iterator;
#endif
    };
    
    template <typename T, typename A = STLAllocator<T, GeneralAllocPolicy> >
    struct list
    {
#if U2_CONTAINERS_USE_CUSTOM_MEMORY_ALLOCATOR == U2_ON
        typedef typename std::list<T, A>                        type;
        typedef typename std::list<T, A>::iterator              iterator;
        typedef typename std::list<T, A>::const_iterator        const_iterator;
#else
        typedef typename std::list<T>                           type;
        typedef typename std::list<T>::iterator                 iterator;
        typedef typename std::list<T>::const_iterator           const_iterator;
#endif
    };
    
    template <typename T, typename P = std::less<T>, typename A = STLAllocator<T, GeneralAllocPolicy> >
    struct set
    {
#if U2_CONTAINERS_USE_CUSTOM_MEMORY_ALLOCATOR == U2_ON
        typedef typename std::set<T, P, A>                      type;
        typedef typename std::set<T, P, A>::iterator            iterator;
        typedef typename std::set<T, P, A>::const_iterator      const_iterator;
#else
        typedef typename std::set<T, P>                         type;
        typedef typename std::set<T, P>::iterator               iterator;
        typedef typename std::set<T, P>::const_iterator         const_iterator;
#endif
    };
    
    template <typename K, typename V, typename P = std::less<K>, typename A = STLAllocator<std::pair<const K, V>, GeneralAllocPolicy> >
    struct map
    {
#if U2_CONTAINERS_USE_CUSTOM_MEMORY_ALLOCATOR == U2_ON
        typedef typename std::map<K, V, P, A>                   type;
        typedef typename std::map<K, V, P, A>::iterator         iterator;
        typedef typename std::map<K, V, P, A>::const_iterator   const_iterator;
#else
        typedef typename std::map<K, V, P>                      type;
        typedef typename std::map<K, V, P>::iterator            iterator;
        typedef typename std::map<K, V, P>::const_iterator      const_iterator;
#endif
    };
    
    template <typename K, typename V, typename P = std::less<K>, typename A = STLAllocator<std::pair<const K, V>, GeneralAllocPolicy> >
    struct multimap
    {
#if U2_CONTAINERS_USE_CUSTOM_MEMORY_ALLOCATOR == U2_ON
        typedef typename std::multimap<K, V, P, A>                  type;
        typedef typename std::multimap<K, V, P, A>::iterator        iterator;
        typedef typename std::multimap<K, V, P, A>::const_iterator  const_iterator;
#else
        typedef typename std::multimap<K, V, P>                     type;
        typedef typename std::multimap<K, V, P>::iterator           iterator;
        typedef typename std::multimap<K, V, P>::const_iterator     const_iterator;
#endif
    };
    
} // U2EG_NAMESPACE_NAME



#endif
