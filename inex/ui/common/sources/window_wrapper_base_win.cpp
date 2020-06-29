#include "pch.h"
#include "window_wrapper_base_win.h"

namespace inex {
namespace ui {

static LRESULT CALLBACK WndProc ( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
	switch ( msg )
	{
		case WM_LBUTTONUP:
		case WM_SIZE	:
		case WM_CREATE	:
		case WM_PAINT	:
		{
			break;
		}
		case WM_DESTROY	:
		{ 
			PostQuitMessage( 0 );
			return 0; 
		}
	}

	return			 DefWindowProc( hWnd, msg, wParam, lParam );
}

window_wrapper_base::window_wrapper_base (	pcstr		window_title, 
											HINSTANCE	instance,
											DWORD		style,
											UINT		x,
											UINT		y,
											UINT		height,
											UINT		width  ) :
	m_wclassex				{ 0 },
	m_x_coordinate			{ x },
	m_y_coordinate			{ y },
	m_window_width			{ width },
	m_window_height			{ height },
	m_style					{ style }

{
	m_wclassex.cbSize				= sizeof( WNDCLASSEX ); 
	m_wclassex.style				= CS_HREDRAW | CS_VREDRAW;
	m_wclassex.lpfnWndProc			= WndProc;
	m_wclassex.hInstance			= GetModuleHandle( 0 );
	m_wclassex.hbrBackground		= ( HBRUSH )GetStockObject( WHITE_BRUSH );
	m_wclassex.lpszClassName		= nullptr;
 
	ASSERT_D( RegisterClassEx(&m_wclassex), "Couldn't register window class." );

	m_hwnd							= CreateWindow (	"",
														window_title,
														style,
														x,
														y,
														width,
														height,
														nullptr,
														nullptr,
														GetModuleHandle( 0 ),
														this
													);

		VERIFY( m_hwnd ); //ASSERT_S( g_log = FindWindow( log_class, nullptr ) );
		LOGGER( "* iWindow: initial config: [%d x %d]", m_window_width, m_window_height );
}

} // namespace ui
} // namespace inex 