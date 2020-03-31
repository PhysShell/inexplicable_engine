#include "stdafx.h"
#include <inex/sound/sound_object.h>
#include <inex/fs_utils.h>
#include <map>
#include <fstream>
#include <iostream>
#include <AL/alc.h>
#include <AL/alut.h>

using std::istream;

#define PRELOADED_BUFFERS_COUND             ( 1u << 1u )
#define DYNAMIC_BUFFER_SIZE                 ( 1u << 10u )  

pcstr    extract_extenstion ( pcstr target )
{
    pcstr end          = target + strlen( target );
    while ( end != target )
    {
        if ( *end-- == '.' )
        {
            return end;
        }
    }

    return              "";
}

namespace inex {
namespace sound {
ALboolean CheckALCError()
{
	ALenum ErrCode;
	std::string Err = "ALC error: ";
	if ((ErrCode = alcGetError(pDevice)) != ALC_NO_ERROR)
	{
		Err += (char *)alcGetString(pDevice, ErrCode);
		LOGGER(Err.data());
		return AL_FALSE;
	}
	return AL_TRUE;
}

ALboolean CheckALError()
{
	ALenum ErrCode;
	std::string Err = "OpenAL error: ";
	if ((ErrCode = alGetError()) != AL_NO_ERROR)
	{
		Err += (char *)alGetString(ErrCode);
		LOGGER(Err.data());
		return AL_FALSE;
	}
	return AL_TRUE;
}

bool InitializeOpenAL()
{

	// Position of the Listener.
	ALfloat ListenerPos[] = { 0.0, 0.0, 0.0 };

	// Velocity of the Listener.
	ALfloat ListenerVel[] = { 0.0, 0.0, 0.0 };

	// Orientation of the Listener. (first 3 elements are "at", second 3 are "up")
	// Also note that these should be units of '1'.
	ALfloat ListenerOri[] = { 0.0, 0.0, -1.0,  0.0, 1.0, 0.0 };

	// Open default sound device
	pDevice = alcOpenDevice(NULL);
	// Check for errors
	if (!pDevice)
	{
		LOGGER("Default sound device not present");
		return false;
	}
	// Creating rendering context
	pContext = alcCreateContext(pDevice, NULL);
	if (!CheckALCError()) return false;

	alcMakeContextCurrent(pContext);

	// Set listener properties
    alListenerfv(AL_POSITION,    ListenerPos);
    alListenerfv(AL_VELOCITY,    ListenerVel);
    alListenerfv(AL_ORIENTATION, ListenerOri);
	return true;
}

void DestroyOpenAL()
{
	// Clear all buffers and sources
	for (TBuf::iterator i = Buffers.begin(); i != Buffers.end(); i++)
		alDeleteBuffers(1, &i->second.ID);
	// Shut down context
	alcMakeContextCurrent(NULL);
	// Destroy context
	alcDestroyContext(pContext);
	// Close sound device
	alcCloseDevice(pDevice);
}
// Typedefs
typedef struct 
{
	unsigned int	ID;
    std::string     Filename;
	unsigned int	Rate;
	unsigned int	Format;
} SndInfo;

typedef std::map<ALuint, SndInfo> TBuf;

// Vars
TBuf		Buffers;
ALCdevice	*pDevice;
ALCcontext	*pContext;


size_t ReadOgg(void *ptr, size_t size, size_t nmemb, void *datasource)
{
	istream *File = reinterpret_cast<istream*>(datasource);
	File->read((char *)ptr, size * nmemb);
	return File->gcount();
}

int SeekOgg(void *datasource, ogg_int64_t offset, int whence)
{
	istream *File = reinterpret_cast<istream*>(datasource);
	std::ios_base::seekdir Dir;
	File->clear();
	switch (whence) 
	{
		case SEEK_SET: Dir = std::ios::beg;  break;
		case SEEK_CUR: Dir = std::ios::cur;  break;
		case SEEK_END: Dir = std::ios::end;  break;
		default: return -1;
	}
	File->seekg((std::streamoff)offset, Dir);
	return (File->fail() ? -1 : 0);
}

long TellOgg(void *datasource)
{
	istream *File = reinterpret_cast<istream*>(datasource);
	return File->tellg();
}

int CloseOgg(void *datasource)
{
	return 0;
}

sound_object::sound_object ( ) :
    m_info          ( nullptr ),
    m_comment       ( nullptr ),
    m_source        ( nullptr ),
    m_source_id     { },
    m_velocity      ( 0.f, 0.f, 0.f ),
    m_position      ( 0.f, 0.f, 0.f ),
    m_streamed      ( 0 )
{
}

bool    sound_object::open ( pcstr path, bool looped, bool streamed )
{
    ASSERT_D( fs::exists( path ), "File '%s' not found", path );
    m_looped            = looped;
    float a[ 3 ];
    alGenSources        ( 1, &m_source_id );
    // check_al_errors     ( );
    alSourcef           ( m_source_id, AL_PITCH,    1.f );
    alSourcef           ( m_source_id, AL_GAIN,     1.f );
    alSourcefv          ( m_source_id, AL_POSITION, a );
    alSourcefv          ( m_source_id, AL_VELOCITY, a );
    alSourcei           ( m_source_id, AL_LOOPING, m_looped );

    string16            extension;
    strcpy              ( extension, extract_extenstion( path ) );

    if ( !strcmp( extension, "wav" ) )
    {
        return          load_wave( path );
    }
    else if ( !(strcmp( extension, "ogg" ) ) )
    {
        return          load_ogg( path, streamed );
    }

    return              0;
}

bool sound_object::is_streamed( ) const
{
	return m_streamed;

}

bool    sound_object::load_wave ( pcstr path )
{
    SndInfo		buffer;
	ALenum		format;
	ALvoid		*data;
	ALsizei		size;
	ALsizei		freq;
	ALboolean	loop;
	ALuint		BufID = 0;

	// Fill buffer struct
	buffer.Filename = path;
	// Check for existance of sound
	for (TBuf::iterator i = Buffers.begin(); i != Buffers.end(); i++)
	{
		if (i->second.Filename == path) BufID = i->first;
	}

	// If Such buffer not exist yet
	if (!BufID)
	{
		// Generate buffers
		alGenBuffers(1, &buffer.ID);
		if (!CheckALError()) return;
		// Load wav data
		alutLoadWAVFile((ALbyte *)path, &format, &data, &size, &freq, &loop);
		if (!CheckALError()) return;
	
		buffer.Format			= format;
		buffer.Rate				= freq;
		// Fill buffer
		alBufferData(buffer.ID, format, data, size, freq);
		if (!CheckALError()) return; // assert( 0 )
		// Unload wav
		alutUnloadWAV(format, data, size, freq);
		if (!CheckALError()) return; // assert( 0 )

		Buffers[buffer.ID] = buffer;
	}
	else 
		buffer = Buffers[BufID];

	alSourcei ( m_source_id, AL_BUFFER,	buffer.ID);

	// Place buffer to Buffers map
	return; // remove
}

bool    sound_object::load_ogg ( pcstr path, bool streamed )
{
	int				i, DynBuffs = 1, BlockSize;
	// OAL specific
	SndInfo			buffer;
	ALuint			BufID = 0;
	// OggVorbis specific structures
	ov_callbacks	cb;

	// Fill cb struct
	cb.close_func	= CloseOgg;
	cb.read_func	= ReadOgg;
	cb.seek_func	= SeekOgg;
	cb.tell_func	= TellOgg;

	// Create OggVorbis_File struct
	m_source = new OggVorbis_File;

	// Open Ogg file
	// reder::reader OggFile.open(Filename.c_str(), ios_base::in | ios_base::binary);

	// Generate local buffers
	// if (ov_open_callbacks(&OggFile, m_source, NULL, -1, cb) < 0)
	// {
	// 	// This is not ogg bitstream. Return
	// 	return false;
	// }

	// Check for existance of sound
	if (!m_streamed)
	{
		for (TBuf::iterator i = Buffers.begin(); i != Buffers.end(); i++)
		{
			if (i->second.Filename == path) BufID = i->first;
		}
		BlockSize = ov_pcm_total(m_source, -1) * 4;
	}
	else
	{
		BlockSize	=  1 << 10 ;
		DynBuffs	= PRELOADED_BUFFERS_COUND;
		alSourcei(m_source_id, AL_LOOPING, AL_FALSE);
	}
	
	// Return vorbis_comment and vorbis_info structures
	m_comment		= ov_comment( m_source, -1);
	m_info			= ov_info(m_source, -1);

	// Fill buffer infos
	buffer.Rate		= m_info->rate;
	buffer.Filename	= path;
	buffer.Format = (m_info->channels == 1) ? AL_FORMAT_MONO16 : AL_FORMAT_STEREO16;

	// Fill buffers with data each block by DYNBUF_SIZE bytes
	if (m_streamed || !BufID)
	{
		for (i = 0; i < DynBuffs; i++)
		{
			// Create buffers
			alGenBuffers(1, &buffer.ID);
			if (!CheckALError()) return ; // assert( 0 )
			Buffers[buffer.ID] = buffer;
			// Read amount (DYNBUF_SIZE) data into each buffer
			read_next_chunk(buffer.ID, BlockSize);
			if (!CheckALError()) return;// assert( 0 )

			if (m_streamed) // Place buffer to queue
			{
				alSourceQueueBuffers(m_source_id, 1, &buffer.ID);
				if (!CheckALError()) return; // assert( 0 )
			}
			else 
				alSourcei(m_source_id, AL_BUFFER, buffer.ID);
		}
	}
	else
	{
		alSourcei(m_source_id, AL_BUFFER, Buffers[BufID].ID);
	}

	return ; // remove
}

bool    sound_object::read_next_chunk ( u32 const id, u64 const size )
{
	// vars
	char		eof = 0;
	int			current_section;
	long		TotalRet = 0, ret;
	char		*PCM;

	if (size < 1) return false;
	PCM = new char[size];

	// Read loop
	while (TotalRet < size) 
	{
		ret = ov_read(m_source, PCM + TotalRet, size - TotalRet, 0, 2, 1, &current_section);

		// if end of file or read limit exceeded
		if (ret == 0) break;
		else if (ret < 0) 		// Error in bitstream
		{
			//
		}
		else
		{
			TotalRet += ret;
		}
	}
	if (TotalRet > 0)
	{
		alBufferData(m_source_id, Buffers[m_source_id].Format, (void *)PCM, 
					 TotalRet, Buffers[m_source_id].Rate);
		CheckALError();
	}
	delete [] PCM;
	return (ret > 0);
}


void sound_object::play()
{
	alSourcePlay(m_source_id);
}

void sound_object::close()
{
	alSourceStop(m_source_id);
	if (alIsSource(m_source_id)) alDeleteSources(1, &m_source_id);
	if (!m_source)
	{	
		ov_clear(m_source);
		delete m_source;
	}
}

void sound_object::update()
{
	if (!m_streamed) return;
	
	int				Processed = 0;
	ALuint			BufID;

	alGetSourcei(m_source_id, AL_BUFFERS_PROCESSED, &Processed);

	// We still have processed buffers
	while (Processed--)
	{
		alSourceUnqueueBuffers(m_source_id, 1, &BufID);
		if (!CheckALError()) return;
		if (read_next_chunk(BufID, DYNAMIC_BUFFER_SIZE) != 0)
		{
			alSourceQueueBuffers(m_source_id, 1, &BufID);
			if (!CheckALError()) return;
		}
		else
		{
			ov_pcm_seek(m_source, 0);
			alSourceQueueBuffers(m_source_id, 1, &BufID);
			if (!CheckALError()) return;

			if (!m_looped) stop();
		}
	}
}

void sound_object::stop()
{
	alSourceStop(m_source_id);
}

void sound_object::move(    float const&    x,
                            float const&    y,
                            float const&    z )   
{
	ALfloat Pos[3] = { x, y, z };
	alSourcefv(m_source_id, AL_POSITION, Pos);
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
