////////////////////////////////////////////////////////////////////////////
//	Created 	: 03.12.2021
//	Author		: Feudor Shelipov
////////////////////////////////////////////////////////////////////////////

#ifndef INEX_DEBUG_MACROS_H_INCLUDED
#	define INEX_DEBUG_MACROS_H_INCLUDED

#	if defined ( ASSERT_S ) || defined ( ASSERT_D )
#		error please do not define R_ASSERT, R_ASSERT_T macros
#	endif // #if defined ( ASSERT_S ) || defined ( ASSERT_D )

#if defined ( FATAL ) || defined ( UNREACHABLE_CODE ) || defined ( NODEFAULT ) || defined ( NOT_IMPLEMENTED ) || defined ( CHECK_AND_CORRECT ) || defined ( CHECK_OR_EXIT )
#	error please do not define FATAL, UNREACHABLE_CODE, NODEFAULT, NOT_IMPLEMENTED, CHECK_AND_CONTINUE and CHECK_OR_EXIT macros
#endif // #if defined (FATAL) || defined (UNREACHABLE_CODE) || defined (NODEFAULT) || defined (NOT_IMPLEMENTED) || defined (CHECK_AND_CORRECT) || defined (CHECK_OR_EXIT)

#define INEX_EMPTY_EXPRESSION												if ( ::inex::identity(false) ) { } else (void)0
#define INEX_EMPTY_EXPRESSION_VA_ARGS( ... )								INEX_EMPTY_EXPRESSION
#define INEX_EMPTY_EXPRESSION_U_VA_ARGS( assertion_type, expression, ... )	if ( ::inex::identity(false) ) { ::inex::debug::detail::expression_eater(assertion_type, expression, ##__VA_ARGS__); } else (void)0

////////////////////////////////////////////////////////////////////////////
// R_ASSERT* macros
////////////////////////////////////////////////////////////////////////////
#ifdef MASTER_GOLD
#	define FATAL( format, ... )												INEX_EMPTY_EXPRESSION

#	define R_ASSERT_T														INEX_EMPTY_EXPRESSION_VA_ARGS
#	define R_ASSERT_CMP_T( value1, operation, value2, assert_type, ... )	INEX_EMPTY_EXPRESSION

#	define R_ASSERT_T_U														INEX_EMPTY_EXPRESSION_U_VA_ARGS
#	define R_ASSERT_CMP_T_U( value1, operation, value2, assert_type, ... )	if ( ::inex::identity(false) ) { ::inex::debug::detail::expression_eater(value1, value2, assert_type, ##__VA_ARGS__); } else (void)0

#	define R_ASSERT_BOX														INEX_EMPTY_EXPRESSION_VA_ARGS

#else // #ifdef MASTER_GOLD
#	define FATAL( format, ... )												\
		if ( ::inex::identity(true) ) {										\
			static bool debug_macro_helper_ignore_always = false;			\
			if ( !debug_macro_helper_ignore_always ) {						\
				INEX_ASSERT_HELPER(											\
					debug_macro_helper_ignore_always,						\
					::inex::process_error_true,								\
					"fatal error",											\
					::inex::assert_untyped,									\
					format,													\
					##__VA_ARGS__											\
				)															\
			}																\
		}																	\
		else (void)0

#	define R_ASSERT_T( assert_type, expression, ... )						\
		if ( ::inex::identity(true) ) {										\
			static bool debug_macro_helper_ignore_always = false;			\
			if ( !debug_macro_helper_ignore_always && !::inex::identity(expression) ) {	\
				INEX_ASSERT_HELPER(											\
					debug_macro_helper_ignore_always,						\
					::inex::process_error_true,								\
					INEX_MAKE_STRING(expression),							\
					assert_type,											\
					##__VA_ARGS__											\
				)															\
			}																\
			INEX_ANALYSIS_ASSUME( !!(expression) );							\
		} else INEX_ANALYSIS_ASSUME( !!(expression) )

#	define R_ASSERT_CMP_T( value1, operation, value2, assert_type, ... )	\
		if ( ::inex::identity(true) ) {										\
			static bool debug_macro_helper_ignore_always = false;			\
			if ( !debug_macro_helper_ignore_always ) {						\
				bool debug_macro_helper_comparison_result;					\
				::inex::debug::detail::string_helper fail_message;			\
				::inex::debug::detail::make_fail_message(					\
					& fail_message,											\
					debug_macro_helper_comparison_result,					\
					::inex::debug::detail::make_tuple( value1, value2 )		\
					operation												\
					::inex::debug::detail::compare_helper()					\
				);															\
				if ( !debug_macro_helper_comparison_result )	{			\
					fail_message.appendf	(__VA_ARGS__);					\
					INEX_ASSERT_HELPER(										\
						debug_macro_helper_ignore_always,					\
						::inex::process_error_true,							\
						INEX_MAKE_STRING(value1)							\
						" "													\
						INEX_MAKE_STRING(operation)							\
						" "													\
						INEX_MAKE_STRING(value2),							\
						assert_type,										\
						"%s",												\
						fail_message.c_str( )								\
					);														\
				}															\
			}																\
			INEX_ANALYSIS_ASSUME( ((value1) operation (value2)) );			\
		}																	\
		else																\
			INEX_ANALYSIS_ASSUME( ((value1) operation (value2)) )

#	define R_ASSERT_T_U			R_ASSERT_T
#	define R_ASSERT_CMP_T_U		R_ASSERT_CMP_T

#	define R_ASSERT_BOX( expression, ... )									\
		if ( ::inex::identity(true) ) {										\
			static bool debug_macro_helper_ignore_always = false;			\
			if ( !debug_macro_helper_ignore_always && !::inex::identity(expression) ) {		\
				INEX_ASSERT_HELPER(											\
					debug_macro_helper_ignore_always,						\
					::inex::process_error_to_message_box,					\
					INEX_MAKE_STRING(expression),							\
					::inex::assert_untyped,									\
					##__VA_ARGS__											\
				)															\
			}																\
			INEX_ANALYSIS_ASSUME( !!(expression) );							\
		} else INEX_ANALYSIS_ASSUME( !!(expression) )

#endif // #ifdef MASTER_GOLD

#define R_ASSERT( expression, ... )											R_ASSERT_T( ::inex::assert_untyped, expression, ##__VA_ARGS__ )
#define R_ASSERT_CMP( value1, operation, value2, ... )						R_ASSERT_CMP_T( value1, operation, value2, ::inex::assert_untyped, ##__VA_ARGS__ )

#define R_ASSERT_U( expression, ... )										R_ASSERT_T_U( ::inex::assert_untyped, expression, ##__VA_ARGS__ )
#define R_ASSERT_CMP_U( value1, operation, value2, ... )					R_ASSERT_CMP_T_U( value1, operation, value2, ::inex::assert_untyped, ##__VA_ARGS__ )

#include <inex/debug/macros_inline.h>

#endif // #ifndef INEX_DEBUG_MACROS_H_INCLUDED