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
option(BUILD_TESTS "Build tests" OFF)

# ARCHITECTURES
# -------------

if(CMAKE_SYSTEM_NAME MATCHES "Linux")
    set(INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/platforms/linux")
elseif(CMAKE_SYSTEM_NAME MATCHES "Darwin")
    set(INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/platforms/darwin")
elseif(CMAKE_SYSTEM_NAME MATCHES "Windows")
    if(MSVC)
        set(INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/platforms/msvc")
    elseif(MSYS)
        set(INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/platforms/msys")
    else()
        set(INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/platforms/mingw")
    endif()
else()
    message(FATAL_ERROR "Unrecognized configuration, please download IConv from GNU at https://www.gnu.org/software/libiconv, run ./configure and send libs/config.h to ahuszagh(at)gmail(.)com")
endif()

# STANDARDS
# ---------

# Various patches, see: https://lists.freebsd.org/pipermail/freebsd-stable/2014-February/077408.html
set(CMAKE_C_VISIBILITY_PRESET hidden)
set(CMAKE_C_STANDARD 90)
if(UNIX)
    set(POSITION_INDEPENDENT_CODE TRUE)
endif()

# WARNINGS
# --------

if(MSYS)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-pointer-to-int-cast -Wno-int-to-pointer-cast -Wno-attributes -Wno-write-strings")
endif()

# DEFINITIONS
# -----------

add_definitions(
)

if(MSVC)
    add_definitions(
        -D_WINDOWS
    )
else()
    add_definitions(
        -DIN_LIBRARY
        -DNO_XMALLOC
        -Dset_relocation_prefix=libcharset_set_relocation_prefix
        -Drelocate=libcharset_relocate
        -DBUILDING_DLL
        -DENABLE_RELOCATABLE=1
        -DHAVE_CONFIG_H
        -DBUILDING_LIBCHARSET
    )
endif()

if(BUILD_STATIC)
    # STATIC
    add_definitions(
        -DUSING_STATIC_LIBICONV
    )
    remove_definitions(
        -DBUILDING_LIBICONV
    )
    if(MSVC)
        add_definitions(
            -D_LIB
        )
    endif()
else()
    # SHARED
    add_definitions(
        -DBUILDING_LIBICONV
    )
    remove_definitions(
        -DUSING_STATIC_LIBICONV
    )
    if(MSVC)
        add_definitions(
            -D_USRDLL
            -DLIBICONV_EXPORTS
            -DBUILDING_LIBCHARSET
        )
    endif()
endif()

# INCLUDES
# ---------

include_directories(
    "${CMAKE_CURRENT_SOURCE_DIR}/lib"
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
    "${INCLUDE_DIR}"
)

# TARGETS
# -------

set(ICONV_SOURCES
    lib/iconv.c
    lib/localcharset.c
    lib/relocatable.c
)

if(MSVC)
    list(APPEND ICONV_SOURCES platforms/msvc/libiconv.rc)
endif()

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

if(BUILD_TESTS)
    # BUILD TESTS

    add_executable(IConvTests
        tests/test.c
    )
    target_link_libraries(IConvTests
        iconv
    )
endif()
