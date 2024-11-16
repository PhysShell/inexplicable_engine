set(PROJECT_NAME core)

################################################################################
# Source groups
################################################################################
set(no_group_source_files
    "../../command_line.h"
    "../../construction.h"
    "../../extensions.h"
    "../../library_dependencies.h"
    "../../memory_macros.h"
    "../../monitoring.h"
    "../../static_cast_checked.h"
    "../../stl_extensions.h"
    "../../stl_extensions_inline.h"
    "../../stl_extensions_vector.h"
    "../../strings_functions.h"
    "../../types.h"
    "../../utils.h"
    "../../utils_inline.h"
    "../api.h"
    "../core.h"
    "../engine.h"
    "../ie_core.h"
    "build_extensions.cpp"
    "build_extensions.h"
    "command_line.cpp"
    "core_entry_point.cpp"
    "encryption.cpp"
    "encryption.h"
    "ie_trims.cpp"
    "ie_trims.h"
    "log_callback.cpp"
    "log_callback.h"
    "logger.cpp"
    "logger.h"
    "pch.cpp"
    "pch.h"
    #"stdafx.h.gch" UNCOMMENT FOR MSVC  ?!
    "utils.cpp"
)
source_group("" FILES ${no_group_source_files})

if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Linux")
    set(debug
        "ie_debug.cpp"
        "ie_debug.h"
        "ie_debug_linux.cpp"
    )
else()
    set(debug
        "ie_debug.cpp"
        "ie_debug.h"
        "ie_debug_win.cpp"
    )
endif()

source_group("debug" FILES ${debug})

if(NOT "${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Linux")
    set(debug__win
        "RpcExStackTraceEngine.cpp"
        "RpcExStackTraceEngine.h"
    )
    source_group("debug\\win" FILES ${debug__win})
endif()

set(filesystem
    "fs_file_system.cpp"
    "fs_file_system.h"
    "fs_file_system_internal.cpp"
    "fs_file_system_internal.h"
    "fs_ini_file.cpp"
    "fs_ini_file.h"
    "memory_chunk_reader.h"
)
source_group("filesystem" FILES ${filesystem})

set(fs_manager
    "fs_directory_entry.h"
    "fs_directory_entry_inline.h"
    "fs_directory_iterators.cpp"
    "fs_directory_iterators.h"
    "fs_directory_iterators_inline.h"
    "fs_path_string.h"
    "fs_path_string_inline.h"
)
source_group("fs_manager" FILES ${fs_manager})

if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Linux")
    set(fs_manager__linux
        "fs_catalog_operations_linux_impl.h"
    )
    source_group("fs_manager\\linux" FILES ${fs_manager__linux})
else()
    set(fs_manager__win
        "fs_catalog_operations_win_impl.h"
    )
    source_group("fs_manager\\win" FILES ${fs_manager__win})
endif()

set(macros
    "../../c_array_functions.h"
    "../../macro_compiler.h"
    "../../macro_debug.h"
    "../../macro_declarations.h"
    "../../macro_extensions.h"
    "../../macro_log.h"
    "../../macro_platform.h"
    "../../macro_string.h"
    "../../macro_unreferenced_parameter.h"
)
source_group("macros" FILES ${macros})

set(math
    "../../math_color.h"
    "../../math_constants.h"
    "../../math_float2.h"
    "../../math_float2_inline.h"
    "../../math_float3.h"
    "../../math_float3_inline.h"
    "../../math_float4x4.h"
    "../../math_functions.h"
    "../../math_functions_inline.h"
    "../../math_matrix2.h"
    "../../math_matrix2_inline.h"
    "math_float4x4.cpp"
    "math_functions.cpp"
)
source_group("math" FILES ${math})

set(memory
    "../../memory_extensions.h"
    "../../memory_fixed_size_allocator.h"
    "ie_memory.cpp"
    "ie_memory.h"
    "ie_memory_inline.h"
    "memory_base_allocator.cpp"
    "memory_base_allocator.h"
    "memory_chunk_reader.cpp"
    "memory_general_allocator.cpp"
    "memory_general_allocator.h"
    "memory_multi.cpp"
    "memory_platform.h"
    "memory_pool_allocator.cpp"
    "memory_pool_allocator.h"
    "memory_shared_object.h"
    "memory_shared_object_inline.h"
)
source_group("memory" FILES ${memory})

