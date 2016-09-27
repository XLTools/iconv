#  :copyright: (c) 2015-2016 The Regents of the University of California.
#  :license: LGPLv3, see licenses/gnu-lgpl-v3.0.md for more details.

cmake_minimum_required(VERSION 3.4)
project(IConv C)

# VERSION
# -------

set(${PROJECT}_VERSION_MAJOR 1)
set(${PROJECT}_VERSION_MINOR 14)

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


# CMAKE_SYSTEM_NAME
# CMAKE_HOST_SYSTEM

# gcc -Ilinux -Iinclude -fvisibility=hidden -DBUILDING_LIBCHARSET -DBUILDING_DLL -DENABLE_RELOCATABLE=1 -DIN_LIBRARY -DNO_XMALLOC -Dset_relocation_prefix=libcharset_set_relocation_prefix -Drelocate=libcharset_relocate -DHAVE_CONFIG_H -c lib/localcharset.c -o build/localcharset.o

# gcc -Ilinux -Iinclude -fvisibility=hidden -DBUILDING_LIBCHARSET -DBUILDING_DLL -DENABLE_RELOCATABLE=1 -DIN_LIBRARY -DNO_XMALLOC -Dset_relocation_prefix=libcharset_set_relocation_prefix -Drelocate=libcharset_relocate -DHAVE_CONFIG_H -c lib/relocatable.c -o build/relocatable.o

# gcc -Ilib -Ilinux -Iinclude -fvisibility=hidden -DBUILDING_LIBICONV -DBUILDING_DLL -DENABLE_RELOCATABLE=1 -DIN_LIBRARY -DNO_XMALLOC -Dset_relocation_prefix=libiconv_set_relocation_prefix -Drelocate=libiconv_relocate -DHAVE_CONFIG_H -c lib/iconv.c -o build/iconv.o

# ar rvs build/libiconv.a build/*.o
