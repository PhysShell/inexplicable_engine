#include "pch.h"

#include <inex/render/base/world.h>
#include <inex/render/api.h>

typedef inex::render::render_allocator_type	render_allocator_type;
typedef inex::render::logic_allocator_type	logic_allocator_type;
typedef inex::render::editor_allocator_type	editor_allocator_type;

using inex::render::base_world;

//static inex::uninitialized_reference<base_world>	s_world;
static base_world	*	s_world;

//render_allocator_type*	inex::render::g_allocator = 0;
//logic_allocator_type*	inex::render::logic::g_allocator = 0;
//editor_allocator_type*	inex::render::editor::g_allocator = 0;

void inex::render::memory_allocator		(
		render_allocator_type&	render_allocator,
		logic_allocator_type&	logic_allocator,
		editor_allocator_type&	editor_allocator
	)
{
	//R_ASSERT			( !g_allocator );
	//g_allocator			= &render_allocator;

	//R_ASSERT			( !logic::g_allocator );
	//logic::g_allocator	= &logic_allocator;

	//R_ASSERT			( !editor::g_allocator );
	//editor::g_allocator	= &editor_allocator;
}

inex::render::world* inex::render::create_world	( inex::render::engine::wrapper& wrapper, HWND window_handle )
{
	//XRAY_CONSTRUCT_REFERENCE( s_world, base_world)	( wrapper, window_handle );
	s_world					= new base_world( wrapper, window_handle );
	return					( &*s_world );
}

void inex::render::destroy_world					( inex::render::world*& world )
{
	//ASSERT_S				( &*s_world == world );
	delete					s_world;
	//XRAY_DESTROY_REFERENCE	( s_world );
	world					= 0;
}