if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Linux")
    set(memory__linux
        "memory_chunk_reader_linux.cpp"
    )
    source_group("memory\\linux" FILES ${memory__linux})
else()
    set(memory__win
        "memory_chunk_reader_win.cpp"
    )
    source_group("memory\\win" FILES ${memory__win})
endif()

# set(miscellanous
#     "core.cbp"
#     "core.depend"
#     "core.layout"
#     "post_build.bat"
# )
# source_group("miscellanous" FILES ${miscellanous})

if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Linux")
    set(os
        "../../os_extensions.h"
        "../../os_include.h"
        "../../os_linux.h"
    )
else()
    set(os
        "../../os_extensions.h"
        "../../os_include.h"
        "../../os_windows.h"
    )
endif()

source_group("os" FILES ${os})

set(resources
    "../../resources.h"
)
source_group("resources" FILES ${resources})

set(resources__resource
    "../../render/core/resource_intrusive_base.h"
)
source_group("resources\\resource" FILES ${resources__resource})

set(tasks
    "../../tasks_packaged_task.h"
)
source_group("tasks" FILES ${tasks})


if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Linux")
    set(threading
        "../../threading_functions.h"
        "../../threading_functions_linux_inline.h"
        "../../threading_policies.h"
        "cpuid_internal.cpp"
        "cpuid_internal.h"
        "ie_syncronize.cpp"
        "ie_syncronize.h"
        "processor_info.cpp"
        "processor_info.h"
    )
else()
    set(threading
        "../../threading_functions.h"
        "../../threading_functions_win_inline.h"
        "../../threading_policies.h"
        "cpuid_internal.cpp"
        "cpuid_internal.h"
        "ie_syncronize.cpp"
        "ie_syncronize.h"
        "processor_info.cpp"
        "processor_info.h"
    )
endif()

source_group("threading" FILES ${threading})

set(ALL_FILES
    ${no_group_source_files}
    ${debug}
    ${debug__win}
    ${filesystem}
    ${fs_manager}
    ${fs_manager__linux}
    ${fs_manager__win}
    ${macros}
    ${math}
    ${memory}
    ${memory__linux}
    ${memory__win}
    ${miscellanous}
    ${os}
    ${resources}
    ${resources__resource}
    ${tasks}
    ${threading}
)

################################################################################
# Target
################################################################################
add_library(${PROJECT_NAME} SHARED ${ALL_FILES})

target_precompile_headers(${PROJECT_NAME} PRIVATE
    "$<$<COMPILE_LANGUAGE:CXX>:${CMAKE_CURRENT_SOURCE_DIR}/pch.h>"
)

use_props(${PROJECT_NAME} "${CMAKE_CONFIGURATION_TYPES}" "${DEFAULT_CXX_PROPS}")
set(ROOT_NAMESPACE ieCore)

set_target_properties(${PROJECT_NAME} PROPERTIES
    VS_GLOBAL_KEYWORD "Win32Proj"
)
################################################################################
# Output directory
################################################################################
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        OUTPUT_DIRECTORY_DEBUG   "${CMAKE_SOURCE_DIR}/../binaries/msvc_${CMAKE_VS_PLATFORM_NAME}/"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Win32")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        OUTPUT_DIRECTORY_DEBUG   "${CMAKE_SOURCE_DIR}/../binaries/msvc_${CMAKE_VS_PLATFORM_NAME}/"
        OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/../binaries/"
    ) 
endif()
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY_DEBUG   "${CMAKE_SOURCE_DIR}/../binaries/libraries/msvc_${CMAKE_VS_PLATFORM_NAME}"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Win32")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY_DEBUG   "${CMAKE_SOURCE_DIR}/../binaries/libraries/msvc_${CMAKE_VS_PLATFORM_NAME}"
        ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}/../../libraries"
    )
