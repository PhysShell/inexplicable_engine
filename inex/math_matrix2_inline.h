////////////////////////////////////////////////////////////////////////////
//	Created 	: 08.04.2019
//	Author		: Feudor Shelipov
////////////////////////////////////////////////////////////////////////////

#ifndef MATH_MATRIX2_INLINE_H_INCLUDED
#   define MATH_MATRIX2_INLINE_H_INCLUDED

namespace inex {
namespace math {

inline
matrix2::type *   matrix2::operator [ ] ( u8 index )
{
    ASSERT_S            ( ( index < 2 ) );
    return              * ( ( & x + index )[ 0 ] );
}

inline
matrix2::type const *   matrix2::operator [ ] ( u8 index ) const
{
    ASSERT_S            ( ( index < 2 ) );
    return              * ( ( & x + index )[ 0 ] );
}

} // namespace math
} // namespace inex

#endif // #ifndef MATH_MATRIX2_INLINE_H_INCLUDED
