////////////////////////////////////////////////////////////////////////////
//	Created 	: 19.10.2019
//	Author		: Feudor Shelipov
////////////////////////////////////////////////////////////////////////////

#ifndef INEX_SOUND_H_INCLUDED
#	define INEX_SOUND_H_INCLUDED

#   include <inex/macro_extensions.h>
#   include <inex/types.h>
#   include <inex/math_float3.h>
#   include <inex/sound/sound_file.h>
#   include <AL/al.h>
// #   include <AL/alc.h>
// // #include <AL/alu.h>
// #   include <AL/alut.h>
#   include <vorbis/vorbisfile.h>

namespace inex {
namespace sound {
struct sound_info;

class sound_object
{
public:
                    sound_object        ( )                                         ;

    void            preload_buffers     ( s32 const buffer_id )                     ;
    bool            open                ( pcstr path, bool looped, bool streamed )  ;
    bool            is_streamed         ( ) const   {   return m_streamed;  }

    void            play                ( )                                         ;
    void            pause               ( )                                         ;
    void            stop                ( )                                         ;
    void            close               ( )                                         ;
    void            update              ( )                                         ;
    void            move                ( math::float3 const position )             ;

    bool            m_looped                                                        ;
    math::float3    m_velocity                                                      ;
    math::float3    m_position                                                      ;

protected:
    INEX_DEFINE_PURE_VIRTUAL_DESTRUCTOR ( sound_object )                            ;

private:
    // put these into sound_file corresponding instance
    bool            load_ogg            ( pcstr path, bool streamed )                              ;
    bool            load_wave           ( pcstr path )                              ;
    // and store it here by inclusion
    bool            read_next_chunk     ( u32 const id, u64 const size )            ;

private:
    u32             m_source_id                                                     ;
    bool            m_streamed                                                      ;
    OggVorbis_File* m_source;
    vorbis_comment* m_comment;
    vorbis_info*    m_info;
    // sound_file*     m_source                                                        ;
    // sound_info*     m_info                                                          ;
}; // class sound_object

} // namespace sound
} // namespace inex

#endif // #ifndef INEX_SOUND_API_H_INCLUDED