endif()
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        ARCHIVE_OUTPUT_NAME_DEBUG   "${PROJECT_NAME}"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Win32")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        ARCHIVE_OUTPUT_NAME_DEBUG   "${PROJECT_NAME}"
        ARCHIVE_OUTPUT_NAME_RELEASE "${PROJECT_NAME}"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Linux")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        ARCHIVE_OUTPUT_NAME_DEBUG   "${PROJECT_NAME}"
        ARCHIVE_OUTPUT_NAME_RELEASE "${PROJECT_NAME}"
    )
endif()
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        INTERPROCEDURAL_OPTIMIZATION_RELEASE "TRUE"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Win32")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        INTERPROCEDURAL_OPTIMIZATION_RELEASE "TRUE"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Linux")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        INTERPROCEDURAL_OPTIMIZATION_RELEASE "TRUE"
    )
endif()

if("${CMAKE_SYSTEM_NAME}" STREQUAL "Linux")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        LIBRARY_OUTPUT_DIRECTORY_DEBUG   "${CMAKE_SOURCE_DIR}/../binaries/linux_gcc_${CMAKE_VS_PLATFORM_NAME}/"
        LIBRARY_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/../binaries/"

        ARCHIVE_OUTPUT_DIRECTORY_DEBUG   "${CMAKE_SOURCE_DIR}/../binaries/libraries/linux_gcc_${CMAKE_VS_PLATFORM_NAME}/"
        ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/../libraries/"
        
        RUNTIME_OUTPUT_DIRECTORY_DEBUG   "${CMAKE_SOURCE_DIR}/../binaries/linux_gcc_${CMAKE_VS_PLATFORM_NAME}/"
        RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/../binaries/"
    )

    message(STATUS "CMAKE_SYSTEM_NAME: ${CMAKE_SYSTEM_NAME}")
    message(STATUS "PROJECT_NAME: ${PROJECT_NAME}")

    get_target_property(LIB_DEBUG_OUTPUT ${PROJECT_NAME} LIBRARY_OUTPUT_DIRECTORY_DEBUG)
    get_target_property(LIB_RELEASE_OUTPUT ${PROJECT_NAME} LIBRARY_OUTPUT_DIRECTORY_RELEASE)

    get_target_property(ARCHIVE_DEBUG_OUTPUT ${PROJECT_NAME} ARCHIVE_OUTPUT_DIRECTORY_DEBUG)
    get_target_property(ARCHIVE_RELEASE_OUTPUT ${PROJECT_NAME} ARCHIVE_OUTPUT_DIRECTORY_RELEASE)

    get_target_property(RUNTIME_DEBUG_OUTPUT ${PROJECT_NAME} RUNTIME_OUTPUT_DIRECTORY_DEBUG)
    get_target_property(RUNTIME_RELEASE_OUTPUT ${PROJECT_NAME} RUNTIME_OUTPUT_DIRECTORY_RELEASE)

    message(STATUS "LIBRARY_OUTPUT_DIRECTORY_DEBUG: ${LIB_DEBUG_OUTPUT}")
    message(STATUS "LIBRARY_OUTPUT_DIRECTORY_RELEASE: ${LIB_RELEASE_OUTPUT}")

    message(STATUS "ARCHIVE_OUTPUT_DIRECTORY_DEBUG: ${ARCHIVE_DEBUG_OUTPUT}")
    message(STATUS "ARCHIVE_OUTPUT_DIRECTORY_RELEASE: ${ARCHIVE_RELEASE_OUTPUT}")

    message(STATUS "RUNTIME_OUTPUT_DIRECTORY_DEBUG: ${RUNTIME_DEBUG_OUTPUT}")
    message(STATUS "RUNTIME_OUTPUT_DIRECTORY_RELEASE: ${RUNTIME_RELEASE_OUTPUT}")
    
