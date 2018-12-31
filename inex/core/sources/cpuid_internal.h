#ifndef CPUID_INTERNAL_H_INCLUDED
#	define CPUID_INTERNAL_H_INCLUDED

namespace inex {
namespace threading {
namespace detail {
    void	cpuid_platform ( s32 registers[ 4 ], s32 current_register );
    void    cpuid_fill     ( s32 registers[ 4 ], s32 current_register );
} // namespace detail
} // namespace threading
} // namespace inex

#endif // #ifndef CPUID_INTERNAL_H_INCLUDED
