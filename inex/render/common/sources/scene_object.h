////////////////////////////////////////////////////////////////////////////
//	Created 	: 15.06.2019
//	Author		: Feudor Shelipov
////////////////////////////////////////////////////////////////////////////
#ifndef SCENE_OBJECT_H_INCLUDED
#	define SCENE_OBJECT_H_INCLUDED

namespace inex {
namespace render {

/*
* It's not cool to have an object rendering itself. - Wise people;
******************************************************************/

class scene_object
{
public:
    virtual void    render          ( ) = 0;
    // virtual void    render_shadow   ( ) = 0;
}; // class scene_object

} // namespace render
} // namespace inex

#endif // #ifndef SCENE_OBJECT_H_INCLUDED
