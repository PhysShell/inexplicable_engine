#include "pch.h"
#include "renderer_context.h"
#include <inex/render/common/scene_view.h>
using namespace inex::math;

namespace inex {
namespace render {

renderer_context::renderer_context	() :
	m_scene				( NULL),
	m_scene_view		( NULL),
	//m_targets			( NULL),
	m_view_pos			( 0.f, 0.f, 0.f, 1.f ),
	m_view_dir			( 0.f, 0.f, 1.f, 0.1f ),
	m_w					( math::float4x4().identity() ),
	m_w_transposed		( math::float4x4().identity() ),
	m_v					( math::float4x4().identity() ),
	m_v_transposed		( math::float4x4().identity() ),
	m_v_inverted		( math::float4x4().identity() ),
	m_v_inverted_transposed	( math::float4x4().identity() ),
	m_p					( math::float4x4().identity() ),
	m_p_transposed		( math::float4x4().identity() ),
	m_p_inverted		( math::float4x4().identity() ),
	m_wv				( math::float4x4().identity() ),
	m_wv_transposed		( math::float4x4().identity() ),
	m_vp				( math::float4x4().identity() ),
	m_vp_transposed		( math::float4x4().identity() ),
	m_wvp				( math::float4x4().identity() ),
	m_wvp_transposed	( math::float4x4().identity() ),
	m_v2shadow0			( math::float4x4().identity() ),
	m_v2shadow1			( math::float4x4().identity() ),
	m_v2shadow2			( math::float4x4().identity() ),
	m_v2shadow3			( math::float4x4().identity() ),
	//m_c_w				( NULL),
	//m_c_w_inv			( NULL),
	//m_c_v				( NULL),
	//m_c_p				( NULL),
	//m_c_wv				( NULL),
	//m_c_vp				( NULL),
	//m_c_wvp				( NULL),
	//m_c_v2w				( NULL),
	m_time_delta		( 0.0f),
	m_solid_color_specular			( 0.f, 0.f, 0.f, 0.f),
	m_solid_material_parameters		( 10.f, 1.f, 0.f, 0.f)
{

}
void	renderer_context::update_near_far()
{
	//// Near plane distance
	//float4	tmp_transformed = m_p_inverted.transform( float4( 0.f, 0.f, 0.f, 1.f));
	//m_near_far_invn_invf.x	= tmp_transformed.z/tmp_transformed.w;

	//// Far plane distance
	//tmp_transformed			= m_p_inverted.transform( float4( 0.f, 0.f, 1.f, 1.f));
	//m_near_far_invn_invf.y	= tmp_transformed.z/tmp_transformed.w;

	//// Invert Near and far distances
	//m_near_far_invn_invf.z = 1.f/m_near_far_invn_invf.x;
	//m_near_far_invn_invf.w = 1.f/m_near_far_invn_invf.y;
}

// update eye rays

// set world, projection, view matricies here

void renderer_context::set_scene( render::scene * scene)
{
	m_scene = scene;
}

void renderer_context::reset_matrices()
{
	m_w.identity();
	m_w_transposed.identity();
	m_v.identity();
	m_v_transposed.identity();
	m_v_inverted.identity();
	m_v_inverted_transposed.identity();
	m_p.identity();
	m_p_transposed.identity();
	m_p_inverted.identity();
	m_wv.identity();
	m_wv_transposed.identity();
	m_vp.identity();
	m_vp_transposed.identity();
	m_wvp.identity();
	m_wvp_transposed.identity();

	m_near_far_invn_invf	= math::float4( 0.f, 0.f, 0.f, 0.f);
}

void renderer_context::set_w(  const float4x4& m)
{
	m_w_transposed		= transpose( m_w = m );
	m_wv_transposed		= transpose( m_wv = m_w * m_v );
	m_wvp_transposed	= transpose( m_wvp = mul4x4( m_wv, m_p) );

	//backend::ref().set_vs_constant( m_c_w, m_w_transposed);
	//backend::ref().set_vs_constant( m_c_wv, m_wv_transposed);
	//backend::ref().set_vs_constant( m_c_wvp, m_wvp_transposed);

	//backend::ref().set_ps_constant( m_c_w, m_w_transposed);
	//backend::ref().set_ps_constant( m_c_wv, m_wv_transposed);
	//backend::ref().set_ps_constant( m_c_wvp, m_wvp_transposed);


	//m_bInvWValid	= false;
	//if ( c_invw)		apply_invw();
}

void renderer_context::set_v( const float4x4& m)
{
	m_v_transposed		= transpose( m_v = m );
	
	m_v_inverted.try_invert	( m );
	m_v_inverted_transposed	= transpose( m_v_inverted );

	m_wv_transposed		= transpose( m_wv = m_w * m_v );
	m_vp_transposed		= transpose( m_vp = mul4x4( m_v, m_p ) );
	m_wvp_transposed	= transpose( m_wvp = mul4x4( m_wv, m_p) );

	m_view_pos			= float4( m_v_inverted.c.xyz(), 1); 
	m_view_dir			= float4( m_v_inverted.k.xyz(), 0); 

	// ??????????????
	//backend::ref().set_ps_constant( m_c_view_pos, m_view_pos);
	//backend::ref().set_ps_constant( m_c_view_dir, m_view_dir);
	//
	//backend::ref().set_vs_constant( m_c_v, m_v_transposed);
	//backend::ref().set_vs_constant( m_c_vp, m_vp_transposed);
	//backend::ref().set_vs_constant( m_c_wv, m_wv_transposed);
	//backend::ref().set_vs_constant( m_c_wvp, m_wvp_transposed);

	//backend::ref().set_ps_constant( m_c_v, m_v_transposed);
	//backend::ref().set_ps_constant( m_c_vp, m_vp_transposed);
	//backend::ref().set_ps_constant( m_c_wv, m_wv_transposed);
	//backend::ref().set_ps_constant( m_c_wvp, m_wvp_transposed);
}

#ifndef MASTER_GOLD
void renderer_context::set_culling_v( const float4x4& m )
{
	m_culling_v					= m;
	m_culling_v_inverted		= math::invert4x3( m_culling_v );
	m_culling_vp				= mul4x4( m_culling_v, m_p );
	m_culling_view_pos			= m_culling_v_inverted.c;
	m_culling_view_dir			= m_culling_v_inverted.k;
}
#endif // #ifndef MASTER_GOLD

void renderer_context::set_p( const float4x4& m)
{
	m_p		= m;
	m_p_transposed		= transpose( m_p = m );
	m_p		= m;
	
	

	m_p_inverted		= math::invert4x4(m);

	//m_p_inverted		= utils::get_projection_invert( m );
//	m_p_inverted_transposed	= transpose( m_p_inverted );

	m_vp_transposed		= transpose( m_vp = mul4x4( m_v, m_p ) );

#ifndef MASTER_GOLD
	m_culling_vp		= mul4x4( m_culling_v, m_p );
#endif // #ifndef MASTER_GOLD

	m_wvp_transposed	= transpose( m_wvp = mul4x4( m_wv, m_p) );

	update_near_far		( );
	update_eye_rays		( );

	//backend::ref().set_vs_constant( m_c_p, m_p_transposed);
	//backend::ref().set_vs_constant( m_c_vp, m_vp_transposed);
	//backend::ref().set_vs_constant( m_c_wvp, m_wvp_transposed);

	//backend::ref().set_ps_constant( m_c_p, m_p_transposed);
	//backend::ref().set_ps_constant( m_c_vp, m_vp_transposed);
	//backend::ref().set_ps_constant( m_c_wvp, m_wvp_transposed);
}

void renderer_context::update_eye_rays()
{
	float4x4 const& inv_proj = m_p_inverted;

	float4 eye_00	( -1.f,  1.f, 1.f, 1.f);

//		float4 eye_00	( -1.f,  1.f, 1.f, 1.f);
//  	float4 eye_01	( -1.f, -1.f, 1.f, 1.f);
//  	float4 eye_10	(  1.f,  1.f, 1.f, 1.f);
//  	float4 eye_11	(  1.f, -1.f, 1.f, 1.f);

	eye_00 = inv_proj.transform( eye_00);
//  	eye_01 = inv_proj.transform( eye_01);
//  	eye_10 = inv_proj.transform( eye_10);
//  	eye_11 = inv_proj.transform( eye_11);

	float inv_w  = 1.f/eye_00.w;
	eye_00.x *= inv_w;
	eye_00.y *= inv_w;
	eye_00.z *= inv_w;
	m_eye_rays[0] = float3(  eye_00.x,  eye_00.y, eye_00.z);
	m_eye_rays[1] = float3(  eye_00.x, -eye_00.y, eye_00.z);
	m_eye_rays[2] = float3( -eye_00.x,  eye_00.y, eye_00.z);
	m_eye_rays[3] = float3( -eye_00.x, -eye_00.y, eye_00.z);

// 	m_eye_rays[0] = float3( eye_00.x*inv_w, eye_00.y*inv_w, eye_00.z*inv_w);
// 	m_eye_rays[1] = float3( eye_01.x*inv_w, eye_01.y*inv_w, eye_01.z*inv_w);
// 	m_eye_rays[2] = float3( eye_10.x*inv_w, eye_10.y*inv_w, eye_10.z*inv_w);
// 	m_eye_rays[3] = float3( eye_11.x*inv_w, eye_11.y*inv_w, eye_11.z*inv_w);
}

} // namespace render
} // namespace inex