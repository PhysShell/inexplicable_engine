////////////////////////////////////////////////////////////////////////////
//	Created 	: 15.06.2019
//	Author		: Feudor Shelipov
////////////////////////////////////////////////////////////////////////////
#ifndef RENDER_AGENT_H_INCLUDED
#	define RENDER_AGENT_H_INCLUDED

namespace inex {
namespace render {

/*
* Class: render_agent
* Desc:
* Basically, we have one render_agent object for every scene_object type
* Then we have render_data to store the concrete instance of scene_object
* To save it there, or don't know yet
* After we proceed sorting and stuff like this, we call renderer( )
* to draw it all
***************************************************************************/
class render_agent
{
}; // class render_agent

} // namespace render
} // namespace inex

#endif // #ifndef RENDER_AGENT_H_INCLUDED
