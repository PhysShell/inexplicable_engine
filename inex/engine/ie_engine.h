////////////////////////////////////////////////////////////////////////////
//	Created 	: 09.02.2018
//	Author		: Feudor Shelipov
////////////////////////////////////////////////////////////////////////////

#ifndef IE_ENGINE_H_INCLUDED
#	define IE_ENGINE_H_INCLUDED

#	include <inex/utils.h>

namespace inex {
namespace engine  {

struct /*_declspec(novtable)*/  engine_base											
{
	virtual void 	exit					( s32 exit_code ) = 0;
	virtual void 	set_exit_code			( s32 exit_code ) = 0;
	virtual int		get_exit_code			( ) const = 0;
protected:
	IE_DECLARE_PURE_VIRTUAL_DESTRUCTOR( engine_base )
}; // struct engine_base

class engine : 
			inex::nonassignable, 
			inex::noncopyable, 
			public engine_base
{
public:
					engine					( u32 argc , pstr* argv, pvoid instance = 0 );
					engine					( )					{							}
	virtual			~engine					( );
	virtual void 	exit					( s32 error_code )	{ m_exit_code = error_code;	}
	virtual s32		get_exit_code			( ) const			{ return m_exit_code;		}
	virtual void 	set_exit_code			( s32 error_code )	{ m_exit_code = error_code; }

//			void	run						( );
private:
	s32						m_exit_code;
}; // class engine

} //namespace inex
} //namespace engine
#endif // #ifndef IE_ENGINE_H_INCLUDED
