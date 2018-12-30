#include "stdafx.h"
#include "fs_ini_file.h"
#include "ie_trims.h"
#include <iostream>
#include <algorithm>
#include <cstring>
#include <stdlib.h>
#include "ie_memory.h"
  
namespace inex {
namespace ini {

ini_file::~ini_file ( )
{
	for ( root_const_iterator	it 	=	m_contents.begin( );
								it	!=	m_contents.end( );
								++it )
	{
		for ( section_contents_const_iterator	sect_it	=	( *it )->data.begin( ); 
												sect_it	!=	( *it )->data.end( ); 
												++sect_it )
		{
			memory::ie_delete( ( *sect_it ).first );
			memory::ie_delete( (*sect_it ).second );
		}

		memory::ie_delete( ( *it )->name );
		memory::ie_delete( ( *it ) );
	}
}

void	ini_file::load ( pcstr fname )
{
	fs::reader *r			= { fs::r_open( fname ) };
	ASSERT_D( r, "Reader was set to 0!" );
	section* current			= nullptr;

    while ( !r->eof( ) )
	{
        string1024 buf		= 	{ };
        r->r_string				( buf, sizeof( buf ) );
        if ( buf[ 0 ] && ( buf[ 0 ] == ';' || buf[ 0 ] == '\n' ) )
		{
			continue;
		}

        trim_string					( buf );
        handle_comments				( buf );
        if ( buf[ 0 ] == 0 )
		{
			continue;
		}

        if ( buf[ 0 ] == '[' )
		{
            if ( current )
			{
				for ( root_const_iterator	it	=	m_contents.begin( );
											it	!=	m_contents.end( );
											++it )
				{
                    ASSERT_D( 0!= ( strcmp( ( *it )->name, current->name ) ), "Duplicate section '%s' found.", current->name );
                }

                m_contents.insert	( m_contents.end( ), current );
            }

            pstr name			= 	strchr( buf, ']' );
            ASSERT_D				( name, "Bad ini section found: %s", buf );
            *name				=	0;
            current				=	memory::ie_new< section >( );
            current->name		=	memory::ie_allocate< char >( strlen( buf ) );
            strcpy					( current->name, buf + 1 );
        }
		else
		{
            if( current )
			{
                item i;
                pstr t			=	strchr( buf, '=' );
                ASSERT_S( t != nullptr );
                *t				=	0;
                i.first			=	memory::ie_allocate< char >( strlen( buf) + 1 );
                strcpy				( i.first, buf );
                ++					t;
                i.second		=	memory::ie_allocate< char >( strlen( t ) + 1 );
                strcpy				( i.second, t );
                current->data.insert( current->data.end( ), i );
            }
        }
    }

    if ( current )
	{
        for ( root_const_iterator	it	=	m_contents.begin( );
									it	!=	m_contents.end( );
									++it )
		{
            ASSERT_D( ( strcmp( ( *it )->name, current->name ) !=0 ), "Duplicate section '%s' found.", current->name );
		}
    }

	m_contents.insert( m_contents.end( ), current );
	fs::r_close( r );

	for ( root_const_iterator	it	=	m_contents.begin( );
								it	!=	m_contents.end( );
								++it )
	{
		std::cout << ( *it )->name << '\n';
	}

}

ini_file::section*	ini_file::r_section ( pcstr sect ) const
{
    root_const_iterator it			= { m_contents.begin( ) };
    root_const_iterator end_it 		= { m_contents.end() };

    for ( ; it != end_it; ++it )
	{
        if ( !( strcmp( sect, ( *it )->name) ) )
		{
			break;
		}
    }

    ASSERT_D( it != end_it, "Can't open section '%s'", sect );
    return  				( *it );
}

pcstr	ini_file::r_string ( pcstr sect, pcstr key ) const
{
    section* current						= r_section( sect );
    section_contents_const_iterator it    	= { current->data.begin( ) };
    section_contents_const_iterator end_it 	= { current->data.end( ) };

    for ( ; it != end_it; ++it )
	{
        if ( !( strcmp( key, ( *it ).first ) ) )
		{
			break;
		}
    }

    ASSERT_D( it != end_it, "Can't find variable '%s' in [%s]", key, sect );
    return  								( *it ).second;
}

s32		ini_file::r_s32 ( pcstr sect,pcstr key ) const
{
	return				static_cast< s32 >( std::atoi( r_string( sect, key) ) );
}

float	ini_file::r_float ( pcstr sect,pcstr key ) const
{
	return				static_cast< float >( std::atof( r_string( sect, key ) ) );
}

} // namespace ini
} // namespace inex
