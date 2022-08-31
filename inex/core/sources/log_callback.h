////////////////////////////////////////////////////////////////////////////
//	Created 	: 30.06.2022
//	Author		: Feudor Shelipov
////////////////////////////////////////////////////////////////////////////

#ifndef LOG_CALLBACK_H_INCLUDED
#   define LOG_CALLBACK_H_INCLUDED


namespace inex {
namespace debug {
typedef		std::function< void (	pcstr	initiator, 
									bool	is_error_verbosity, 
									bool	log_only_user_string, 
									pcstr	message )	>		log_callback;
									
INEX_CORE_API	log_callback	get_log_callback		( );
INEX_CORE_API	log_callback	set_log_callback		( log_callback const & callback );
INEX_CORE_API	void			disable_log_callback	( );
INEX_CORE_API	void			enable_log_callback		( );		
} // namespace debug
} // namespace inex

#endif // #ifndef LOG_CALLBACK_H_INCLUDED