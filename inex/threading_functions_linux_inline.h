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

INEX_CORE_API
inline
atomic_ptr_value_type interlocked_compare_exchange_pointer( atomic_ptr_type& target, atomic_ptr_value_type const exchange, atomic_ptr_value_type const comperand )
{
    NOT_IMPLEMENTED                 ( );
	return							0;
}

INEX_CORE_API
inline
atomic32_value_type 	interlocked_exchange			( atomic32_type& target, atomic32_value_type value )
{
    NOT_IMPLEMENTED                 ( );
	return							0;
}

INEX_CORE_API
inline
atomic_ptr_value_type	interlocked_exchange_pointer	( atomic_ptr_type& target, atomic_ptr_value_type const value )
{
    NOT_IMPLEMENTED                 ( );
	return							0;
}

inline
u64     cache_line_size ( )
{
    return          sysconf( _SC_LEVEL1_DCACHE_LINESIZE );
}

inline
u64      processors_available ( )
{
    return          sysconf( _SC_NPROCESSORS_ONLN );
}

namespace detail {
    __inline__
    bool    cpuid_instruction_available ( )
    {
        __try
        {
            __asm__ ( "cpuid\n\t" );
        }
        __catch ( ... )
        {
            return          0;
        }
        return              1;
    }
} // namespace detail

inline
u64 clock_cycle_per_second ( )
{
    return                  sysconf ( _SC_CLK_TCK );
}

/***
*
* u64 clock_cycle_count ( )
*
*
* Exit:
*
*   Returns cycles passed ( for commands measurement )
*
****************************************************/


__inline__
u64     clock_cycle_count ( )
{
    u64 eax;
#   ifdef __i386
    __asm__ __volatile__ ( "rdtsc" : "=A" ( eax ) );
#   elif __amd64 // #ifdef __i386
    u64 edx;
    __asm__ __volatile__
    (
        // "cpuid\n\t" // cpuid takes about ~200 cycles...

        //"movl %%edx, %%ecx\n\t"
        "rdtsc\n\t"
        //"movl (eax_internal), %%ecx\n\t"
        //"movl %%eax,     %[eax_internal]\n\t"
        //"movl %%edx,     %0\n\t"
        //"xorl %%ecx, %%edx\n\t"
        //"shll $32, %%edx\n\t"
        //"orl %%edx, %%eax\n\t"
        : "=a" ( eax ), "=d" ( edx )
    );
    //printf( "EAX:\t'%d'; EDX:\t'%d'\n", eax, edx );
    eax             = ( eax | ( edx << 32 ) );
#   endif // #ifdef __i386
    return              eax;
}

/*
 * Was forced to use tmp instead of src in inline asm
 * cuz with src in opcodes ( instead of tmp ) it doesn't modify 'value'
*/

/***
*
* atomic32_value_type interlocked_increment ( atomic32_type* value )
*
* Entry:
*
*   value: atomic variable to be changed atomically
*
* Exit:
*
*   Returns previous value storied in 'value'
*
****************************************************/


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

inline
atomic32_value_type interlocked_decrement ( atomic32_type* value )
{
    NOT_IMPLEMENTED                 ( );
	return							0;
}

} // namespace threading
} // namespace inex

#endif // #ifndef THREADING_FUNCTIONS_LINUX_INLINE_H_INCLUDED
