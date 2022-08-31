#include "pch.h"
#include <inex/render/base/sources/platform_gl4.h>
#include <inex/render/gl4/sources/visual.h>

#include <inex/render/core/shaders.h>

#include <inex/core/sources/fs_ini_file.h>

#include <inex/render/common/sources/system_render.h>

#include <inex/render/common/scene.h>

#include <inex/macro_log.h>

#include <time.h>
#include <math.h>
#include <vector>

#if INEX_PLATFORM_WINDOWS
#	define gl_context GLFWwindow
#   pragma comment( lib, "glfw3.lib" )
#   pragma comment( lib, "opengl32.lib" )
#endif // #if INEX_PLATFORM_WINDOWS
//#pragma comment(lib,"d3d9.lib")
//#pragma comment(lib,"d3gl3.lib")
//#pragma comment(lib,"dxerr.lib")

//const DWORD vertex_colored_fvf	= (D3DFVF_XYZ | D3DFVF_DIFFUSE);
//const DWORD ui_vertex_fvf		= (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1);

//using inex::render::gl4::world;
//using inex::resources::managed_resource_ptr;
//using inex::memory::chunk_reader;

#define ARRAY_COUNT( array ) (sizeof( array ) / (sizeof( array[0] ) * (sizeof( array ) != sizeof(void*) || sizeof( array[0] ) <= sizeof(void*))))


