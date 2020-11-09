////////////////////////////////////////////////////////////////////////////
//	Created 	: 16.10.2019
//	Author		: Feudor Shelipov
////////////////////////////////////////////////////////////////////////////

#ifndef INEX_SOUND_H_INCLUDED
#	define INEX_SOUND_H_INCLUDED

#	include <AL/al.h>
#	include <AL/alc.h>
#	include <inex/sound/api.h>

namespace inex {
namespace sound {

enum
{
    sm_looped       = ( 1u << 0u )
};

// to make a manager abstract class
class INEX_SOUND_API  sound_device
{
public:
    void        preinitialize       ( );
    void        initialize          ( );
    void        finalize            ( );

    void        request_free_buffer ( );

private:
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
