#ifndef IE_ENGINE_H_INCLUDED
#	define IE_ENGINE_H_INCLUDED



namespace inex {
namespace engine  {

struct /*_declspec(novtable)*/  engine_base
{

	virtual			~engine_base			( ) 				{ }
	virtual void 	exit					( s32 exit_code ) = 0;
	virtual void 	set_exit_code			( s32 exit_code ) = 0;
	virtual int		get_exit_code			( ) const = 0;
}; // class IEngine

class engine :
	public engine_base
{

public:
					engine					( s32 argc , pstr* argv );
	virtual			~engine					( );
	virtual void 	exit					( s32 error_code )	{ m_exit_code = error_code; /*xray::debug::terminate("");*/}
	virtual int		get_exit_code			( ) const			{ return m_exit_code; }
	virtual void 	set_exit_code			( s32 error_code )	{ m_exit_code = error_code; }

private:
	s32		m_exit_code;
}; // class engine

} //namespace inex
} //namespace engine
#endif // #ifndef IE_ENGINE_H_INCLUDED
