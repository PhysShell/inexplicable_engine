#ifndef STL_EXTENSIONS_INLINE_H_INCLUDED
#	define STL_EXTENSIONS_INLINE_H_INCLUDED

#define	TEMPLATE_SPECIALIZATION	\
				template <typename T>

#define	_ie_vector	\
				ie_vector<T>

TEMPLATE_SPECIALIZATION
 
T&	_ie_vector::operator[ ] ( int i )
{
    std::cout			<< "& ";
	return 				std::vector< T >::at( i );
}

TEMPLATE_SPECIALIZATION
inline
T const&	_ie_vector::operator[ ] ( int i ) const
{
    std::cout			<< "const&";
	return 				std::vector< T >::at( i );
}

//inline char& ie_vector<char>::operator[](int i)
//{
//	return std::vector<char>::at(i) ;
//}
//
//inline const char&	ie_vector<char>::operator[]	(int i) const
//{
//	return std::vector<char>::at(i);
//}





#undef TEMPLATE_SPECIALIZATION
#undef _ie_vector

#endif // #ifndef STL_EXTENSIONS_INLINE_H_INCLUDED
