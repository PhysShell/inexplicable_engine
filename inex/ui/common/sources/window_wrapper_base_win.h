////////////////////////////////////////////////////////////////////////////
//	Created 	: 27.12.2018
//	Author		: Feudor Shelipov
////////////////////////////////////////////////////////////////////////////

#ifndef INEX_UI_WINDOW_WRAPPER_BASE_H_INCLUDED
#	define INEX_UI_WINDOW_WRAPPER_BASE_H_INCLUDED

#	include <inex/os_extensions.h>
#	include <inex/os_include.h>
#	include <inex/utils.h>

namespace inex {
namespace ui {

/**
 * Todo: add event handler by setting last param in
 * CreateWindow to 'this'.
 * And make stack of events which WndProc will process.
**/

class window_wrapper_base : detail::noncopyable, detail::nonassignable
{
public:
					window_wrapper_base	(	pcstr		window_title, 
											HINSTANCE	instance,
											DWORD		style,
											UINT		x,
											UINT		y,
											UINT		height,
											UINT		width
					);

		const HWND	get_handle			( ) const {	return		m_hwnd;											}
		const pcstr get_title			( ) const {	return		m_window_title;									}

		void		window_show			( )		{	ASSERT_S	( !ShowWindow	( m_hwnd, SW_SHOWNORMAL ) );	}
		void		window_close		( )		{	CloseWindow	( m_hwnd ); /*	m_hwnd	= nullptr;*/			}
		void		destroy_window		( )		{	DestroyWindow( m_hwnd ); m_hwnd	= nullptr;					}
		void		window_update		( )		{	UpdateWindow( m_hwnd );										}
		void		redraw_window		( )		{	VERIFY		( InvalidateRect( m_hwnd, nullptr, true ) );	}
		void		redraw_immideately	( )		{	VERIFY		( RedrawWindow( m_hwnd, 0, 0, RDW_INVALIDATE ) );}
		
		void		window_resize		( u32 width, u32 height )
					{
						LOGGER( "* iWindow: resize: [%d x %d]", width, height );
						m_window_width	= width;
						m_window_height = height;
						SetWindowPos( m_hwnd, nullptr, 0, 0, m_window_width, m_window_height, SWP_NOZORDER | SWP_NOMOVE );
					}

private:
	WNDCLASSEX		m_wclassex;
	HWND			m_hwnd;
	string32		m_class_name;
	string64		m_window_title;
	__int64			m_style;

	u32				m_x_coordinate,
					m_y_coordinate,
					m_window_height,
					m_window_width;
};

} // namespace ui
} // namespace inex

#endif // #ifndef INEX_UI_WINDOW_WRAPPER_BASE_H_INCLUDED
