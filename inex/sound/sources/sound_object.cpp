#include "pch.h"
#include "sound_object.h"
#include <inex/fs_utils.h>
#include <AL/alc.h>
#include <AL/alut.h>


#define PRELOADED_BUFFERS_COUND             ( 1u << 1u )
#define DYNAMIC_BUFFER_SIZE                 ( 1u << 10u )

#ifdef AL_CHECK
#   error please do not define AL_CHECK
#endif // #ifndef AL_CHECK

#ifdef ALC_CHECK
#   error please do not define ALC_CHECK
#endif // #ifndef ALC_CHECK

#ifdef _DEBUG
#       define AL_CHECK( stmt )     do { stmt; check_al_errors(  ); } while ( 0 )
#       define ALC_CHECK( stmt )    do { stmt; check_alc_errors( ); } while ( 0 )
#   else // #ifdef _DEBUG
#       define AL_CHECK( stmt )     stmt
#       define ALC_CHECK( stmt )    stmt
#endif // #ifdef _DEBUG

// void    sound_device::check_alc_errors ( )
// {
//     ALenum error_code;
//     if ( ( error_code = alcGetError( m_device ) ) != ALC_NO_ERROR )
//     {
//         ASSERT_D( 0, ( pstr ) alcGetString( device, error_code ) );
//     }
// }

void    check_al_errors ( )
{
    ALenum error_code;
    if ( ( error_code = alGetError( ) ) != AL_NO_ERROR )
    {
        ASSERT_D( 0, ( pstr ) alGetString( error_code ) );
    }
}

namespace inex {
namespace sound {

sound_object::sound_object ( )
// :
//     m_info          ( nullptr ),
//     m_comment       ( nullptr ),
//     m_source        ( nullptr ),
//     m_source_id     { },
//     m_velocity      ( 0.f, 0.f, 0.f ),
//     m_position      ( 0.f, 0.f, 0.f ),
//     m_streamed      ( 0 )
{
    for (int i = 0; i < 3; ++i)
    {
        mPos[i] = mVel[i] = 1.0f;
    }
}

void    sound_object::open ( pcstr path, bool looped, bool streamed )
{
    ASSERT_D( !fs::exists( path ), "File '%s' not found", path );
    m_looped            = looped;

    alGenSources        ( 1, &source_ID );

    alSourcef           ( source_ID, AL_PITCH,		1.0f );
    alSourcef           ( source_ID, AL_GAIN,		1.0f );
    alSourcefv          ( source_ID, AL_POSITION,	mPos );
    alSourcefv          ( source_ID, AL_VELOCITY,	mVel );
    alSourcei           ( source_ID, AL_LOOPING,	m_looped );

    load_wave			( path );
}

void    sound_object::load_wave ( pcstr path )
{
    // SndInfo		buffer;
    ALenum		format;
    ALvoid		*data;
    ALsizei		size;
    ALsizei		freq;
    ALboolean	loop;
    ALuint		BufID = 0;

    alGenBuffers                ( 1, &buffers );

    AL_CHECK (  alutLoadWAVFile     (
                                        ( ALbyte * )path,
                                        &format,
                                        &data,
                                        &size,
                                        &freq,
                                        &loop
                                    );
    );

    AL_CHECK (  alBufferData                ( buffers, format, data, size, freq ) );
    AL_CHECK (  alutUnloadWAV               ( format, data, size, freq ) );
    // attach buffer 0 to source
    AL_CHECK (  alSourcei                   ( source_ID, AL_BUFFER, buffers ) );
}

bool    sound_object::load_ogg ( pcstr path, bool streamed )
{
}

bool    sound_object::read_next_chunk ( u32 const id, u64 const size )
{
}

void sound_object::play()
{
	alSourcePlay            ( source_ID );
}

void sound_object::stop()
{
	alSourceStop            ( source_ID );
}

void sound_object::close()
{
}

void sound_object::update()
{
}

void sound_object::move(    float const&    x,
                            float const&    y,
                            float const&    z )
{
	ALfloat Pos[3] = { x, y, z };
	alSourcefv( source_ID , AL_POSITION, Pos );
}

// void    sound_object::preload_buffers ( s32 const buffer_id )
// {
//     std::vector< int > decompressed_buffer;
//     this->m_source->decompress_stream   ( decompressed_buffer, this->m_looped );
//     ASSERT_S( 0 != decompressed_buffer.size( ) );
//     alBufferData                        (
//         m_source_id,
//         0,
//         &decompressed_buffer[ 0 ],
//         decompressed_buffer.size( ),
//         m_info->freqency
//     );

// }

} // namespace sound
} // namespace inex
