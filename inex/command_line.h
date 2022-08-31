#ifndef COMMAND_LINE_H_INCLUDED
#	define COMMAND_LINE_H_INCLUDED

namespace inex {
namespace command_line {
	
class INEX_CORE_API key
{
public:
								key						(pcstr full_name, pcstr short_name, pcstr category, pcstr description, pcstr argument_description = "");

								operator bool			() { return is_set(); }

	bool						is_set					();
	bool						is_set_as_string		(pcstr * out_value);
	bool						is_set_as_number		(float * out_value);

	template <class int_type>
	bool						is_set_as_number		(int_type * out_value)
	{
		float float_value	=	0;
		if ( !is_set_as_number(& float_value) )
			return				false;
		* out_value			=	(int_type)float_value;
		return					true;
	}

	pcstr						full_name				() const { return m_full_name; }
	pcstr						short_name				() const { return m_short_name; }
	pcstr						category				() const { return m_category; }
	pcstr						description				() const { return m_description; }
	pcstr						argument_description	() const { return m_argument_description; }

	void						initialize				(pcstr value);

private:
	void						protected_construct		();
	void						initialize				();

	friend void					protected_key_construct (pvoid);

private:
	string512					m_string_value;
	float						m_number_value;
	pcstr						m_full_name;
	pcstr						m_short_name;
	pcstr						m_category;
	pcstr						m_description;
	pcstr						m_argument_description;

	enum type_enum				{ type_uninitialized, type_unset, type_void, type_number, type_string };
	type_enum					m_type;
	
public:
	command_line::key *			m_next_key;
};
	
			    void 	initialize			( pcstr const command_line );
                void    concat_command_line ( s32 , pstr*, pstr );
INEX_CORE_API   void    copy_argument		( pcstr source, pstr destination, u8 separator = '-' );
INEX_CORE_API   pstr    get_value_by_key	( pcstr k, pstr v );
INEX_CORE_API   bool    check_key           ( pcstr );

} // namespace command_line
} // namespace inex

#endif // #ifdef COMMAND_LINE_H_INCLUDED
