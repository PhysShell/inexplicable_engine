#include "pch.h"
#include "visual.h"
#include <inex/render/gl4/sources/scene_context.h>

namespace inex {
namespace render {

render_visual::render_visual ( ) :
type				(0),
flags				(0)
//, m_collision_geom	(NULL)
{
}

render_visual::~render_visual()
{
	//if( m_collision_geom != NULL )
	//	collision::destroy(m_collision_geom);
}

void	render_visual::load ( )
{

}

} // namespace render
} // namespace inex