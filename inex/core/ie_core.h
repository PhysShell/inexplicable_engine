#ifndef IE_CORE_H_INCLUDED
#	define IE_CORE_H_INCLUDED

//namespace inex {using inex::core::log::Msg;}
namespace inex {
namespace core {

void    IECORE_API	initialize	( s32, pstr* );
void    IECORE_API  finalize		( );
//#ifdef USE_SINGLETON
//#define get_params() Params
extern	IECORE_API	string128	command_line_parameters;
//#endif //#ifdef get_params()

//#else
pstr    IECORE_API  get_params  ( );
//#endif // #ifdef USE_SINGLETON
    //

    //string512	Params;
    //string64	User;

} // names core
} // namespace inex



#endif // #ifnded IE_CORE_H_INCLUDED
