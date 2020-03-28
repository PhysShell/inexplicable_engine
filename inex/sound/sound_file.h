////////////////////////////////////////////////////////////////////////////
//	Created 	: 19.10.2019
//	Author		: Feudor Shelipov
////////////////////////////////////////////////////////////////////////////

#ifndef INEX_SOUND_FILE_H_INCLUDED
#	define INEX_SOUND_FILE_H_INCLUDED

#   include <inex/macro_extensions.h>
#   include <inex/types.h>
#   include <vector>

namespace inex {
namespace sound {

struct sound_info 
{
	s32 freqency;   //sound frequency (eg. 44100 Hz)
	s32 channels;   //nunber of channels (eg. Stereo = 2)
	s32 bitrate;    //sound bitrate
	s32 bpc;        //number of bits per channel (eg. 16 for 2 channel stereo)

}; // struct sound_info

class sound_file
{
public:
    virtual void    initialize      ( )                 = 0;
    virtual void    decompress_stream ( std::vector< int > & buffer, bool looped )                 { } // = 0
    // virtual void    fill_buffers    ( )                 = 0;

protected:
    INEX_DECLARE_PURE_VIRTUAL_DESTRUCTOR( sound_file )  ;
}; // class sound_file

struct sound_buffer;

class ogg_file : public sound_file
{
public:
    virtual void    initialize      ( )                 override;

private:
    sound_buffer *  m_buffers;
}; // class ogg_file

class wav_file : public sound_file
{
}; // class wav_file

} // namespace sound
} // namespace inex

#endif // #ifndef INEX_SOUND_FILE_API_H_INCLUDED
