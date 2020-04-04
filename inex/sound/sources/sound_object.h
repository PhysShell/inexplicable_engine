////////////////////////////////////////////////////////////////////////////
//	Created 	: 19.10.2019
//	Author		: Feudor Shelipov
////////////////////////////////////////////////////////////////////////////

#ifndef INEX_SOUND_OBJECT_H_INCLUDED
#	define INEX_SOUND_OBJECT_H_INCLUDED

#   include <AL/al.h>
#   include <inex/math_float3.h>
// #   include <AL/alc.h>
// // #include <AL/alu.h>
// #   include <AL/alut.h>

namespace inex {
namespace sound {

struct sound_info;

class sound_object
{
public:
                    sound_object        (   float const    x = .0f,
                                            float const    y = .0f,
                                            float const    z = .0f
                                        )                                           ;

    void            preload_buffers     ( s32 const buffer_id )                     ;
    void            open                ( pcstr path, bool looped = 0, bool streamed = 0 )  ;
    bool            is_streamed         ( ) const   {   return is_streamed( );  }

    void            play                ( )                                         ;
    void            pause               ( )                                         ;
    void            stop                ( )                                         ;
    void            close               ( )                                         ;
    void            update              ( )                                         ;
    void            move                ( math::float3 const& position )             ;
    void            move                (   float const&    x,
                                            float const&    y,
                                            float const&    z
                                        )                                           ;



protected:
    // INEX_DECLARE_PURE_VIRTUAL_DESTRUCTOR ( sound_object )                            ;

private:
    // put these into sound_file corresponding instance
    bool            load_ogg            ( pcstr path, bool streamed )                              ;
    void            load_wave           ( pcstr path )                              ;
    // and store it here by inclusion
    bool            read_next_chunk     ( u32 const id, u64 const size )            ;

private:
    bool            m_looped                                                        ;
    ALuint          buffers                                                         ;
    ALuint          source_ID                                                       ;
    math::float3    m_position                                                      ;
    math::float3    m_velocity                                                      ;

    // sound_file*     m_source                                                        ;
    // sound_info*     m_info                                                          ;
}; // class sound_object

} // namespace sound
} // namespace inex

#endif // #ifndef INEX_SOUND_OBJECT_H_INCLUDED
