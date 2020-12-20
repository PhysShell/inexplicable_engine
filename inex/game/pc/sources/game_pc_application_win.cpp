#include "pch.h"
#include "game_pc_application.h"
#include <inex/math_functions.h>
#include <inex/engine/api.h>

#define ALLOCA	alloca

using game::application;

static HWND	s_splash_screen			= 0;

static char		s_finger_print[ 512 ];

static bool load_splash_screen		( HANDLE const file_handle, pbyte const buffer, u32 const buffer_size )
{
	return							false;
	//inex::threading::event			event;

	//OVERLAPPED overlapped;
	//overlapped.Offset				= 0;
	//overlapped.OffsetHigh			= 0;
	//overlapped.hEvent				= event.get_handle( );

	//BOOL const result				= ReadFile( file_handle, buffer, buffer_size, 0, &overlapped );
	//if ( !result ) {
	//	DWORD const last_error		= GetLastError( );
	//	if ( last_error != ERROR_IO_PENDING )
	//		return					false;
	//}

	//event.wait						( INFINITE );

	//DWORD bytes_done;
	//if ( !GetOverlappedResult(file_handle, &overlapped, &bytes_done, FALSE) )
	//	return						false;

	//return							true;
}

class raii_buffer // : private boost::noncopyable
{
public:
	raii_buffer( pbyte const buffer, bool dynamic_allocation ) :
		m_buffer					( buffer ),
		m_dynamic_allocation		( dynamic_allocation )
	{
	}

	~raii_buffer( )
	{
		if ( !m_dynamic_allocation )
			return;

		HeapFree					( GetProcessHeap(), 0, m_buffer );
	}

private:
	pbyte const						m_buffer;
	bool							m_dynamic_allocation;
};

static pbyte allocate				( u32 const size )
{
	//inex::memory::lock_process_heap		( );
	pbyte const result					= static_cast<pbyte>( HeapAlloc(GetProcessHeap(), 0, size) );
	//inex::memory::unlock_process_heap	( );
	return								result;
}

#if INEX_PLATFORM_WINDOWS_32
#	define RETURN_TYPE	BOOL
#elif INEX_PLATFORM_WINDOWS_32 // #ifdef XRAY_PLATFORM_WINDOWS_32
#	define RETURN_TYPE	INT_PTR
#else // #elif XRAY_PLATFORM_WINDOWS_64 // #ifdef XRAY_PLATFORM_WINDOWS_32
#	error do not use this file in non-Windows platforms
#endif // #elif XRAY_PLATFORM_WINDOWS_64 // #ifdef XRAY_PLATFORM_WINDOWS_32

static RETURN_TYPE CALLBACK window_procedure ( HWND window_handle, UINT msg, WPARAM wp, LPARAM lp)
{
	INEX_UNREFERENCED_PARAMETERS	( wp, lp, window_handle );

	switch( msg ){
		case WM_DESTROY: {
			PostQuitMessage	( 0 );
			return					( FALSE );
		}
	}

	return							( FALSE );
}

#undef RETURN_TYPE

#pragma warning(push)
#pragma warning(disable:4509)
static void splash_screen_main		( )
{

}
#pragma warning(pop)

void application::preinitialize					( )
{
	inex::engine::preinitialize		( g_command_line, "demo", __DATE__ );

	//void   decode_finger_print		(inex::fixed_string512 * );
	//decode_finger_print				( & s_finger_print );

	//if ( !inex::engine::command_line_no_splash_screen() )
	//	inex::threading::spawn		( &splash_screen_main, "splash screen", "splash", 0, 0, inex::threading::tasks_unaware );
}

void application::postinitialize				( )
{
	PostMessage						( s_splash_screen, WM_DESTROY, 0, 0 );
}