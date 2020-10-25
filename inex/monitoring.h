////////////////////////////////////////////////////////////////////////////
//	Created		: 25.10.2020
//	Author		: Feudor Shelipov
////////////////////////////////////////////////////////////////////////////

#ifndef MONITORING_H_INCLUDED
#   define MONITORING_H_INCLUDED

#   include <inex/extensions.h>
#   include <inex/core/sources/fs_file_system_internal.h>

namespace inex {

////////////////////////////////////////////////////////////////////////////
u64     memory_usage ( )
{
    string128               buffer;
    fs::memory_mapped_file  src  ( "/proc/self/status" );
    fs::reader              file ( src.m_data, strlen( src.m_data ) );
    pstr                    substring;

    while ( !file.eof( ) )
    {
        file.r_string  ( buffer, sizeof ( buffer ) );

        if ( substring  = strstr( buffer, "VmSize" ) )
        {
            substring       = strchr( buffer, ':' );
            return          std::atol( substring );
        }
    }

    LOGGER( "!Couldn't read /proc/self/status" );
    return                  0;
}

} // namespace inex

#endif // #ifndef MONITORING_H_INCLUDED