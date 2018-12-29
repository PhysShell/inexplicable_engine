#ifndef COMMAND_LINE_H_INCLUDED
#	define COMMAND_LINE_H_INCLUDED

namespace inex {
namespace command_line {

			void 	initialize			( );
IECORE_API  void    copy_argument		( pcstr source, pstr destination, u8 separator = '-' );
IECORE_API  pstr    get_value_by_key	( pcstr k, pstr v );

} // namespace command_line
} // namespace inex 

#endif // #ifdef COMMAND_LINE_H_INCLUDED