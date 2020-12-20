////////////////////////////////////////////////////////////////////////////
//	Created		: 26.10.2020
//	Author		: Feudor Shelipov
////////////////////////////////////////////////////////////////////////////

#ifndef TASK_PACKAGED_TASK_H_INCLUDED
#	define TASK_PACKAGED_TASK_H_INCLUDED

#	include <thread>
#	include <future>

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
	explicit 							packaged_task		( parameters_pack_1 ... parameters ) : m_function( std::forward< parameters_pack_1 >( parameters ) ... )
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

template < typename F >
inline auto async ( F&& func ) -> std::future< decltype( func( ) ) >
{
	typedef				decltype( func( ) )	result_type;
	auto promise		= std::promise< result_type > ( );
	auto future			= promise.get_future ( );
	std::thread ( std::bind( [ = ] ( std::promise< result_type > & promise )
	{
		try				{ promise.set_value( func( ) ); } // it doesn't handle void return type
		catch ( ... )	{ promise.set_exception( std::current_exception ); }
	}, std::move( promise ) ) ).detach( );

	return				std::move( future );
}

} // namespace tasks
} // namespace inex
#endif // #ifndef TASK_PACKAGED_TASK_H_INCLUDED


