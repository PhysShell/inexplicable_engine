////////////////////////////////////////////////////////////////////////////
//	Created 	: 15.06.2019
//	Author		: Feudor Shelipov
////////////////////////////////////////////////////////////////////////////
#ifndef STATIC_MESH_H_INCLUDED
#	define STATIC_MESH_H_INCLUDED

#   include <inex/render/common/sources/scene_object.h>
#   include <inex/render/common/sources/render_agent.h>

namespace inex {
namespace render {

class static_mesh : public scene_object
{
public:
    // needed to have an Update method before rendering
    void            render          ( )
                    {
                        static_mesh_render->render_static_mesh( this );   
                    }
private:
    static_mesh_render*             m_static_mesh_render;
}; // class static_mesh

// class skeleton_mesh;
// class static_mesh_ogl;

class static_mesh_render
{
public:
    void            render_static_mesh  ( static_mesh* mesh )
                    {
                        // here, we recieve data from data holder aka mesh
                        // proceeding textures, shaders
                    }

    void            renderer            ( )
                    {
                        // render the data saved by batch
                    }
private:
    // this is to  save data-holder data or smt like that
    // render_data     m_data_holder;
}; // class static_mesh_render

} // namespace render
} // namespace inex

#endif // #ifndef STATIC_MESH_H_INCLUDED