endif()
################################################################################
# Include directories
################################################################################
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    target_include_directories(${PROJECT_NAME} PUBLIC
        "$<$<CONFIG:Debug>:"
            "${CMAKE_CURRENT_SOURCE_DIR}/../../.."
        ">"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Win32")
    target_include_directories(${PROJECT_NAME} PUBLIC
        "$<$<CONFIG:Debug>:"
            "${CMAKE_CURRENT_SOURCE_DIR}/../../.."
        ">"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Linux")
    target_include_directories(${PROJECT_NAME} PUBLIC
        "$<$<CONFIG:Debug>:"
            "${CMAKE_CURRENT_SOURCE_DIR}/../../.."
        ">"
    )
	# target_include_directories(${PROJECT_NAME} PUBLIC
		# "$<$<CONFIG:Debug>:"
			# "${CMAKE_CURRENT_SOURCE_DIR}/../.."
		# ">"
		# "$<$<CONFIG:Release>:"
			# "${CMAKE_CURRENT_SOURCE_DIR}/../.."
		# ">"
    # )
endif()

################################################################################
# Compile definitions
################################################################################
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    target_compile_definitions(${PROJECT_NAME} PRIVATE
        "$<$<CONFIG:Debug>:"
            "_DEBUG;"
            "_MBCS"
        ">"
        "$<$<CONFIG:Release>:"
            "NDEBUG;"
            "UNICODE;"
            "_UNICODE"
        ">"
        "_WINDOWS;"
        "_USRDLL;"
        "IECORE_EXPORTS"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Win32")
    target_compile_definitions(${PROJECT_NAME} PRIVATE
        "$<$<CONFIG:Debug>:"
            "_DEBUG;"
            "DEBUG;"
            "_MBCS"
        ">"
        "$<$<CONFIG:Release>:"
            "WIN32;"
            "NDEBUG;"
            "UNICODE;"
            "_UNICODE"
        ">"
        "_WINDOWS;"
        "_USRDLL;"
        "IECORE_EXPORTS"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Linux")
    target_compile_definitions(${PROJECT_NAME} PRIVATE
        "$<$<CONFIG:Debug>:"
            "_DEBUG;"
            "DEBUG;"
            "_MBCS"
        ">"
        "$<$<CONFIG:Release>:"
            "LINUX;"
            "NDEBUG;"
            "UNICODE;"
            "_UNICODE"
        ">"
        "_LINUX;"
        "_USRDLL;"
        "IECORE_EXPORTS"
    )
endif()

################################################################################
# Compile and link options
################################################################################
if(MSVC)
    if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
        target_compile_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Debug>:
                /std:c++17;
                /Od;
                /W4
            >
            $<$<CONFIG:Release>:
                /O2;
                /Oi;
                /Gy;
                /W3;
                /Y-
            >
            ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT};
            ${DEFAULT_CXX_EXCEPTION_HANDLING}
        )
    elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Win32")
        target_compile_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Debug>:
                /std:c++17;
                /Od;
                /Zi;
                /FAcs
            >
            $<$<CONFIG:Release>:
                /O2;
                /Oi;
                /Gy;
                /W4;
                ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT};
                /Y-
            >
            ${DEFAULT_CXX_EXCEPTION_HANDLING}
        )
    endif()
    if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
        target_link_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Debug>:
                /SUBSYSTEM:CONSOLE;
                /INCREMENTAL
            >
            $<$<CONFIG:Release>:
                /SUBSYSTEM:WINDOWS;
                /OPT:REF;
                /OPT:ICF;
                /INCREMENTAL:NO
            >
            /DEBUG
        )
    elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Win32")
        target_link_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Debug>:
                /SUBSYSTEM:CONSOLE;
                /INCREMENTAL;
                /Zc:__cplusplus
            >
            $<$<CONFIG:Release>:
                /SUBSYSTEM:WINDOWS;
                /OPT:REF;
                /OPT:ICF;
                /INCREMENTAL:NO
            >
            /DEBUG
        )
    endif()
endif()

################################################################################
# Dependencies
################################################################################
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Win32")
    set(ADDITIONAL_LIBRARY_DEPENDENCIES
        "$<$<CONFIG:Debug>:"
            "kernel32;"
            "user32;"
            "gdi32;"
            "winspool;"
            "comdlg32;"
            "advapi32;"
            "shell32;"
            "ole32;"
            "oleaut32;"
            "uuid;"
            "odbc32;"
            "odbccp32"
        ">"
    )
endif()
target_link_libraries(${PROJECT_NAME} PUBLIC "${ADDITIONAL_LIBRARY_DEPENDENCIES}")

