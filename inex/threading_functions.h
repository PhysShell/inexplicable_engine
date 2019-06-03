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

#   if INEX_PLATFORM_LINUX
        typedef s64                             atomic64_value_type;
        typedef atomic64_value_type volatile    atomic64_type;
        typedef s32                             atomic32_value_type;
        typedef atomic32_value_type volatile    atomic32_type;
#   else // #if INEX_PLATFORM_LINUX
#       error please define atomics for your platform here
#   endif // #if INEX_PLATFORM_LINUX

INEX_CORE_API    inline  atomic32_value_type         interlocked_increment   ( atomic32_type* );


} // namespace threading
} // namespace inex

#   if INEX_PLATFORM_LINUX
#       include <inex/threading_functions_linux_inline.h>
#   endif // #if INEX_PLATFORM_LINUX



#endif // #ifndef THREADING_FUNCTIONS_H_INCLUDED
