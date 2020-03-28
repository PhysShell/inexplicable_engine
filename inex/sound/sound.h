////////////////////////////////////////////////////////////////////////////
//	Created 	: 16.10.2019
//	Author		: Feudor Shelipov
////////////////////////////////////////////////////////////////////////////

#ifndef INEX_SOUND_H_INCLUDED
#	define INEX_SOUND_H_INCLUDED

#   include <inex/macro_extensions.h>
#   include <inex/types.h>
#   include <inex/math_float3.h>
#   include <AL/al.h>
#   include <AL/alc.h>
// #include <AL/alu.h>
#   include <AL/alut.h>

namespace inex {
namespace sound {

enum
{
    sm_looped       = ( 1u << 0u )
};

class sound_device
{
public:
    void        preinitialize       ( );
    void        initialize          ( );
    void        finalize            ( );

    void        request_free_buffer ( );

    void        check_alc_errors    ( );
    void        check_al_errors     ( );

private:
    ALCcontext* m_context;
    ALCdevice*  m_device;
}; // class sound_device

extern sound_device*        g_sound_device;

} // namespace sound
} // namespace inex

#endif // #ifndef INEX_SOUND_API_H_INCLUDED
