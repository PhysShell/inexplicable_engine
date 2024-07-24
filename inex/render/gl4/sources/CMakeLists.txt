set(PROJECT_NAME render_gl4)

################################################################################
# Source groups
################################################################################
set(no_group_source_files
    "../../common/sources/camera.h"
    "../../common/sources/system_render.h"
    "cpp.hint"
    "ReadMe.txt"
    "render_ogl3.cpp"
    "system_render.cpp"
    "targetver.h"
)
source_group("" FILES ${no_group_source_files})

set(core
    "../../core/quasi_singleton.h"
    "dllmain.cpp"
    "pch.cpp"
    "pch.h"
)
source_group("core" FILES ${core})

set(include
    "../../base/base_classes.h"
    "../../core/vertex_colored.h"
)
source_group("include" FILES ${include})

set(include__facade
    "../../core/model.h"
    "../../facade/render_stage_type.h"
    "../../facade/sources/render_stage_type.cpp"
)
source_group("include\\facade" FILES ${include__facade})

set(include__gl4
    "../renderer.h"
)
source_group("include\\gl4" FILES ${include__gl4})

set(misc
    "../gl4_extensions.h"
    "../gl4_external.h"
    "gl4_entry_point.cpp"
    "gl4_external.cpp"
)
source_group("misc" FILES ${misc})

set(objects
    "model_manager.cpp"
    "model_manager.h"
    "visual.cpp"
    "visual.h"
)
source_group("objects" FILES ${objects})

set(render_common__hw_wrapper
    "../../common/sources/hw_wrapper.h"
    "../../common/sources/hw_wrapper_base_gl4.h"
    "../../common/sources/hw_wrapper_gl4.cpp"
)
source_group("render_common\\hw_wrapper" FILES ${render_common__hw_wrapper})

set(render_common__hw_wrapper__hw_caps
    "../../common/sources/hw_wrapper_inline.h"
)
source_group("render_common\\hw_wrapper\\hw_caps" FILES ${render_common__hw_wrapper__hw_caps})

set(render_common__win
    "../../common/sources/hw_wrapper_base_gl4_win_winapi.cpp"
    "../../common/sources/hw_wrapper_base_gl4_win_winapi.h"
)
source_group("render_common\\win" FILES ${render_common__win})

set(resources
    "../../common/sources/res_shader.h"
)
source_group("resources" FILES ${resources})

set(resources__model__render_models__base
    "../../common/render_model.h"
    "../../common/sources/render_model.cpp"
)
source_group("resources\\model\\render_models\\base" FILES ${resources__model__render_models__base})

set(resources__scene
    "../../common/scene.h"
    "../../common/scene_view.h"
    "../../common/sources/scene.cpp"
    "../../common/sources/scene_view.cpp"
)
source_group("resources\\scene" FILES ${resources__scene})

set(scene_render__stages
    "scene_context.h"
    "stage.cpp"
    "stage.h"
)
source_group("scene_render\\stages" FILES ${scene_render__stages})

set(world__renderer
    "../../common/renderer.h"
    "../../common/sources/renderer.cpp"
    "renderer_context.cpp"
    "renderer_context.h"
)
source_group("world\\renderer" FILES ${world__renderer})

set(world__renderer__stages
    "../../common/stage.h"
)
source_group("world\\renderer\\stages" FILES ${world__renderer__stages})

set(world__renderer__stages__g_stage
    "../../common/sources/stage_gbuffer.cpp"
    "../../common/stage_gbuffer.h"
)
source_group("world\\renderer\\stages\\g_stage" FILES ${world__renderer__stages__g_stage})

set(ALL_FILES
    ${no_group_source_files}
    ${core}
    ${include}
    ${include__facade}
    ${include__gl4}
    ${misc}
    ${objects}
    ${render_common__hw_wrapper}
    ${render_common__hw_wrapper__hw_caps}
    ${render_common__win}
    ${resources}
    ${resources__model__render_models__base}
    ${resources__scene}
    ${scene_render__stages}
    ${world__renderer}
    ${world__renderer__stages}
    ${world__renderer__stages__g_stage}
)

################################################################################
# Target
################################################################################
add_library(${PROJECT_NAME} STATIC ${ALL_FILES})

target_precompile_headers(${PROJECT_NAME} PRIVATE
    "$<$<COMPILE_LANGUAGE:CXX>:${CMAKE_CURRENT_SOURCE_DIR}/pch.h>"
)

use_props(${PROJECT_NAME} "${CMAKE_CONFIGURATION_TYPES}" "${DEFAULT_CXX_PROPS}")
set(ROOT_NAMESPACE render_ogl3)

set_target_properties(${PROJECT_NAME} PROPERTIES
    VS_GLOBAL_KEYWORD "Win32Proj"
)
################################################################################
# Target name
################################################################################
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
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
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        OUTPUT_DIRECTORY_DEBUG   "${CMAKE_SOURCE_DIR}/../binaries/libraries/msvc_${CMAKE_VS_PLATFORM_NAME}"
        OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/../binaries/msvc_${CMAKE_VS_PLATFORM_NAME}/"
    )
endif()
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY_DEBUG   "${CMAKE_SOURCE_DIR}/../binaries/libraries/msvc_${CMAKE_VS_PLATFORM_NAME}"
    )
endif()
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        ARCHIVE_OUTPUT_NAME_DEBUG   "${PROJECT_NAME}"
    )
endif()
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        INTERPROCEDURAL_OPTIMIZATION_RELEASE "TRUE"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        INTERPROCEDURAL_OPTIMIZATION_RELEASE "TRUE"
    )
endif()
################################################################################
# Include directories
################################################################################
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
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
        "RENDER_OGL3_EXPORTS;"
        "UNICODE;"
        "_UNICODE"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
    target_compile_definitions(${PROJECT_NAME} PRIVATE
        "$<$<CONFIG:Debug>:"
            "_DEBUG;"
            "INEX_RENDER_GL4_EXPORTS;"
            "_MBCS"
        ">"
        "$<$<CONFIG:Release>:"
            "NDEBUG;"
            "RENDER_OGL3_EXPORTS;"
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
    elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
        target_compile_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Debug>:
                /Od;
                /W4;
                /Zi;
                /FAcs
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
        string(CONCAT FILE_CL_OPTIONS
            "/Y-"
        )
    elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
        string(CONCAT FILE_CL_OPTIONS
            "/Y-"
        )
    endif()
    source_file_compile_options(dllmain.cpp ${FILE_CL_OPTIONS})
    if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
        target_link_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Release>:
                /OPT:REF;
                /OPT:ICF
            >
            /SUBSYSTEM:WINDOWS
        )
    elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
        target_link_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Release>:
                /OPT:REF;
                /OPT:ICF
            >
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

if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
    set(ADDITIONAL_LIBRARY_DEPENDENCIES
        "$<$<CONFIG:Debug>:"
            "core;"
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

if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
    target_link_directories(${PROJECT_NAME} PUBLIC
        "$<$<CONFIG:Debug>:"
            "${CMAKE_SOURCE_DIR}/inex/3rd_patry/libraries/x86/;"
            "${CMAKE_SOURCE_DIR}/../binaries/libraries/msvc_${CMAKE_VS_PLATFORM_NAME}/"
        ">"
    )
endif()

