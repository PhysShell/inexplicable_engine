#ifndef IE_TRIMS_H_INCLUDED
#	define IE_TRIMS_H_INCLUDED

namespace inex {
namespace core {
namespace str {

IECORE_API  void    copy_command_line_argunement( pcstr, pstr, u8 = '-' );
IECORE_API  pstr    get_command_line_argument	( pcstr k, pstr v );
IECORE_API	void	trim_string					( pstr tgt );
IECORE_API	void	trim_string_left			( pstr& tgt );
IECORE_API	void	trim_string_right			( pstr& tgt );
IECORE_API	void	handle_comments				( pstr tgt );

} // namespace str
} // namespace core
} // namespace inex
#endif // #ifndef IE_TRIMS_H_INCLUDED

