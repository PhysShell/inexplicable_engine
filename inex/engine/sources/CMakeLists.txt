set(PROJECT_NAME engine)

################################################################################
# Source groups
################################################################################
set(no_group_source_files
    "../api.h"
    "../engine_user.h"
    "../library_dependencies.h"
    "engine_entry_point.cpp"
    "engine_memory.h"
    "engine_world.cpp"
    "engine_world.h"
    "engine_world_logic.cpp"
    "engine_world_win.cpp"
#    "library_loader.h"
    "pch.cpp"
    "pch.h"
)
source_group("" FILES ${no_group_source_files})

set(miscellanous
    "engine.cbp"
    "engine.depend"
    "engine.filters"
    "engine.layout"
    "stdafx.h.gch"
)
source_group("miscellanous" FILES ${miscellanous})

set(ALL_FILES
    ${no_group_source_files}
    ${miscellanous}
)

################################################################################
# Target
################################################################################
add_library(${PROJECT_NAME} SHARED ${ALL_FILES})

target_precompile_headers(${PROJECT_NAME} PRIVATE
    "$<$<COMPILE_LANGUAGE:CXX>:${CMAKE_CURRENT_SOURCE_DIR}/pch.h>"
)

use_props(${PROJECT_NAME} "${CMAKE_CONFIGURATION_TYPES}" "${DEFAULT_CXX_PROPS}")
set(ROOT_NAMESPACE ieEngine)

set_target_properties(${PROJECT_NAME} PROPERTIES
    VS_GLOBAL_KEYWORD "Win32Proj"
)
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
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    target_include_directories(${PROJECT_NAME} PUBLIC
        "$<$<CONFIG:Debug>:"
            "${CMAKE_CURRENT_SOURCE_DIR}/../../.."
        ">"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Win32")
    target_include_directories(${PROJECT_NAME} PUBLIC
        "$<$<CONFIG:Debug>:"
            "${CMAKE_CURRENT_SOURCE_DIR}/../../3rd_patry/include;"
            "${CMAKE_CURRENT_SOURCE_DIR}/../../.."
        ">"
    )
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
            "_CONSOLE;"
            "UNICODE;"
            "_UNICODE"
        ">"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Win32")
    target_compile_definitions(${PROJECT_NAME} PRIVATE
        "$<$<CONFIG:Debug>:"
            "INEX_ENGINE_EXPORT;"
            "_DEBUG;"
            "_MBCS"
        ">"
        "$<$<CONFIG:Release>:"
            "WIN32;"
            "NDEBUG;"
            "_CONSOLE;"
            "UNICODE;"
            "_UNICODE"
        ">"
    )
endif()
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Win32")
    set_source_files_properties(engine_entry_point.cpp PROPERTIES
        COMPILE_DEFINITIONS_DEBUG "_DEBUG"
    )
endif()

################################################################################
# Compile and link options
################################################################################
if(MSVC)
    if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
        target_compile_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Debug>:
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
                ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT};
                /Y-
            >
            /W4;
            ${DEFAULT_CXX_EXCEPTION_HANDLING}
        )
    endif()
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
            /SUBSYSTEM:CONSOLE
        )
    elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Win32")
        target_link_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Debug>:
                /SUBSYSTEM:WINDOWS;
                /INCREMENTAL;
                /NODEFAULTLIB:library
            >
            $<$<CONFIG:Release>:
                /SUBSYSTEM:CONSOLE;
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
add_dependencies(${PROJECT_NAME}
    render_base
    sound
    ui
)

# Link with other targets.
target_link_libraries(${PROJECT_NAME} PUBLIC
    core
)

if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    set(ADDITIONAL_LIBRARY_DEPENDENCIES
        "$<$<CONFIG:Debug>:"
            "render;"
            "opengl32;"
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
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Win32")
    set(ADDITIONAL_LIBRARY_DEPENDENCIES
        "$<$<CONFIG:Debug>:"
            "ui;"
            "sound;"
            "render_base;"
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

if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    target_link_directories(${PROJECT_NAME} PUBLIC
        "$<$<CONFIG:Debug>:"
            "${CMAKE_SOURCE_DIR}/inex/3rd_patry/libraries/x64"
        ">"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Win32")
    target_link_directories(${PROJECT_NAME} PUBLIC
        "$<$<CONFIG:Debug>:"
            "${CMAKE_SOURCE_DIR}/inex/3rd_patry/libraries/x86;"
            "${CMAKE_SOURCE_DIR}/../binaries/libraries/msvc_${CMAKE_VS_PLATFORM_NAME}/"
        ">"
    )
endif()

