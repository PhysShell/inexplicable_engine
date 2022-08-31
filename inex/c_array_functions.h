////////////////////////////////////////////////////////////////////////////
//	Created 	: 05.07.2022
//	Author		: Feudor Shelipov
////////////////////////////////////////////////////////////////////////////


#ifndef INEX_C_ARRAY_FUNCTIONS_H_INCLUDED
#	define INEX_C_ARRAY_FUNCTIONS_H_INCLUDED

namespace inex {

template <class T, u32 Count>
inline u32 array_size ( T (&)[Count] )
{
	return	Count;
}

template <class T, u32 Count>
inline T * array_begin ( T (&array)[Count] )
{
	return	& array[0];
}

template <class T, u32 Count>
inline T * array_end ( T (&array)[Count] )
{
	return	& array[Count];
}

namespace detail {

template <typename T, size_t N>
char	( &array_size_helper(T (&array)[N]) ) [N];

} // namespace detail

template <typename T>
struct array_size_helper
{
	enum { count = sizeof( detail::array_size_helper( *(T*)0 ) ) };
}; // struct array_size_helper

} // namespace inex

#endif // #ifndef INEX_C_ARRAY_FUNCTIONS_H_INCLUDED