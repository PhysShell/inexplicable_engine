#include "stdafx.h"
#include <inex/sound/sound.h>
#include <inex/fs_utils.h>
#include <vector>
#include <vorbis/codec.h>

// #pragma comment(lib, "alut.lib")
// #pragma comment(lib, "OpenAL32.lib")

#ifndef AL_CHECK
#   ifdef _DEBUG
#       define AL_CHECK( stmt ) do { \
            stmt; \
            check_al_errors( #stmt, __FILE__, __LINE__ ); \
        } while ( 0 )
#   else // #ifdef _DEBUG
#       define AL_CHECK( stmt ) stmt
#   endif // #ifdef _DEBUG
#endif // #ifndef AL_CHECK

namespace inex {
namespace sound {

void    sound_device::preinitialize ( )
{
    float   listener_position   [ ]         = { 0.f, 0.f, 0.f },
            listener_velocity   [ ]         = { 0.f, 0.f, 0.f },
                                                 // front            // above
            listener_orientation [ ]        = { 0.f, 0.f, -1.f, 0.f, 1.f, 0.f };
    m_device                                = alcOpenDevice ( nullptr );
    ASSERT_D( m_device, "OpenAL: default sound device not present." );
    m_context                               = alcCreateContext ( m_device, nullptr );
    ASSERT_S( m_context );
    alcMakeContextCurrent                   ( m_context );
    alListenerfv                            ( AL_POSITION,      listener_position );
    alListenerfv                            ( AL_VELOCITY,      listener_velocity );
    alListenerfv                            ( AL_ORIENTATION,   listener_orientation );
}

void    sound_device::initialize ( )
{
    for (int i = 0; i < 512; i++)
{
	SoundBuffer buffer;
	AL_CHECK( alGenBuffers((ALuint)1, &buffer.refID) );
	this->buffers.push_back(buffer);
}

for (int i = 0; i < 16; i++)
{
	SoundSource source;
	AL_CHECK( alGenSources((ALuint)1, &source.refID)) ;
	this->sources.push_back(source);
}

for (uint32 i = 0; i < this->buffers.size(); i++)
{
	this->freeBuffers.push_back(&this->buffers);
}

for (uint32 i = 0; i < this->sources.size(); i++)
{
	this->freeSources.push_back(&this->sources);
}
}

void    sound_device::finalize ( )
{
    // alDeleteSources(NUM_SOURCES, source);
    // alDeleteBuffers(NUM_BUFFERS, buffers);
    // alutExit                ( );
    alcMakeContextCurrent   ( nullptr );
    alcDestroyContext       ( m_context );
    alcCloseDevice          ( m_device);
}

void    sound_device::check_alc_errors ( )
{
    ALenum error_code;
    if ( ( error_code = alcGetError( m_device ) ) != ALC_NO_ERROR )
    {
        ASSERT_D( 0, ( pstr ) alcGetString( device, error_code ) );
    }
}

void    sound_device::check_al_errors ( )
{
    ALenum error_code;
    if ( ( error_code = alGetError( ) ) != AL_NO_ERROR )
    {
        ASSERT_D( 0, ( pstr ) alGetString( device, error_code ) );
    }
}

bool    sound_object::open ( pcstr path, bool looped, bool streamed )
{
    ASSERT_D( fs::exists( path ), "File '%s' not found", path );
    m_looped            = looped;
    float a[ 3 ];
    alGenSources        ( 1, &m_source_id );
    check_al_errors     ( );
    alSourcef           ( m_source_id, AL_PITCH, 1.f );
    alSourcef           ( m_source_id, AL_GAIN, 1.f );
    alSource3f          ( m_source_id, AL_POSITION, *a, *a, *a );
    ;
}

} // namespace sound
} // namespace inex
