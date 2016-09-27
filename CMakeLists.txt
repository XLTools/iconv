#  :copyright: (c) 2015-2016 The Regents of the University of California.
#  :license: LGPLv3, see licenses/gnu-lgpl-v3.0.md for more details.

cmake_minimum_required(VERSION 3.4)
project(IConv C)

# VERSION
# -------

set(${PROJECT}_VERSION_MAJOR 1)
set(${PROJECT}_VERSION_MINOR 14)

# ARGUMENTS
# ---------

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()
option(BUILD_STATIC "Build static or shared library" ON)

# ARCHITECTURES
# -------------

if(CMAKE_SYSTEM_NAME MATCHES "Linux")
    set(INCLUDE_DIR "${CMAKE_SOURCE_DIR}/linux")
elseif(CMAKE_SYSTEM_NAME MATCHES "Darwin")
    set(INCLUDE_DIR "${CMAKE_SOURCE_DIR}/darwin")
elseif(CMAKE_SYSTEM_NAME MATCHES "Windows")
    if(MSVC)
        # TODO
    else()
        # TODO
    endif()
else()
    message(FATAL_ERROR "Unrecognized configuration, please download IConv from GNU at https://www.gnu.org/software/libiconv, run ./configure and send libs/config.h to ahuszagh(at)gmail(.)com")
endif()

# DEFINITIONS
# -----------

add_definitions(
    -DBUILDING_LIBCHARSET
    -DBUILDING_DLL
    -DENABLE_RELOCATABLE=1
    -DIN_LIBRARY
    -DNO_XMALLOC
    -Dset_relocation_prefix=libcharset_set_relocation_prefix
    -Drelocate=libcharset_relocate
    -DHAVE_CONFIG_H
)

set(CMAKE_C_VISIBILITY_PRESET hidden)
if(UNIX)
    set(POSITION_INDEPENDENT_CODE TRUE)
endif()

# INCLUDES
# ---------

include_directories(
    "${CMAKE_SOURCE_DIR}/lib"
    "${CMAKE_SOURCE_DIR}/include"
    "${INCLUDE_DIR}"
)

# TARGETS
# -------

set(ICONV_SOURCES
    lib/iconv.c
    lib/localcharset.c
    lib/relocatable.c
)

if(BUILD_STATIC)
    add_library(iconv
        STATIC
        ${ICONV_SOURCES}
    )
else()
    add_library(iconv
        SHARED
        ${ICONV_SOURCES}
    )
endif()
