#ifndef TYPES_H_INCLUDED
#	define TYPES_H_INCLUDED

#	ifdef USE_COMPILER_FIXED_SIZE_TYPES
typedef		signed		__int8	s8;
typedef		unsigned	__int8	u8;

typedef		signed		__int16	s16;
typedef		unsigned	__int16	u16;

typedef		signed		__int32	s32;
typedef		unsigned	__int32	u32;

typedef		signed		__int64	s64;
typedef		unsigned	__int64	u64;
#	else // #ifdef USE_COMPILER_FIXED_SIZE_TYPES
typedef		std::uint8_t		u8;
typedef		std::int8_t			s8;

typedef		std::uint16_t		u16;
typedef		std::int16_t		s16;

typedef		std::uint32_t		u32;
typedef		std::int32_t		s32;

typedef		std::uint64_t		u64;
typedef		std::int32_t		s64;
#endif // #ifdef USE_COMPILER_FIXED_SIZE_TYPES

typedef		u8					flags8;
typedef		u16					flags16;
typedef		u32					flags32;
typedef		u64					flags64;

typedef		char*				pstr;
typedef		char const*			pcstr;
typedef		unsigned char*		pbyte;
typedef		unsigned char const* pcbyte;

typedef		void*				pvoid;
typedef		void const*			pcvoid;

typedef	    char				string16	[ 16 ];
typedef	    char				string32	[ 32 ];
typedef	    char				string64	[ 64 ];
typedef	    char				string128	[ 128 ];
typedef	    char				string256	[ 256 ];
typedef	    char				string512	[ 512 ];
typedef	    char				string1024	[ 1024 ];
typedef	    char		    	string2048	[ 2048 ];
typedef	    char				string4096	[ 4096 ];
typedef	    char				string_path	[ INEX_MAX_PATH ];


#endif // #ifndef TYPES_H_INCLUDED
