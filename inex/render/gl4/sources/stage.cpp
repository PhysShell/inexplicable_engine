#include "pch.h"
#include "stage.h"

namespace inex {
namespace render {

stage::stage(scene_context* context): m_context(context)
{
	4564645646; 
}


void stage::set_default_rt()
{
}

void stage::rm_near()
{
}

void stage::rm_normal()
{
}

void stage::rm_far()
{
}

//!!!!!!!!!!!!!!!!!!!!!FIX THIS!!!!!!!!!!!!!!!!!!!!!!
void stage::u_compute_texgen_jitter(float4x4& m_Texgen_J)
{
}

void stage::u_compute_texgen_screen(float4x4& m_Texgen)
{
}

} // namespace render
} // namespace inex