namespace inex {

// 4x4 operations
using math::float4;
using math::float3;

using inex::render_ogl::shader;
using inex::render_ogl::shader_program;


// just testing
math::float4x4 vertices; // = points;
math::float4x4 vertices_2;

render::triangle_primitive_visual triangle;

void    initialize_shaders ( )
{
   // LOGGER              ( "\tinitializing shaders" );           // TODO: make shader append gamedata/shaders!
	//triangle.set_shader	( "gamedata/shaders/ogl4.vs", "gamedata/shaders/ogl4.fs");

    //program.use         ( );
    //program.unbind      ( );
}

void    initialize_vertex_buffer_object ( )
{
	//math::float4x4 t		= points1;
	//triangle.load			( t );
}

namespace render {

//command_line::key	s_render_test_scene("render_test_scene", "", "render", "renders test scene");

namespace gl4 {

render::platform * create_render_platform( inex::render::engine::wrapper& wrapper, HWND window_handle)
{
	return							new platform( wrapper, window_handle );
}


//void create_pixel_shader(pcstr text, IDirect3DPixelShader9** dest, IDirect3DDevice9* device, pcstr entrypoint);
//void create_vertex_shader(pcstr text, IDirect3DVertexShader9** dest, IDirect3DDevice9* device, pcstr entrypoint);

//extern float4 g_debug_color;

platform* pw				= nullptr;
platform&	get_w ( )		{ return *pw; }

float cam_speed				/*= .01f*/;				// 1 unit per second
float cam_yaw_speed			/*= .5f*/;				// 10 degrees p er second
float cam_pos[ ]			= { .0f, .0f, 2.f };	// don't start at zero, or we will be too close
float cam_yaw 				= .0f;					// y-rotation in degrees

int	  view_mat_location;

void	initialize_model_manager ( model_manager& manager )
{
	LOGGER( "initializing model manager...\n" );

	resources::managed_resource_ptr resource;
	resource.m_vertices	= vertices;
	resource.fs			= "gamedata/shaders/ogl4.fs";
	resource.vs			= "gamedata/shaders/ogl4.vs";

	resources::managed_resource_ptr resource2;
	resource2.m_vertices	= vertices_2;
	//resource2.m_vertices.print  ( );
	resource2.fs			= "gamedata/shaders/ogl4.fs";
	resource2.vs			= "gamedata/shaders/ogl4.vs";

	manager.add_static	( resource, resource, resource  );
	manager.add_static	( resource2, resource2, resource2  );


}

platform::platform					( inex::render::engine::wrapper& wrapper, HWND const window_handle ) :
// #pragma warning ( push )
// #pragma warning ( disable : 4355 )
// 	render::base_world	( wrapper, *this ),
// #pragma warning ( pop )
	//m_ui_texture_font			( 0 ),
	//m_ui_texture				( 0 ),
	//m_ui_ps						( 0 ),
	//m_ui_ps_font				( 0 ),
	//m_ui_ps_fill				( 0 ),
	//m_debug_vb					( 0 ),
	//m_debug_ib					( 0 ),
	//m_editor_vb					( 0 ),
	//m_editor_ib					( 0 ),
	//m_editor_selected_color		( 1.f, 1.f, 0.f, 1.f ),
	//m_ps_geom					( 0 ),
	m_hw						( wrapper, window_handle ),
//	m_started_scene				( false ),
	m_render_frame_id			( 0 ),
	//m_line						( 0 ),
	m_render_test_scene			( 1 )
	//m_res_mgr					( true )//s_render_test_scene.is_set() )
{


	pw							= this;

	m_scene						= new scene_render( true );

	//glEnable					( GL_CULL_FACE ); 	// cull face
	//glCullFace					( GL_BACK );		// cull back fa ce
	//glFrontFace					( GL_CW );			// GL_CCW for coun ter clock-wise

	// LOGGER( "initialize debugging..." );
    // core::debug::initialize		( nullptr );
	// core::debug::postinitialize	( );
	// LOGGER( "initialize debugging successfully" );
	//initialize_shaders          ( );
    //initialize_vertex_buffer_object ( );

	ini::ini_file system_config;
	system_config.load			( "gamedata/System.ltx" );
	cam_speed					= system_config.r_float( "Camera", "speed" );
	cam_yaw_speed				= system_config.r_float( "Camera", "yaw_speed" );

	vertices 					= system_config.r_float4x4( "Visuals", "visual_1_pos" );
	vertices_2					= system_config.r_float4x4( "Visuals", "visual_2_pos" );

	LOG_FLOAT4X3				( vertices );
	LOG_FLOAT4X3				( vertices_2 );

	initialize_model_manager	( m_model_manager );

	math::float4x4 T			= math::translate4x4( math::identity4x4( ), math::float3( -cam_pos[ 0 ], -cam_pos[ 1 ], -cam_pos[ 2 ] ) );
	math::float4x4 R			= math::rotate_yaw( math::identity4x4( ), -cam_yaw );
	math::float4x4 view_matrix	= R * T;

	// input variables
	float znear					= 0.1f;								// clipping plane
	float zfar					= 100.f;							// clipping plan e
	float fov					= math::degrees_to_radians( 67.f );
	float aspect				= 1024.f / 620.f;					// aspect ratio
	// matrix components

	float range					= tan ( fov * .5f ) * znear;
	float Sx					= ( 2.f * znear ) / ( range * aspect + range * aspect );
	float Sy					= znear / range;
	float Sz					= -( zfar + znear ) / ( zfar - znear );
	float Pz					= -( 2.f * zfar * znear ) / ( zfar - znear );

	float proj_mat[] = {
		Sx, 0.0f, 0.0f, 0.0f,
		0.0f, Sy, 0.0f, 0.0f,
		0.0f, 0.0f, Sz, -1.0f ,
		0.0f, 0.0f, Pz, 0.0f
	};

	math::float4x4 prj_mtx	= proj_mat;

    m_model_manager.get_visuals( ).at( 0 )->m_program.use( );

	view_mat_location		= m_model_manager.get_visuals( ).at( 0 )->m_program.find_unifrom( "view" );
	glUniformMatrix4fv		( view_mat_location, 1, GL_FALSE, view_matrix.elements );
	int proj_mat_location	= m_model_manager.get_visuals( ).at( 0 )->m_program.find_unifrom( "proj" );
	glUniformMatrix4fv		( proj_mat_location, 1, GL_FALSE, prj_mtx.elements );

    m_model_manager.get_visuals( ).at( 0 )->m_program.unbind( );
}

platform::~platform					( )
{

	delete m_scene;
	//m_backend.on_device_destroy	();

	//destroy_resources		( );
	//release_grid_textures	( );

	//if( m_line )
	//	m_line->Release();
}


void platform::draw_scene						(
		scene_ptr const& scene,
		scene_view_ptr const& view,
		render_output_window_ptr const& output_window,
		viewport_type const& viewport,
		std::function< void ( bool ) > const& on_draw_scene
	)
{
	float4x4 identity;
	identity.identity			( );
	system_renderer::reference().set_w( identity );
	
	if (m_renderer)
	{
		//m_renderer->render	( scene, view, output_window, viewport, on_draw_scene, false );
	}
	else
	{
		static_cast< inex::render::scene * >( scene )->flush( on_draw_scene );
		//static_cast_checked<inex::render::scene*>(scene->flush	( on_draw_scene );
	}
}

//extern D3DXMATRIXA16				view_d3d;
//extern D3DXMATRIXA16				projection_d3d;


//void platform::add_static			( resources::managed_resource_ptr const& collision, resources::managed_resource_ptr const& geometry, resources::managed_resource_ptr const& visuals )
//{
//
//}

//void	update_fps_counter ( gl_context * window )
//{
//#if INEX_PLATFORM_LINUX
//	struct 	timeval tp;
//	gettimeofday						( &tp, NULL );
//
//			long int ms 				= tp.tv_sec * 1000 + tp.tv_usec / 1000;
//	static	float	previous_seconds	= ms;
//	static	s32		frame_count;
//
//	gettimeofday						( &tp, NULL );
//					ms 					= tp.tv_sec * 1000 + tp.tv_usec / 1000;
//			float	current_seconds		= ms;
//			float	elapsed_seconds		= current_seconds - previous_seconds;
//#elif INEX_PLATFORM_WINDOWS // #if INEX_PLATFORM_LINUX
//	//static	float	previous_seconds	= glfwGetTime ();
//	//static	s32		frame_count;
//	//		float	current_seconds		= glfwGetTime ();
//	//		float	elapsed_seconds		= current_seconds - previous_seconds;
//
//#endif // #if INEX_PLATFORM_LINUX
//	//if ( elapsed_seconds > 0.25f )
//	//{
//	//	previous_seconds				= current_seconds;
//	//	float		fps					= ( float )frame_count / elapsed_seconds;
//	//	string128	tmp;
//	//	sprintf							(tmp, "opengl @ fps: %.2f", fps);
//#if INEX_PLATFORM_WINDOWS
//		//glfwSetWindowTitle				( window, tmp );
//
//#elif INEX_PLATFORM_LINUX // #if INEX_PLATFORM_WINDOWS
//		set_window_title				( window, tmp );
//		frame_count						= 0;
//#endif // #if INEX_PLATFORM_WINDOWS
//	//}
//
//	//++									frame_count;
//}


void platform::draw_frame			( )
{
	bool cam_moved 	= 0;
	//m_hw.context( )->render		( );
	//m_hw.context( )->swapBuffers( );
#if INEX_PLATFORM_LINUX
	XNextEvent					( GLX.display, &GLX.x_event );


	if( 1 ||  GLX.x_event.type == Expose )
	{
		update_fps_counter			( g_gl4_context );

		XGetWindowAttributes		( g_gl4_context->display, g_gl4_context->window, &g_gl4_context->x_window_attributes );
		glClear                 	( GL_COLOR_BUFFER_BIT );
		glClear						( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glViewport					( 0, 0, g_gl4_context->x_window_attributes.width, g_gl4_context->x_window_attributes.height );

		//triangle.prologue			( );
		//program.use( );
		//triangle.draw_static		( );
		//program.validate	( );

		//glBindVertexArray (vao);
		m_model_manager.get_visuals( ).at( 0 )->m_program.use( );
		render_visuals	( );

		glXSwapBuffers				( GLX.display, GLX.window );
	}
/*
  // XSelectInput(Pixel.GetX11Display(),Pixel.GetX11Window(),KeyPressMask|KeyReleaseMask);
    while(XPending(Pixel.GetX11Display())) { //Repeats until all events are computed
      XEvent KeyEvent;
      XNextEvent(Pixel.GetX11Display(),&KeyEvent); //Gets exactly one event
      if(KeyEvent.type==KeyPress) {
        uint32_t KeyEventCode=KeyEvent.xkey.keycode; //Gets the key code, NOT HIS CHAR EQUIVALENT
        std::cout << KeyEventCode << '\n'; //Displays the key code

        // Code handling a Keypress event

      } else if(KeyEvent.type==KeyRelease) {
         uint32_t KeyEventCode=KeyEvent.xkey.keycode;
         std::cout << KeyEventCode << '\n'; //Displays the key code

         / Code handling a KeyRelease event

      }
    }

    // General code

  }
*/
	if( GLX.x_event.type == KeyPress )
	{
		#define KEY_ESCAPE	0x09
		// rotating
		#define KEY_RIGHT 	114
		#define KEY_LEFT 	113
		#define KEY_UP		111
		#define KEY_DOWN	116

		// moving
		#define KEY_A		38
		#define KEY_D		40
		#define KEY_S		39
		#define KEY_W		25


		if ( GLX.x_event.xkey.keycode == KEY_ESCAPE )
		{
			exit 		( EXIT_SUCCESS );
		}

		if ( 	GLX.x_event.xkey.keycode == KEY_A || GLX.x_event.xkey.keycode == KEY_D ||
				GLX.x_event.xkey.keycode == KEY_W || GLX.x_event.xkey.keycode == KEY_S ||
				GLX.x_event.xkey.keycode == KEY_UP || GLX.x_event.xkey.keycode == KEY_DOWN ||
				GLX.x_event.xkey.keycode == KEY_LEFT || GLX.x_event.xkey.keycode == KEY_RIGHT )
		{
			cam_moved	= 1;
		}
	}

	// update view matrix
	if ( cam_moved )
	{
		// control keys
		if ( GLX.x_event.xkey.keycode == KEY_A )
			cam_pos[ 0 ] 		-= cam_speed ;

		if ( GLX.x_event.xkey.keycode == KEY_D )
			cam_pos[ 0 ] 		+= cam_speed ;

		if ( GLX.x_event.xkey.keycode == KEY_UP )
			cam_pos[ 1 ] 		+= cam_speed ;

		if ( GLX.x_event.xkey.keycode == KEY_DOWN )
			cam_pos[ 1 ] 		-= cam_speed ;

		if ( GLX.x_event.xkey.keycode == KEY_W )
			cam_pos[ 2 ] 		-= cam_speed ;

		if ( GLX.x_event.xkey.keycode == KEY_S )
			cam_pos[ 2 ] 		+= cam_speed ;

		if ( GLX.x_event.xkey.keycode == KEY_LEFT )
			cam_yaw 			+= cam_yaw_speed ;

		if ( GLX.x_event.xkey.keycode == KEY_RIGHT )
			cam_yaw 			-= cam_yaw_speed ;

		math::float4x4 T		= math::translate4x4( math::identity4x4 ( ), float3 (-cam_pos[0], -cam_pos[1], -cam_pos[2] ) ); // cam translation
		math::float4x4 R		= math::rotate_yaw	( math::identity4x4 ( ), -cam_yaw );
		math::float4x4 view_mat = R * T;

		glUniformMatrix4fv ( view_mat_location, 1, GL_FALSE, view_mat.elements );
	}

	m_model_manager.get_visuals( ).at( 0 )->m_program.unbind( );

	if( GLX.x_event.type == Expose )
	{
		glXSwapBuffers				( GLX.display, GLX.window );
	}

#elif INEX_PLATFORM_WINDOWS // #if INEX_PLATFORM_LINUX
	//update_fps_counter			( g_gl4_context );

    glClearColor                ( 0.6f, 0.6f, 0.8f, 1.f );
    glClear                     ( GL_COLOR_BUFFER_BIT );

	glClear						( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//triangle.prologue			( );
	//program.use( );
	//triangle.draw_static		( );
	//program.validate	( );

	//glBindVertexArray (vao);
	m_model_manager.get_visuals( ).at( 0 )->m_program.use( );
	render_visuals	( );

	//glDrawArrays ( GL_TRIANGLES, 0, 3);
	//glfwPollEvents              ( );
 //   glfwSwapBuffers             ( g_gl4_context );

	//if ( glfwWindowShouldClose ( g_gl4_context ) )
	//	exit					( 0 );

	//if (GLFW_PRESS == glfwGetKey ( g_gl4_context, GLFW_KEY_ESCAPE)) {
	//	glfwSetWindowShouldClose (g_gl4_context, 1);
	//}

	//float elapsed_seconds		= glfwGetTime( );
		// control keys

	//if (glfwGetKey (g_gl4_context, GLFW_KEY_A)) {
	//	cam_pos[0] -= cam_speed ;
	//	cam_moved = true;
	//	//LOGGER( "go left : %f\n", cam_pos[ 0 ] );
	//}

	//if (glfwGetKey (g_gl4_context, GLFW_KEY_D)) {
	//	cam_pos[0] += cam_speed ;
	//	cam_moved = true;
	//	//LOGGER( "go rigth : %f\n", cam_pos[ 0 ] );
	//}

	//if (glfwGetKey (g_gl4_context, GLFW_KEY_PAGE_UP)) {

	//	cam_pos[1] += cam_speed ;
	//	cam_moved = true; 		//LOGGER( "go up: %f\n", cam_pos[ 1 ] );
	//}

	//if (glfwGetKey (g_gl4_context, GLFW_KEY_PAGE_DOWN)) {

	//	cam_pos[1] -= cam_speed ;
	//	cam_moved = true; 		//LOGGER( "go down: %f\n", cam_pos[ 1 ] );
	//}

	//if (glfwGetKey (g_gl4_context, GLFW_KEY_W)) {

	//	cam_pos[2] -= cam_speed ;
	//	cam_moved = true; 		//LOGGER( "go forward: %f\n", cam_pos[ 2 ] );
	//}

	//if (glfwGetKey (g_gl4_context, GLFW_KEY_S)) {

	//	cam_pos[2] += cam_speed ;
	//	cam_moved = true; 		//LOGGER( "go back: %f\n", cam_pos[ 2 ] );
	//}

	//if (glfwGetKey (g_gl4_context, GLFW_KEY_LEFT)) {

	//	cam_yaw += cam_yaw_speed ;
	//	cam_moved = true; 		//LOGGER( "rotated right: %f\n", cam_yaw );
	//}

	//if (glfwGetKey (g_gl4_context, GLFW_KEY_RIGHT)) {

	//	cam_yaw -= cam_yaw_speed ;
	//	cam_moved = true; 		//LOGGER( "rotated right: %f\n", cam_yaw );
	//}

	// update view matrix
	//if (cam_moved)
	//{
	//	logging::set_output_destination( logging::logging_to_enum::terminal );
	//	LOGGER( "recalculating..." );
	//	math::float4x4 T		= math::translate4x4( math::identity4x4 ( ), float3 (-cam_pos[0], -cam_pos[1], -cam_pos[2])); // cam translation
	//	math::float4x4 R		= math::rotate_yaw	( math::identity4x4 ( ), -cam_yaw ); //
	//	math::float4x4 view_mat = R * T;

	//	//T.print( ); R.print( ); view_mat.print( );
	//	glUniformMatrix4fv (view_mat_location, 1, GL_FALSE, view_mat.elements);
	//	//cam_moved				= false;
	//	logging::set_output_destination( logging::logging_to_enum::file );
	//}

	m_model_manager.get_visuals( ).at( 0 )->m_program.unbind( );

#endif  // #if INEX_PLATFORM_LINUX

	//glfwPollEvents              ( );
    //glfwSwapBuffers             ( g_gl4_context );
	//triangle.epilogue			( );

//	float4x4 ident;
//	ident.identity			( );
//	set_world_matrix		( ident );
//
//	++m_render_frame_id;
//
//// 	game().debug().tick		( );
//// 	editor().tick			( );
//
//	m_render_device.end_frame( );
//
//	if (!m_render_device.begin_frame( ))
//		return;
//
//	m_world_matrix.identity();
//
//	float4x4 mat = math::mul4x4(m_view_matrix, m_proj_matrix);
//
//	if( identity(true) || m_render_test_scene )
//	{
//		m_scene->render	( m_view_matrix, m_proj_matrix);

//	}
//	else
//	{
//		backend::get_ref().invalidate();
//		backend::get_ref().reset_stages();
//		device().Clear( 0, 0, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER|D3DCLEAR_STENCIL, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
//	}
}

void	platform::render_visuals ( )
{
 	model_manager::Visuals const& visuals = m_model_manager.get_visuals( );

	model_manager::Visuals::const_iterator	it = visuals.begin();
	model_manager::Visuals::const_iterator	end = visuals.end();

	for( ; it != end; ++it )
		//if( !it->system_object )

	//logging::set_output_destination	( logging::logging_to_enum::terminal );
	m_model_manager.render_static	( );
	//logging::set_output_destination	( logging::logging_to_enum::file );
}

} // namespace gl4
} // namespace render
} // namespace inex

