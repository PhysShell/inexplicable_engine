#ifndef INEX_TRIMS_H_INCLUDED
#	define INEX_TRIMS_H_INCLUDED

namespace inex {

INEX_CORE_API	void	trim_string					( pstr tgt );
INEX_CORE_API	void	trim_string_left			( pstr& tgt );
INEX_CORE_API	void	trim_string_right			( pstr& tgt );
INEX_CORE_API	void	handle_comments				( pstr tgt );

} // namespace inex
#endif // #ifndef INEX_TRIMS_H_INCLUDED

