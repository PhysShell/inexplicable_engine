#ifndef INEX_RENDER_BASE_EXTENDED_RENDERER_H_INCLUDED
#	define INEX_RENDER_BASE_EXTENDED_RENDERER_H_INCLUDED

namespace inex {
namespace render {
namespace extended {

struct NOVTABLE renderer {
	virtual	pcstr	type		( ) = 0;

protected:
	INEX_DECLARE_PURE_VIRTUAL_DESTRUCTOR( renderer )
}; // class world

} // namespace extended
} // namespace render
} // namespace inex

#endif // #ifndef INEX_RENDER_BASE_EXTENDED_RENDERER_H_INCLUDED
