#include "stdafx.h"
#include "fs_ini_file.h"
#include "ie_trims.h"
#include <iostream>
#include <algorithm>
#include <cstring>
#include <stdlib.h>
#include "ie_memory.h"
  
namespace inex {
namespace core {

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
	fs::reader *r			= { fsmgr::r_open( fname ) };

	//log::Msg( "address of reader allocated: %p", r );

	ASSERT_D( r, "Reader was set to 0!" );
	


	using namespace inex::core::str;
	using namespace inex::core::memory;
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
//			log::Msg( "found '['" );
            if ( current )
			{ // xray does this like this:
            // root_const_iterator it=lower_bound(v.begin(),v.end(),current->name,sect_pred);
            // sect pred uses strcmp
            //if(it!=v.end()) ERROR. R_CIthey check if current->NAme==(*it)->name


				//if ( !m_contents.size( ) )
				//{
				//	printf( "Empty\n" );
				//}

//				log::Msg( "current true, before for" );
				for ( root_const_iterator	it	=	m_contents.begin( );
											it	!=	m_contents.end( );
											++it )
				{
					//std::cin >> ch;
                    ASSERT_D( 0!= ( strcmp( ( *it )->name, current->name ) ), "Duplicate section '%s' found.", current->name );
                }

//				log::Msg( "current, before inserting" );
                m_contents.insert( m_contents.end( ), current );
            }

//			log::Msg( "after current '['" );

            pstr name			= 	strchr( buf, ']' );
            ASSERT_D				( name, "Bad ini section found: %s", buf );
            *name				=	0;
//			log::Msg( "allocating new section %s", name );
            current				=	ie_new< section >( );
            current->name		=	ie_allocate< char >( strlen( buf ) );
            strcpy					( current->name, buf + 1 );
			//std::cout			<< "current name: " << current->name << '\n';

        }
		else
		{
//			log::Msg( "NOT '[' found! %s BUF", buf);

            if( current )
			{
//				log::Msg( "current true!" );
                item i;
                pstr t			=	strchr( buf, '=' );
                ASSERT_S( t != nullptr );
                *t				=	0;
                i.first			=	ie_allocate< char >( strlen( buf) + 1 );
                strcpy				( i.first, buf );
                ++t;
                i.second		=	ie_allocate< char >( strlen( t ) + 1 );
                strcpy				( i.second, t );
//				log::Msg( "%s = %s!", i.first, i.second );
                current->data.insert( current->data.end( ), i );
            }
        }
    }
	
//	log::Msg( "exited statements!" );
	//char ch;
    if ( current )
	{
        for ( root_const_iterator	it	=	m_contents.begin( );
									it	!=	m_contents.end( );
									++it )
		{
            ASSERT_D( ( strcmp( ( *it )->name, current->name ) !=0 ), "Duplicate section '%s' found.", current->name );
			//std::cout << "WTF " << current->name << '\n';
			//std::cout << ( *m_contents.rend( ) )->name << '\n';
			//std::cin >> ch;
		}
    }

	m_contents.insert( m_contents.end( ), current );

	//log::Msg( "trying to find in memory %p", r );

	//memory::dump_memory_contents( );

	//fs::virtual_file_reader* pt	= static_cast<  fs::virtual_file_reader* >( r );

	//log::Msg( "PT'sect MEMORY %p", pt );

	fsmgr::r_close( r );

	//float   s={r_float("m_smt","flt")};
	//std::cout<<s<<'\n';

	for ( root_const_iterator	it	=	m_contents.begin( );
								it	!=	m_contents.end( );
								++it )
	{
		std::cout << ( *it )->name << '\n';
		//std::cin >> ch;
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



} // names core
} // namespace inex
