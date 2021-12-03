////////////////////////////////////////////////////////////////////////////
//	Created 	: 15.06.2019
//	Author		: Feudor Shelipov
////////////////////////////////////////////////////////////////////////////
#ifndef RENDER_DEVICE_H_INCLUDED
#	define RENDER_DEVICE_H_INCLUDED


namespace inex      {
namespace render    {
#	if INEX_PLATFORM_WINDOWS

class device_base
{
	
private:

}; // device_base

#	elif INEX_PLATFORM_LINUX // #if INEX_PLATFORM_WINDOWS
class device_base
{
private:

}; // device_base

# 	endif // #if INEX_PLATFORM_WINDOWS

class INEX_RENDER_API device : public quasi_singleton< device >
{
public:
							device 			( )								;
							~device 		( )								;
public:
        void                initialize      ( )                         	;
inline  					base_device 	( ) { return  m_device_base; }	;

private:
	enum device_state_enum
	{
		ds_ok = 0,
		ds_lost,
		ds_need_reset
	};
	
private:
	device_base * 			m_device_base;
	device_context * 		m_device_context;

}; // class device

} // namespace render
} // namespace inex 

#endif // #ifndef RENDER_DEVICE_H_INCLUDED