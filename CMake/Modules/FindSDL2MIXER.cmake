
# OpenClonk, http://www.openclonk.org
#
# Copyright (c) 2016, The OpenClonk Team and contributors
#
# Distributed under the terms of the ISC license; see accompanying file
# "COPYING" for details.
#
# "Clonk" is a registered trademark of Matthes Bender, used with permission.
# See accompanying file "TRADEMARK" for details.
#
# To redistribute this file separately, substitute the full license texts
# for the above references.

# Locate SDL_Mixer 2.
# This module defines
#  SDL2_MIXER_INCLUDE_DIR - a list of directories that need to be added to the include path
#  SDL2_MIXER_LIBRARIE - a list of libraries to link against to use SDL2
#  SDL2_MIXER_FOUND - if false, SDL2 cannot be used

if(SDL2_MIXER_FIND_QUIETLY)
    set(_FIND_SDL2_ARG QUIET)
endif()

find_package(SDL2 ${_FIND_SDL2_ARG})
find_path(SDL2_MIXER_INCLUDE_DIR SDL_mixer.h PATH_SUFFIXES SDL2 HINTS ENV SDL2DIR)
mark_as_advanced(SDL2_MIXER_INCLUDE_DIR)
find_library(SDL2_MIXER_LIBRARY SDL2_mixer HINTS ENV SDL2DIR)
mark_as_advanced(SDL2_MIXER_LIBRARY)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(SDL2_MIXER REQUIRED_VARS SDL2_MIXER_LIBRARY SDL2_MIXER_INCLUDE_DIR
        SDL2_LIBRARY SDL2_INCLUDE_DIR)

if (SDL2_MIXER_FOUND)
    set(SDL2_MIXER_LIBRARIE ${SDL2_MIXER_LIBRARY} ${SDL2_LIBRARY})
    set(SDL2_MIXER_INCLUDE_DIR ${SDL2_MIXER_INCLUDE_DIR} ${SDL2_INCLUDE_DIR})

    message("SDL2_MIXER_LIBRARIE is ${SDL2_MIXER_LIBRARY}")
    message("SDL2_MIXER_INCLUDE_DIR ${SDL2_MIXER_INCLUDE_DIR}")
endif()