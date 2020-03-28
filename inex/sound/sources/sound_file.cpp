#include "stdafx.h"
#include <inex/sound/sound_file.h>
#include <inex/sound/sound.h>
#include <inex/fs_utils.h>

#define PRELOAD_BUFFERS_COUNT   3

namespace inex {
namespace sound {

void    ogg_file::initialize ( )
{
    for (u32 i = 0; i < PRELOAD_BUFFERS_COUNT; ++i )
    {
        sound_buffer * buf = g_sound_device->request_free_buffer( );
        if ( ! buf )
        {
            LOGGER("Not enough free sound-buffers");
            continue;
        }
        
        this->m_buffers = buf;
    }
}

} // namespace sound
} // namespace inex
