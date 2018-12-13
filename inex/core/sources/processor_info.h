#ifndef PROCESSOR_INFO_H_INCLUDED
#	define PROCESSOR_INFO_H_INCLUDED

//void __cpuid_count  ( int ptr, void* i1, int i11, int i2, int i3,int i4);

namespace inex {
namespace core {
namespace CPU {

    void print_cpu_info	( );
    void get_cpu_feats  ( );

} // namespace CPU
} // namespace core
} // namespace inex

#endif // #ifndef PROCESSOR_INFO_H_INCLUDED
