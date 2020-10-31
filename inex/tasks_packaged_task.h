////////////////////////////////////////////////////////////////////////////
//	Created		: 26.10.2020
//	Author		: Feudor Shelipov
////////////////////////////////////////////////////////////////////////////

#ifndef TASK_PACKAGED_TASK_H_INCLUDED
#	define TASK_PACKAGED_TASK_H_INCLUDED

#	include <thread>

namespace inex {
namespace tasks {

template < 
	typename 
> class packaged_task;

template < typename function, typename ... parameters_pack_0 >
class packaged_task< function ( parameters_pack_0 ... ) >
{
public:
	template < typename ... parameters_pack_1 >
	explicit 							packaged_task		( parameters_pack_1 ... parameters ) : m_function( std::forward< parameters_pack >( parameters ) ... )
	{
	}
	
	// disable copy, default move
	
	template < typename ... parameters_pack_1 >
	inline		void					operator ( )		( parameters_pack_1 ... parameters )
	{
		m_promise.set_value				( m_function( std::forward< parameters_pack_1 >( parameters ) ... ) );
	}
						
	inline		std::future< function >	get_future			( )
	{
		return 	m_promise.get_future( );			
	}
						
	
	
private:
	std::function	< function( parameters_pack_0 ... ) >	m_function;
	std::promise	< function >							m_promise;
};
	
} // namespace tasks
} // namespace inex
#endif // #ifndef TASK_PACKAGED_TASK_H_INCLUDED