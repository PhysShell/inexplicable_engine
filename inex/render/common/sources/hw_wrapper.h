#ifndef HW_WRAPPER_H_INCLUDED
#	define HW_WRAPPER_H_INCLUDED

#	ifdef	USE_DX10
#		include "hw_wrapper_base_dx10.h"
#	else	//	#ifdef	USE_DX10
#		include "hw_wrapper_base_gl4.h"
#	endif	//	#ifdef	USE_DX10


//#include <inex/render/common/sources/quasi_singleton.h>
//#include <inex/render/common/sources/hw_caps.h>

//	hw_wrapper_base contains all platform specific data
//	and interface.
//	hw_wrapper defines uniform interface that has
//	platform-specific implementation.

//struct gl_context;
//void 	set_window_title ( gl_context * context, pcstr window_name );

namespace inex {
namespace render {

namespace engine {
	struct wrapper;
} // namespace engine

struct	render_options
{
	u32			smap_size;
	bool		hw_smap;
	//D3DFORMAT	hw_smap_format;

	//D3DFORMAT	null_rt_format;

	bool		fp16_filter;
	bool		fp16_blend;
};

// represents device. only creates, but not renders
class hw_wrapper :
	public hw_wrapper_base,
	public quasi_singleton<hw_wrapper>
{
public:
	hw_wrapper( inex::render::engine::wrapper& wrapper, HWND hwnd);
	~hw_wrapper();

	void	create_d3d();	//	CreateD3D
	void	destroy_d3d();	//	DestroyD3D
	void	create_device();	//	CreateDevice hwnd = m_hwnd, move_window = false
	void	create_device(HWND hwnd, bool move_window);	//	CreateDevice
	void	destroy_device();	//	DestroyDevice
	void	reset();

	pvoid	device() const	{ return hw_wrapper_base::render_device( ); }
	hw_wrapper_context *	context() const	{ return hw_wrapper_base::context( ); }

	//	Return current back-buffer width and height.
	//	Desired with and height in global options can be different!
	inline u32		get_width	() const;
	inline u32		get_height	() const;
	//inline math::uint2	get_size	() const;


	//bool	support(D3DFORMAT fmt, DWORD type, DWORD usage);
	//void	update_caps() { m_caps.update();}


	//const	hw_caps&	get_caps() const { return m_caps;}

public:
	render_options	o;
	enum class device_state
	{
		ds_ok = 0,
		ds_lost,
		ds_need_reset
	};

private:
	void		select_resolution(u32 &width, u32 &height, bool windowed) const;	//	selectResolution
//	D3DFORMAT	selectDepthStencil(D3DFORMAT);
//	u32			selectPresentInterval();
	u32			select_gpu() const;	//	selectGPU
	//u32			select_refresh(u32 width, u32 height, D3DFORMAT fmt) const;	//	selectRefresh
	void		update_window_props(HWND hw) const;	//	updateWindowProps

private:
	inex::render::engine::wrapper&	m_wrapper;
	bool		m_move_window;
	//hw_caps		m_caps;
	HWND		m_hwnd;

}; // class hw_wrapper



u32 	hw_wrapper::get_width ( ) const
{
	return 1;
}

u32 	hw_wrapper::get_height ( ) const
{
	return 1;
}

//math::uint2 hw_wrapper::get_size() const
//{
//	return math::uint2( m_dev_pparams.BackBufferWidth, m_dev_pparams.BackBufferHeight);
//}

//#include <inex/render/common/sources/hw_wrapper_inline.h>

} // namespace render
} // namespace inex


#endif // #ifndef HW_WRAPPER_H_INCLUDED
