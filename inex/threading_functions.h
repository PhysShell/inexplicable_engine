////////////////////////////////////////////////////////////////////////////
//	Created 	: 02.06.2019
//	Author		: Feudor Shelipov
////////////////////////////////////////////////////////////////////////////

#ifndef THREADING_FUNCTIONS_H_INCLUDED
#   define THREADING_FUNCTIONS_H_INCLUDED

#   include <inex/types.h>
#   include <inex/macro_platform.h>

namespace inex {
namespace threading {

inline  u64 cache_line_size                     ( );
inline  u64 processors_available                ( );
inline  u64 clock_cycle_count                   ( );
inline  u64 clock_cycle_per_second              ( );

#   if INEX_PLATFORM_LINUX
        typedef s64                             atomic64_value_type;
        typedef atomic64_value_type volatile    atomic64_type;
        typedef s32                             atomic32_value_type;
        typedef atomic32_value_type volatile    atomic32_type;
#   elif INEX_PLATFORM_WINDOWS // #if INEX_PLATFORM_LINUX
        typedef u64                             atomic64_value_type;
        typedef atomic64_value_type volatile    atomic64_type;
        typedef long							atomic32_value_type;
        typedef atomic32_value_type volatile    atomic32_type; 
#	else
#		error please define atomics for your platform here
#   endif // #if INEX_PLATFORM_LINUX

        typedef pvoid							atomic_ptr_value_type;
	    typedef atomic_ptr_value_type volatile	atomic_ptr_type;

INEX_CORE_API	inline  atomic32_value_type         interlocked_increment   ( atomic32_value_type* );
INEX_CORE_API	inline 	u32 						current_thread_id		( );
INEX_CORE_API	inline	void 						yield					( u32 ms );


} // namespace threading
} // namespace inex

#   if INEX_PLATFORM_LINUX
#       include <inex/threading_functions_linux_inline.h>
#	elif INEX_PLATFORM_WINDOWS
#		include <inex/threading_functions_win_inline.h>
#   endif // #if INEX_PLATFORM_LINUX



#endif // #ifndef THREADING_FUNCTIONS_H_INCLUDED
