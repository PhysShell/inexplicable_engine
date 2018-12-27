#ifndef FS_READ_WRITE_H_INCLUDED
#	define FS_READ_WRITE_H_INCLUDED

namespace inex {
namespace core {
namespace fs {

class reader_base
{

protected:
	IE_DECLARE_PURE_VIRTUAL_DESTRUCTOR( reader_base )
}; // class reader_base

class reader :
	public reader_base
{
protected:
	pstr	m_data;
	size_t	m_pos;
	size_t	m_size;
public:
							reader		        ( );
							reader		        ( pvoid _data, size_t );
			reader&			operator=			( reader const& ) = delete;
							reader				( reader const& ) = delete;
	virtual					~reader				( )
							{
								//log::Msg( "*! reader destructor called, addr: %p, sz: %d", this, sizeof( *this ) );
							}


	inline	bool			eof						( ) const 			{	return m_pos == m_size;	}
	inline	size_t			length					( ) const			{	return m_size;		}
	inline	size_t          elapsed					( ) const           {   return m_size - m_pos;    }
	inline	void            seek					( size_t p )        {   ASSERT_D( ( p < m_size ), "Wrong expression 0<=%d<%d", p, m_size ); m_pos = p; }
	inline	size_t          tell					( ) const			{   return m_pos;         }
	inline	pvoid			pointer					( ) const			{	return &m_data[ m_pos ]; }

	virtual void			r_string				( pstr dest, size_t );
	virtual void			r_stringZ				( pstr dest, size_t );
			u32				advance_term_string		( );
}; // class  reader

class virtual_file_reader :
	 public reader
{
private:
#if IE_PLATFORM_WINDOWS
	pvoid m_file_raw_pointer;
	pvoid m_mapped_file;
#elif IE_PLATFORM_LINUX // #if IE_PLATFORM_WINDOWS
	int m_file_descriptor;
#endif // #if IE_PLATFORM_WINDOWS

public:
    explicit							virtual_file_reader		( pcstr );
	virtual								~virtual_file_reader	( );

			virtual_file_reader&		operator=				( virtual_file_reader const& )  =   delete;
										virtual_file_reader     ( virtual_file_reader const& )  =   delete;
}; // class virtual_file_reader

class writer_base
{
public:
	virtual void	close			( )	= 0;
protected:
	IE_DECLARE_PURE_VIRTUAL_DESTRUCTOR( writer_base )
}; // class writer_base

class writer :
	public writer_base
{
//protected:
public:
					writer		( )	{ }
	virtual			~writer		( )
					{
						//log::Msg( "!*	Freeing writer allocated in %p and of size: %d", this, sizeof( writer ) );
					}
	virtual void	w			( pcstr src ) = 0;



	//virtual int	seek		()=0;
	//virtual int	tell		()=0;

}; // class writer

class file_writer :
	public writer
{
private:
	FILE*		m_file;
public:
		explicit					file_writer		( pcstr file_name );
		inline						~file_writer	( ) override
									{
									/*close( );*/
										//log::Msg( "!*	Freeing file_writer allocated in %p and of size: %d", this, sizeof( file_writer ) );
									}
				file_writer							( file_writer const& )  =   delete;
				file_writer&    operator=			( file_writer const& )  =   delete;
		virtual	void				w				( pcstr src ) override;
		virtual	void				close			( ) override;


//	IC  int			seek		() override { fseek() }
}; // class file_writer

} // namespace fs
} // namespace core
} // namespace inex


#endif  // #ifndef FS_READ_WRITE_H_INCLUDED
