#ifndef FS_FILE_SYSTEM_H_INCLUDED
#	define FS_FILE_SYSTEM_H_INCLUDED


// to work with files, create find_file_it,
// which finds the file iterator through the find
// and checks if it's end()

namespace inex {
namespace core {
namespace fsmgr {
		/*
		struct	file_pred: public 	std::binary_function<file&, file&, bool>
		{
			IC bool operator()	(const file& x, const file& y) const
			{	return xr_strcmp(x.name,y.name)<0;	}
		};
        */

    fs::reader*	r_open		( pcstr path );
    void		r_close		( fs::reader*&rdr );
	//void	r_close		( virtual_file_reader*&rdr );
    //writer*	w_open		( pcstr path );
    //void	w_close		( writer*&wrt );
    void		initialize	( pcstr dir );
    void		finalize		( );

} // namespace fsmgr
} // names core
} // namespace inex
#endif // #ifndef FS_FILE_SYSTEM_H_INCLUDED
