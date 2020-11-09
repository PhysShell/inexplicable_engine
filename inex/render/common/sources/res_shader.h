////////////////////////////////////////////////////////////////////////////
//	Created 	: 08.11.2020
//	Author		: Feudor Shelipov
////////////////////////////////////////////////////////////////////////////

#ifndef RES_SHADER_H_INCLUDED
#	define RES_SHADER_H_INCLUDED

#	include <inex/extensions.h>

namespace inex {
namespace render {

class res_geometry
{
public:
	res_geometry( u32 vb, u32 ibm , u32 stride)//:
		//m_vb(vb), m_ib(ib), m_dcl(dcl), m_vb_stride(stride)
	{}
	
	~res_geometry();
	
	bool equal(const res_geometry& other) const;
	
	void apply();
	
	u32	get_stride() {return m_vb_stride;}

private:
	//ID3DVertexBuffer*	m_vb;			//vb;
	//ID3DIndexBuffer*	m_ib;			//ib;
	//ref_declaration		m_dcl;			//dcl;
	u32					m_vb_stride;	//vb_stride;
}; // class res_geometry

typedef res_geometry ref_geometry;

} // namsepace render
} // namsepace inex

#endif 
