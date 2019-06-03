////////////////////////////////////////////////////////////////////////////
//	Created 	: 02.06.2019
//	Author		: Feudor Shelipov
////////////////////////////////////////////////////////////////////////////

#ifndef THREADING_FUNCTIONS_LINUX_INLINE_H_INCLUDED
#   define THREADING_FUNCTIONS_LINUX_INLINE_H_INCLUDED

namespace inex {
namespace threading {

// __sync_fetch_and_add contains a barrier before and after increment
// so it forces compiler not to reorder instructions interlocked incremend surrounded by

#   ifdef INEX_NON_ATOMIC
#       define INEX_INTERLOCKED_INCREMENT( a, b )   ( a )
#   else // #ifdef INEX_NON_ATOMIC
#       define INEX_INTERLOCKED_INCREMENT( a, b )   ( __sync_fetch_and_add( a, b ) )
#   endif // #ifdef INEX_NON_ATOMIC

inline
u64     cache_line_size ( )
{
    return          sysconf( _SC_LEVEL1_DCACHE_LINESIZE );
}

/*
 * Was forced to use tmp instead of src in inline asm
 * cuz with src it doesn't modify 'value'
*/

inline
atomic32_value_type interlocked_increment ( atomic32_type* value )
{
    atomic32_type temp          = * value + 1;
    __asm__ __volatile__
    (
        "m_wait     :                       \n\t"
        "movl       %[tmp],     %%eax       \n\t"
        "cmpxchgl   %%eax,      %[tmp]      \n\t"
        "jnz        m_wait                  \n\t"
        "xchgl      %[src],     %[tmp]      \n\t"
        : [ src ] "+m"( *value ), [ tmp ] "=r" ( temp ) : : "memory", "cc"
    );

    return          temp;//INEX_INTERLOCKED_INCREMENT( value, * value ) + 1;
}

} // namespace threading
} // namespace inex

#endif // #ifndef THREADING_FUNCTIONS_LINUX_INLINE_H_INCLUDED
