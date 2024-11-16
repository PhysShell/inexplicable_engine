# FindALUT.cmake

find_path(ALUT_INCLUDE_DIR
    NAMES alut.h
    PATH_SUFFIXES AL
)

find_library(ALUT_LIBRARY
    NAMES alut
)

if(ALUT_INCLUDE_DIR AND ALUT_LIBRARY)
    set(ALUT_FOUND TRUE)
    set(ALUT_INCLUDE_DIRS ${ALUT_INCLUDE_DIR})
    set(ALUT_LIBRARIES ${ALUT_LIBRARY})
else()
    set(ALUT_FOUND FALSE)
endif()

if(ALUT_FOUND)
    message(STATUS "Found ALUT: ${ALUT_LIBRARY} (include: ${ALUT_INCLUDE_DIR})")
else()
    message(WARNING "Could NOT find ALUT")
endif()

mark_as_advanced(ALUT_INCLUDE_DIR ALUT_LIBRARY)