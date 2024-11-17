set(PROJECT_NAME render_base)

################################################################################
# Source groups
################################################################################
if("${CMAKE_SYSTEM_NAME}" STREQUAL "Linux")
    set(no_group_source_files
        "../../core/shaders.h"
        "../../core/sources/shaders.cpp"
        "pch.cpp"
        "pch.h"
        "render_base.cpp"
        "render_base_entry_point.cpp"
        "render_base_world.cpp"
    )
elseif("${CMAKE_SYSTEM_NAME}" STREQUAL "Win32" OR "${CMAKE_SYSTEM_NAME}" STREQUAL "x64")
    set(no_group_source_files
        "../../core/shaders.h"
        "../../core/sources/shaders.cpp"
        "dllmain.cpp"
        "pch.cpp"
        "pch.h"
        "ReadMe.txt"
        "render_base.cpp"
        "render_base_entry_point.cpp"
        "render_base_world.cpp"
        "targetver.h"
    )
else()
    message(FATAL_ERROR, "[${PROJECT_NAME}]: please define 'no_group_source_files' for your platform")
endif()

source_group("" FILES ${no_group_source_files})

set(commands
    "command_processor.cpp"
    "command_processor.h"
)
source_group("commands" FILES ${commands})

set(include
    "../api.h"
    "../world.h"
)
source_group("include" FILES ${include})

set(include__base
    "../engine_renderer.h"
    "../engine_wrapper.h"
    "../extended_renderer.h"
    "../game_renderer.h"
    "../platform.h"
    "../visual.h"
)
source_group("include\\base" FILES ${include__base})

set(platforms
    "platform_api.h"
)
source_group("platforms" FILES ${platforms})

set(platforms__pc
    "platform_api_pc.cpp"
    "platform_gl4.cpp"
    "platform_gl4.h"
    "platform_gl4_inline.h"
)
source_group("platforms\\pc" FILES ${platforms__pc})

set(world
    "game_renderer.cpp"
    "game_renderer.h"
)
source_group("world" FILES ${world})

set(world__engine_enderer
    "engine_renderer.cpp"
    "engine_renderer.h"
)
source_group("world\\engine_enderer" FILES ${world__engine_enderer})

set(ALL_FILES
    ${no_group_source_files}
    ${commands}
    ${include}
    ${include__base}
    ${platforms}
    ${platforms__pc}
    ${world}
    ${world__engine_enderer}
)

################################################################################
# Target
################################################################################
add_library(${PROJECT_NAME} SHARED ${ALL_FILES})

target_precompile_headers(${PROJECT_NAME} PRIVATE
    "$<$<COMPILE_LANGUAGE:CXX>:${CMAKE_CURRENT_SOURCE_DIR}/pch.h>"
)

use_props(${PROJECT_NAME} "${CMAKE_CONFIGURATION_TYPES}" "${DEFAULT_CXX_PROPS}")
set(ROOT_NAMESPACE render_base)

set_target_properties(${PROJECT_NAME} PROPERTIES
    VS_GLOBAL_KEYWORD "Win32Proj"
)

################################################################################
# 3rd party packages
################################################################################

if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Linux")
    list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules")

    find_package(OpenGL REQUIRED)
    
    if(OPENGL_FOUND)
        target_include_directories(${PROJECT_NAME} PRIVATE ${OPENGL_INCLUDE_DIRS})
        target_link_libraries(${PROJECT_NAME} PRIVATE ${OPENGL_LIBRARIES})
    else()
        message(FATAL_ERROR "OpenGL not found.")
    endif()
else()
    message(WARNING "OpenGL not configured on your platform.")
endif()

################################################################################
# Target name
################################################################################
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Win32")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        TARGET_NAME_DEBUG   "${PROJECT_NAME}"
    )
endif()
################################################################################
# Output directory
################################################################################
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        OUTPUT_DIRECTORY_DEBUG   "${CMAKE_SOURCE_DIR}/../binaries/msvc_${CMAKE_VS_PLATFORM_NAME}/"
        OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/../binaries/msvc_${CMAKE_VS_PLATFORM_NAME}/"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Win32")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        OUTPUT_DIRECTORY_DEBUG   "${CMAKE_SOURCE_DIR}/../binaries/msvc_${CMAKE_VS_PLATFORM_NAME}/"
        OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/../binaries/msvc_${CMAKE_VS_PLATFORM_NAME}/"
    )
