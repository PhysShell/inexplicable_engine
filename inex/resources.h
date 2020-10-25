////////////////////////////////////////////////////////////////////////////
//	Created		: 25.10.2020
//	Author		: Feudor Shelipov
////////////////////////////////////////////////////////////////////////////

#ifndef RESOURCES_H_INCLUDED
#   define RESOURCES_H_INCLUDED

#   include <inex/extensions.h>

namespace inex {

// from file, memory, network (:D)
class stream;

namespace resources {

enum class class_id_enum
{
    unknown_data_class,
    raw_data_class,
    texture_class,
    config_class,
    sound_class,
}; // enum class class_id_enum

class resource_base // inherits from intrusive_ptr?
{
public:
                    resource_base   ( pcstr name, u64 priority );
    virtual         ~resource_base  ( ) = 0;

    virtual bool    reload          ( ) = 0;
    virtual void    unload          ( ) = 0;
    virtual void    destroy         ( ) = 0;

            pcstr   get_name        ( )                             {   return m_name;      }
            u64     get_handle      ( )                             {   return m_handle;  }
            void    set_handle      ( u64 const handle  )           {   m_handle = handle;  }
            pcstr   get_source      ( )                             {   return "original data somehow"; }
            u64     get_time        ( )                             {   return m_time; }
            u64     get_priority    ( )                             {   return m_priority;  }
            u64     get_size        ( ) const                       {   return m_size;  }

            void    set_logging_flag( u8 flag )                     {   m_logging_flags |= flag;    }

            u32     get_reference_count ( ) const                   {   return m_user_count;    }
            void    intrusive_increment ( ); void intrusive_decrement ( );

            u8      has_users       ( )                             {   return m_user_count > 0;    }

protected:
            // static member log and static funcs to set it
            u64     m_priority;
            u64     m_time;
            u64     m_size;
            u8      m_logging_flags;

            u64     m_handle;
            u32     m_user_count;
            pcstr   m_name;
            pcstr   m_file_path;





}; // class resource_base

class resource_manager_base
{
public:
    INEX_DECLARE_PURE_VIRTUAL_DESTRUCTOR    ( resource_manager_base );

    virtual resource_base*  create          ( pcstr name, u8 traverse_for_identical_first = 0 )  = 0;
            resource_base*  create_unknown  ( class_id_enum id, u8 type ); // load unkown resource of 'type'
            resource_base*  get_by_name     ( pcstr name );
            resource_base*  get_by_handle   ( u64 handle );
            void            search_for_unused   ( ); // in separate thread

    // ...manage shared resources...

    // map or 2D array of every type of resource...



private:


}; // class resource_manager_base

template < class StreamedData >
class resource_allocator
{
public:
    virtual pvoid   load    ( pcstr file_name ) = 0;
    virtual void    unload  ( pcstr file_name )  = 0;
}; // resource_allocator


class scene_manager
{
    // stores objects and manages when to load\unload resources
}; // class scene_manager

class object
{
    resource_base*  something;
}; // class object

} // namespace resources
} // namespace inex

#endif // #ifndef RESOURCES_H_INCLUDED