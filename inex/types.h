#ifndef TYPES_H_INCLUDED
#	define TYPES_H_INCLUDED

//#include <stdlib.h>
//
//#	if defined(_MSC_VER)
//		typedef	signed		__int8	s8;
//		typedef	unsigned	__int8	u8;
//
//		typedef	signed		__int16	s16;
//		typedef	unsigned	__int16	u16;
//
//		typedef	signed		__int32	s32;
//		typedef	unsigned	__int32	u32;
//
//		typedef	signed		__int64	s64;
//		typedef	unsigned	__int64	u64;
//
//#	else // #if defined(_MSC_VER)
//#		include <cstdint>
//		typedef		uint8_t			u8;
//		typedef		int8_t			s8;
//
//		typedef		uint16_t			u16;
//		typedef		int16_t				s16;
//
//		typedef		uint32_t			u32;
//		typedef		int32_t				s32;
//
//		typedef		uint64_t			u64;
//		typedef		int32_t				s64;
//#	endif // #if defined(_MSC_VER)

//typedef  int					dword;
//typedef  short				word;
//typedef  char					byte;
//typedef  long					qword;

//typedef	u8						Flags8;
//typedef	u16						Flags16;
//typedef	u32						Flags32;
//typedef	u64						Flags64;

//typedef char*					pstr;
//typedef char const*				pcstr;
//
//typedef unsigned char*			pbyte;
//typedef unsigned char const*	pcbyte;
//
//typedef void*					pvoid;
//typedef void const*				pcvoid;


typedef		uint8_t				u8;
typedef		int8_t				s8;

typedef		uint16_t			u16;
typedef		int16_t				s16;

typedef		uint32_t			u32;
typedef		int32_t				s32;

typedef		uint64_t			u64;
typedef		int32_t				s64;

typedef		char*				pstr;
typedef		char const*			pcstr;

typedef unsigned char*			pbyte;
typedef unsigned char const*	pcbyte;

typedef void*					pvoid;
typedef void const*				pcvoid;

typedef	    char				string16	[ 16 ];
typedef	    char				string32	[ 32 ];
typedef	    char				string64	[ 64 ];
typedef	    char				string128	[ 128 ];
typedef	    char				string256	[ 256 ];
typedef	    char				string512	[ 512 ];
typedef	    char				string1024	[ 1024 ];
typedef	    char		    	string2048	[ 2048 ];
typedef	    char				string4096	[ 4096 ];

#pragma message( "need to manage it one day" )
typedef	    char				string_path	[ 260 ];


#endif // #ifndef TYPES_H_INCLUDED
