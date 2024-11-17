set(PROJECT_NAME sound)

################################################################################
# Source groups
################################################################################
set(no_group_source_files
    "ReadMe.txt"
)
source_group("" FILES ${no_group_source_files})

set(Header_Files
    "../api.h"
    "../library_linkage.h"
    "../sound.h"
    "pch.h"
    "sound_file.h"
    "sound_object.h"
    "targetver.h"
)
source_group("Header Files" FILES ${Header_Files})

if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Linux")
    set(Source_Files
        "pch.cpp"
        "sound.cpp"
        "sound_file.cpp"
        "sound_object.cpp"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Win32" OR "${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    set(Source_Files
        "dllmain.cpp"
        "pch.cpp"
        "sound.cpp"
        "sound_file.cpp"
        "sound_object.cpp"
    )
else()
    message(FATAL_ERROR "please define Source_Files for your platform")
endif()

source_group("Source Files" FILES ${Source_Files})

set(ALL_FILES
    ${no_group_source_files}
    ${Header_Files}
    ${Source_Files}
)

################################################################################
# Target
################################################################################
add_library(${PROJECT_NAME} SHARED ${ALL_FILES})

target_precompile_headers(${PROJECT_NAME} PRIVATE
    "$<$<COMPILE_LANGUAGE:CXX>:${CMAKE_CURRENT_SOURCE_DIR}/pch.h>"
)

use_props(${PROJECT_NAME} "${CMAKE_CONFIGURATION_TYPES}" "${DEFAULT_CXX_PROPS}")
set(ROOT_NAMESPACE sound)

set_target_properties(${PROJECT_NAME} PROPERTIES
    VS_GLOBAL_KEYWORD "Win32Proj"
)

################################################################################
# 3rd party packages
################################################################################

if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Linux")
    find_package(OpenAL REQUIRED)
    if(OPENAL_FOUND)
        target_include_directories(${PROJECT_NAME} PRIVATE ${OPENAL_INCLUDE_DIR})
        target_link_libraries(${PROJECT_NAME} PRIVATE ${OPENAL_LIBRARY})
    else()
        message(FATAL_ERROR "OpenAL not found.")
    endif()

    list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules")

    find_package(ALUT REQUIRED)

    if(ALUT_FOUND)
        target_include_directories(${PROJECT_NAME} PRIVATE ${ALUT_INCLUDE_DIRS})
        target_link_libraries(${PROJECT_NAME} PRIVATE ${ALUT_LIBRARIES} OpenAL::OpenAL)
    else()
        message(FATAL_ERROR "ALUT not found. Please install freealut.")
    endif()
else()
    message(WARNING "ALUT not configured on your platform.")
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
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY_DEBUG   "${CMAKE_SOURCE_DIR}/../binaries/libraries/msvc_${CMAKE_VS_PLATFORM_NAME}"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Win32")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY_DEBUG   "${CMAKE_SOURCE_DIR}/../binaries/libraries/msvc_${CMAKE_VS_PLATFORM_NAME}"
    )
endif()
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        ARCHIVE_OUTPUT_NAME_DEBUG   "${PROJECT_NAME}"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Win32")
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
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    target_include_directories(${PROJECT_NAME} PUBLIC
        "$<$<CONFIG:Debug>:"
            "${CMAKE_CURRENT_SOURCE_DIR}/../../3rd_patry/include;"
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
            "INEX_SOUND_EXPORTS;"
            "_MBCS"
        ">"
        "$<$<CONFIG:Release>:"
            "NDEBUG;"
            "SOUND_EXPORTS;"
            "UNICODE;"
            "_UNICODE"
        ">"
        "_WINDOWS;"
        "_USRDLL"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Win32")
    target_compile_definitions(${PROJECT_NAME} PRIVATE
        "$<$<CONFIG:Debug>:"
            "_DEBUG;"
            "INEX_SOUND_EXPORTS;"
            "_MBCS"
        ">"
        "$<$<CONFIG:Release>:"
            "NDEBUG;"
            "SOUND_EXPORTS;"
            "UNICODE;"
            "_UNICODE"
        ">"
        "WIN32;"
        "_WINDOWS;"
        "_USRDLL"
    )
    elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Linux")
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
        "INEX_SOUND_EXPORTS;"
        "SOUND_EXPORTS"
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
                /Gy;
                /W3
            >
            ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT};
            ${DEFAULT_CXX_EXCEPTION_HANDLING}
        )
    elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Win32")
        target_compile_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Debug>:
                /Od;
                /Zi
            >
            $<$<CONFIG:Release>:
                /O2;
                /Oi;
                /Gy;
                /W3;
                ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT}
            >
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
            /SUBSYSTEM:WINDOWS
        )
    elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Win32")
        target_link_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Debug>:
                /INCREMENTAL
                /SAFESEH:NO
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
    core
)

if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    set(ADDITIONAL_LIBRARY_DEPENDENCIES
        "$<$<CONFIG:Debug>:"
            "core;"
            " OpenAL32;"
            "ALut;"
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
            "core;"
            "OpenAL32;"
            "ALut;"
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
            "${CMAKE_SOURCE_DIR}/inex/3rd_patry/libraries/x86/;"
            "${CMAKE_SOURCE_DIR}/../binaries/libraries/msvc_${CMAKE_VS_PLATFORM_NAME}/"
        ">"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Win32")
    target_link_directories(${PROJECT_NAME} PUBLIC
        "$<$<CONFIG:Debug>:"
            "${CMAKE_SOURCE_DIR}/inex/3rd_patry/libraries/x86/;"
            "${CMAKE_SOURCE_DIR}/../binaries/libraries/msvc_${CMAKE_VS_PLATFORM_NAME}/"
        ">"
    )
endif()

