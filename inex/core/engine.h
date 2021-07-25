////////////////////////////////////////////////////////////////////////////
//	Created		: 02.11.2020
//	Author		: Feudor Shelipov
////////////////////////////////////////////////////////////////////////////

#ifndef INEX_CORE_ENGINE_H_INCLUDED
#	define INEX_CORE_ENGINE_H_INCLUDED

namespace inex {
namespace core {

struct NOVTABLE engine {
	virtual			~engine					( ) { }
	virtual void 	exit					( int exit_code ) = 0;
	virtual void 	set_exit_code			( int exit_code ) = 0;
	virtual int  	get_exit_code			( ) const = 0;
	virtual	pcstr	get_resource_path		( ) const = 0;
	virtual	pcstr	get_mounts_path			( ) const = 0;
	virtual	pcstr	get_underscore_G_path	( ) const = 0;
}; // class engine

} // namespace core
} // namespace inex

#endif // #ifndef INEX_CORE_ENGINE_H_INCLUDED