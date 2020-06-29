#ifndef STL_EXTENSIONS_VECTOR_H_INCLUDED
#	define STL_EXTENSIONS_VECTOR_H_INCLUDED

#include "stl_extensions.h"



// doesn't seem we need this line here
//template class _declspec(dllexport)     ie_vector<int>;


// auxilary definition
DEFINE_VECTOR( int, intVec, intIt );
DEFINE_VECTOR( float, floatVec, floatIt );

// yes, since vector<bool> is some kind of a bitset, I'm gonna use char type
//DEFINE_VECTOR(char,boolVec,boolIt);

#endif // #ifndef STL_EXTENSIONS_VECTOR_H_INCLUDED