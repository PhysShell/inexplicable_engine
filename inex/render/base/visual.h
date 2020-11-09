#ifndef INEX_RENDER_BASE_VISUAL_H_INCLUDED
#	define INEX_RENDER_BASE_VISUAL_H_INCLUDED

namespace inex {

namespace collision {
	struct geometry;
} // namespace collision

namespace render {

class visual // : public resources::unmanaged_resource
{
public:
	virtual	void				render			( )	= 0;
	virtual	void				render_selected	( ) = 0;
	virtual	collision::geometry const* get_collision_geometry	( )	= 0;

protected:
	INEX_DECLARE_PURE_VIRTUAL_DESTRUCTOR( visual )
}; // class visual

//typedef	resources::resource_ptr<
//			visual,
//			resources::unmanaged_intrusive_base
//		> visual_ptr;
typedef visual * visual_ptr;

} // namespace render
} // namespace inex

#endif // #ifndef INEX_RENDER_BASE_VISUAL_H_INCLUDED