endif()
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Win32")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY_DEBUG   "${CMAKE_SOURCE_DIR}/../binaries/libraries/msvc_${CMAKE_VS_PLATFORM_NAME}"
    )
endif()
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Win32")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        ARCHIVE_OUTPUT_NAME_DEBUG   "${PROJECT_NAME}"
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
endif()
################################################################################
# Include directories
################################################################################
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Win32")
    target_include_directories(${PROJECT_NAME} PUBLIC
        "$<$<CONFIG:Debug>:"
            "${CMAKE_CURRENT_SOURCE_DIR}/../../../3rd_patry/include;"
            "${CMAKE_CURRENT_SOURCE_DIR}/../../../..;"
            "${CMAKE_CURRENT_SOURCE_DIR}/."
        ">"
    )
endif()

################################################################################
# Compile definitions
################################################################################
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    target_compile_definitions(${PROJECT_NAME} PRIVATE
        "$<$<CONFIG:Debug>:"
            "_DEBUG"
        ">"
        "$<$<CONFIG:Release>:"
            "NDEBUG"
        ">"
        "_WINDOWS;"
        "_USRDLL;"
        "RENDER_BASE_EXPORTS;"
        "UNICODE;"
        "_UNICODE"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Win32")
    target_compile_definitions(${PROJECT_NAME} PRIVATE
        "$<$<CONFIG:Debug>:"
            ";"
            "_DEBUG;"
            "INEX_RENDER_EXPORTS;"
            "INEX_RENDER_BASE_EXPORTS;"
            "_MBCS"
        ">"
        "$<$<CONFIG:Release>:"
            "NDEBUG;"
            "RENDER_BASE_EXPORTS;"
            "UNICODE;"
            "_UNICODE"
        ">"
        "WIN32;"
        "_WINDOWS;"
        "_USRDLL"
    )
endif()

################################################################################
# Compile and link options
################################################################################
if(MSVC)
    if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
        target_compile_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Debug>:
                /Od
            >
            $<$<CONFIG:Release>:
                /O2;
                /Oi;
                /Gy
            >
            /W3;
            ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT};
            ${DEFAULT_CXX_EXCEPTION_HANDLING}
        )
    elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Win32")
        target_compile_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Debug>:
                /Od;
                /Zi;
                /FAcs
            >
            $<$<CONFIG:Release>:
                /O2;
                /Oi;
                /Gy;
                ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT}
            >
            /W3;
            ${DEFAULT_CXX_EXCEPTION_HANDLING}
        )
    endif()
    if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
        string(CONCAT FILE_CL_OPTIONS
            "/Y-"
        )
    elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Win32")
        string(CONCAT FILE_CL_OPTIONS
            "/Y-"
        )
    endif()
    source_file_compile_options(dllmain.cpp ${FILE_CL_OPTIONS})
    if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
        target_link_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Debug>:
                /INCREMENTAL
            >
            $<$<CONFIG:Release>:
                /OPT:REF;
                /OPT:ICF;
                /INCREMENTAL:NO
            >
            /DEBUG;
            /SUBSYSTEM:WINDOWS
        )
    elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Win32")
        target_link_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Debug>:
                /INCREMENTAL
            >
            $<$<CONFIG:Release>:
                /OPT:REF;
                /OPT:ICF;
                /INCREMENTAL:NO
            >
            /DEBUG;
            /SUBSYSTEM:WINDOWS
        )
    endif()
endif()

################################################################################
# Dependencies
################################################################################
add_dependencies(${PROJECT_NAME}
    render_gl4
)

if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Win32")
    set(ADDITIONAL_LIBRARY_DEPENDENCIES
        "$<$<CONFIG:Debug>:"
            "core;"
            "render_gl4;"
            "glu32;"
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
    target_link_libraries(${PROJECT_NAME} PUBLIC "${ADDITIONAL_LIBRARY_DEPENDENCIES}")
elseif("${CMAKE_SYSTEM_NAME}" STREQUAL "Linux")
    target_link_libraries(${PROJECT_NAME} PRIVATE
        render_gl4
    )
else()
    message(FATAL_ERROR, "please define 'target_link_libraries' for your platform")
endif()

if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Win32")
    target_link_directories(${PROJECT_NAME} PUBLIC
        "$<$<CONFIG:Debug>:"
            "${CMAKE_SOURCE_DIR}/inex/3rd_patry/libraries/x86/;"
            "${CMAKE_SOURCE_DIR}/../binaries/libraries/msvc_${CMAKE_VS_PLATFORM_NAME}/"
        ">"
    )
endif()

