#ifndef INEX_CORE_H_INCLUDED
#	define INEX_CORE_H_INCLUDED

#	include <inex/core/api.h>

//namespace inex {using inex::core::logging::Msg;}
namespace inex {
namespace core {

void    INEX_CORE_API	initialize	( s32, pstr* );
void    INEX_CORE_API  finalize		( );
//#ifdef USE_SINGLETON
//#define get_params() Params
extern	INEX_CORE_API	string128	command_line_parameters;
//#endif //#ifdef get_params()

//#else
pstr    INEX_CORE_API  get_params  ( );
//#endif // #ifdef USE_SINGLETON
    //

    //string512	Params;
    //string64	User;

} // names core
} // namespace inex



#endif // #ifnded INEX_CORE_H_INCLUDED
