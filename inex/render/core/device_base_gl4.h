////////////////////////////////////////////////////////////////////////////
//	Created 	: 03.12.2021
//	Author		: Feudor Shelipov
////////////////////////////////////////////////////////////////////////////
#ifndef RENDER_DEVICE_BASE_GL4_H_INCLUDED
#	define RENDER_DEVICE_BASE_GL4_H_INCLUDED


namespace inex      {
namespace render    {
	
class device_base
{
	
private:

}; // device_base


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

#endif // #ifndef RENDER_DEVICE_BASE_GL4_H_INCLUDED