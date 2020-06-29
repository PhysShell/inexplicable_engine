////////////////////////////////////////////////////////////////////////////
//	Created 	: 02.06.2019
//	Author		: Feudor Shelipov
////////////////////////////////////////////////////////////////////////////

#ifndef THREADING_FUNCTIONS_WIN_INLINE_H_INCLUDED
#   define THREADING_FUNCTIONS_WIN_INLINE_H_INCLUDED

#	include <Windows.h>
#	include <inex/types.h>

namespace inex {
namespace threading {

inline
atomic32_value_type		interlocked_increment	( atomic32_type* )	{	return 0;	}


inline
u64		clock_cycle_count						( )					{	return 0;	}

inline
u64		clock_cycle_per_second					( )					{	return 0;	}

inline
u64     cache_line_size ( )
{
	return				0;
    //size_t  line_size                           = 0;
    //DWORD   buffer_size                         = 0;
    //DWORD   i                                   = 0;
    //SYSTEM_LOGICAL_PROCESSOR_INFORMATION* buffer = 0;

    //GetLogicalProcessorInformation              ( 0, &buffer_size );
    //buffer                                      =
    //    ( SYSTEM_LOGICAL_PROCESSOR_INFORMATION* ) malloc( buffer_size );
    //GetLogicalProcessorInformation              ( &buffer[ 0 ], &buffer_size );

    //for (   i       = 0;
    //        i       = buffer_size / sizeof( SYSTEM_LOGICAL_PROCESSOR_INFORMATION ); 
    //        ++      i)
    //{
    //    if ( buffer[ i ].Relationship == RelationCache && buffer[ i ].Cache.Level == 1 )
    //    {
    //        line_size                           = buffer[ i ].Cache.LineSize;
    //        break;
    //    }
    //}

    //free                                        ( buffer );
    //return                                      line_size;
}

} // namespace threading
} // namespace inex

#endif // #ifndef THREADING_FUNCTIONS_WIN_INLINE_H_INCLUDED
