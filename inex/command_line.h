#ifndef COMMAND_LINE_H_INCLUDED
#	define COMMAND_LINE_H_INCLUDED

namespace inex {
namespace command_line {
			    void 	initialize			( pcstr const command_line );
                void    concat_command_line ( s32 , pstr*, pstr );
INEX_CORE_API   void    copy_argument		( pcstr source, pstr destination, u8 separator = '-' );
INEX_CORE_API   pstr    get_value_by_key	( pcstr k, pstr v );
INEX_CORE_API   bool    check_key           ( pcstr );

} // namespace command_line
} // namespace inex

#endif // #ifdef COMMAND_LINE_H_INCLUDED
