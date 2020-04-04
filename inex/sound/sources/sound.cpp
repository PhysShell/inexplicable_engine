#include "pch.h"
#include <inex/sound/sound.h>
#include <inex/fs_utils.h>
#include <vector>

// #pragma comment(lib, "alut.lib")
// #pragma comment(lib, "OpenAL32.lib")

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

namespace inex {
namespace sound {

void    sound_device::check_alc_errors ( )
{
    ALenum error_code;
    ASSERT_D( ( error_code = alcGetError( m_device ) ) == ALC_NO_ERROR, ( pstr ) alcGetString( m_device, error_code ) );
}

void    sound_device::check_al_errors ( )
{
    ALenum error_code;
    ASSERT_D( ( error_code = alGetError( ) ) == AL_NO_ERROR, ( pstr ) alGetString( error_code ) );
}

void    sound_device::preinitialize ( )
{
}

void    sound_device::initialize ( )
{
    float   listener_position   [ ]         = { 0.f, 0.f, 0.f },
            listener_velocity   [ ]         = { 0.f, 0.f, 0.f },
                                                 // front            // above
            listener_orientation [ ]        = { 0.f, 0.f, -1.f, 0.f, 1.f, 0.f };
    LOGGER                                  ( "Starting SOUND device..." );

    alListenerfv                            ( AL_POSITION,      listener_position );
    alListenerfv                            ( AL_VELOCITY,      listener_velocity );
    alListenerfv                            ( AL_ORIENTATION,   listener_orientation );

    m_device                                = alcOpenDevice ( 0 );
    ASSERT_D( m_device, "OpenAL: default sound device not present." );
    m_context                               = alcCreateContext ( m_device, nullptr );
    alcMakeContextCurrent                   ( m_context );
    ASSERT_D( m_device, "OpenAL: context not present." );

    LOGGER( "*** OpenAL context information ***\n"
            "\t* Default device     : %s\n"
            "\t* Device specifier   : %s\n",
            //"\t* Extensions         : %s\n",
            ( pcstr )alcGetString( m_device, ALC_DEFAULT_DEVICE_SPECIFIER ),
            ( pcstr )alcGetString( m_device, ALC_DEVICE_SPECIFIER )
            //( pcstr )alcGetString( m_device, ALC_EXTENSIONS )
    );

    LOGGER( "*** OpenAL render information ***\n"
            "\t* Renderer           : %s\n"
            "\t* Vendor             : %s\n"
            "\t* Version            : %s\n",
            //"\t* Extensions         : %s\n",
            ( pcstr )alGetString(AL_RENDERER),
            ( pcstr )alGetString(AL_VENDOR),
            ( pcstr )alGetString(AL_VERSION)
            //( pcstr )alGetString(AL_EXTENSIONS)
    );
}

void    sound_device::finalize ( )
{
    // alDeleteSources(NUM_SOURCES, source);
    // alDeleteBuffers(NUM_BUFFERS, buffers);
    // alutExit                ( );
    m_context                   = alcGetCurrentContext( );
    m_device                    = alcGetContextsDevice( m_context );
    alcMakeContextCurrent       ( 0 );
    alcDestroyContext           ( m_context );
    alcCloseDevice              ( m_device );
}

} // namespace sound
} // namespace inex
