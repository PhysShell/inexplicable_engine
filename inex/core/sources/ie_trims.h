#ifndef IE_TRIMS_H_INCLUDED
#	define IE_TRIMS_H_INCLUDED

namespace inex {

IECORE_API	void	trim_string					( pstr tgt );
IECORE_API	void	trim_string_left			( pstr& tgt );
IECORE_API	void	trim_string_right			( pstr& tgt );
IECORE_API	void	handle_comments				( pstr tgt );

} // namespace inex
#endif // #ifndef IE_TRIMS_H_INCLUDED

