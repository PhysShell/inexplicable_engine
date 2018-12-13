#include "stdafx.h"

#include "ie_trims.h"
#include <inex/core/ie_core.h>

namespace inex {
namespace core {
namespace str {

void	copy_command_line_argunement ( pcstr src, pstr dst, u8 separator )
{
    pcstr p			=	strchr( src, '=' );
    ASSERT_D( p, "error while parsing cmd-argument %s", src );

    size_t n		=	{ };
	// p points to '=' currently so skip it
    ++p; 
    while ( *p && *p != separator )
	{
		dst[ n++ ] 	= 	*p++;
	}

    dst[ n ]  		=	0;
}

pstr	get_command_line_argument ( pcstr k, pstr v )
{
    pcstr p;
    if ( !( p = strstr( get_params( ), k ) ) )
    {
		return			nullptr;
	}

    size_t n			= { };
    p   				= strchr( p,'=' );
    // maybe check if the '=' relates exactly to the key we need?
    ASSERT_D( p, "Couldn't read value of the cmd-line argument '%s'. Did you forget '='?", k );

    // p points to '=' currently
    ++p;
    while ( *p && *p != '-' )
	{
		 v[ n++ ]		= *p++;
	}
	
    v[ n ]  			= 0;
    return  			v;
}

inline
pstr	find_trim_character ( pstr src )
{
    for ( pstr p = src; *p; ++p )
	{
        if ( *p <= ' ' )
		{
            return	p;
		}
	}

    return			nullptr;
}


void	trim_string ( pstr tgt )
{
    pstr p;
    size_t c			= { 0 };
    while ( (p = find_trim_character( tgt ) ) )
	{
        while ( p[ ++c ] <= ' ' && p[ c ] );
        strcpy			( p, ( p + c ) );
        c       		= 0;
    }
}


/*
int trim (char s [] )
{
int n;
for (n = strlen(s)-1; n >= 0; n--)
if (s[n] != '' ' && s[n] != '\t' && s[n] != '\n' )
break;
s[n+1]=0;
return n;
}*/
//void _Trim_LR  (char* tgt)
//{
//    char        *p;
//    size_t      c={0};
//    size_t      slen={strlen(tgt)};
//     while(0!=(p=strchr(tgt,' '))) {
//        while(p[++c]==' ');
//        //std::cout<<"Found " << c <<"spaces together!\n";
//        strcpy(p,(p+c));
//        p[slen-c]=0;
//        c=0;
//        //std::cout<<"TGT IS NOW: "<<tgt<<'\n';
//        //getch();
//    }
//
//    while(0!=(p=strchr(tgt,'\t'))) {
//        while(p[++c]=='\t');
//        //std::cout<<"Found " << c <<"spaces together!\n";
//        strcpy(p,(p+c));
//        p[slen-c]=0;
//        c=0;
//        //std::cout<<"TGT IS NOW: "<<tgt<<'\n';
//        //getch();
//    }
//}

void	trim_string_left ( pstr& tgt )
{
    pstr p			= tgt;
    size_t      s	= { };
    while ( p[ s ] <= ' ' )
	{ 
		++s;
	}

    tgt				+= s;
}

void	trim_string_right ( pstr& tgt )
{
    pstr p			= tgt + strlen( tgt );
    size_t s		= { strlen( tgt ) };
    while ( p[ s ] <= ' ' )
	{
		--s;
	}
	
    tgt[ s ]		= 0;
}

void	handle_comments ( pstr tgt )
{
    //if(tgt[0]&&tgt[0]==';')
    //    return true;

    pstr p			= strchr( tgt, ';' );
    if ( !p )
	{
		return;
	}
	
    if ( p!= tgt )	
	{
		*p			= 0;
	}
}

} // namespace str
} // namespace core
} // namespace inex
