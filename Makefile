# Configuration Makefile for EzSDL
#
# Copyright (c) 2018 Kirk Lange
#
# This software is provided 'as-is', without any express or implied
# warranty. In no event will the authors be held liable for any damages
# arising from the use of this software.
#
# Permission is granted to anyone to use this software for any purpose,
# including commercial applications, and to alter it and redistribute it
# freely, subject to the following restrictions:
#
# 1. The origin of this software must not be misrepresented; you must not
#    claim that you wrote the original software. If you use this software
#    in a product, an acknowledgment in the product documentation would be
#    appreciated but is not required.
# 2. Altered source versions must be plainly marked as such, and must not be
#    misrepresented as being the original software.
# 3. This notice may not be removed or altered from any source distribution.



###############################################################################
##############################  Standard Options  #############################
###############################################################################

# Name for your shared library code.
LIB_NAME = ezsdl

# Name of the one application that you want to run when you call `make run`.
# This should be equivalent to one of the items in `MAIN_SUBDIRS`.
EXEC_ME = pong

# Directory within /src of the app, example, and test that you want to build.
# TODO: Allow compilation of multiple mains. This will require compiling the
# shared API part of the code into a shared library.
MAIN_SUBDIRS = pong

# Source subdirectories. Shared among the apps, examples, and tests.
SRC_SUBDIRS = EzUtil EzSDL

# Packages that you want to include in your project.
# If `pkg-config` cannot find the package, `-I$(PREFIX)/include/$(PKG)` and
# `-l$(PKG)` will be added to the build instead, for each PKG in PKGS and for
# each PREFIX in PREFIXES. These are CASE SENSITIVE! Double check the correct
# case for your library. Commented out are examples.
PKGS = sdl2 SDL2_image SDL2_ttf

# Needed submodule include directories within /sub
SUB_INC_DIRS =

# Needed submodule source directories within /sub
SUB_SRC_DIRS =

# If the submodule has its test source files in the same directory as its
# actual API source files (facepalm), then you may want to manually specify
# individual source files here (including the file extension).
SUB_SRC_FILES =



###############################################################################
##############################  Advanced Options  #############################
###############################################################################

# Compiler
CC = gcc
#CC = emcc

# Compile API code to a dynamic (shared) library or static library.
# When using dynamic mode, beware of DLL Hell.
MODE = static
#MODE = dynamic

# C-Flags and library (`-l` only) settings
# In many cases the order in which your `-l`s appear matters!
# WARNING: EzC's emcc mode only supports libc, libc++, and SDL2 at the moment.
ifeq ($(CC),emcc)
	CF = -O3
	LF = -s USE_SDL=2 -s USE_SDL_IMAGE=2 -s USE_SDL_TTF=2
else
	CF = -std=c11 -O3 -w
	# The rest of LF will be taken care of by pkg-config
	LF = -lm
endif

# Source file extensions you want compiled.
SRC_EXTS = c #cpp

# Location(s) where EzC should look for `include` and `lib` subdirectories.
# No biggie if the directory doesn't exist.
PREFIXES = /usr /mingw64 /mingw32 $$HOME

# Root directory
ROOT = .

# Submodule directory
# WARNING: Changing this may cause a lot of headache!
SUB_DIR = $(ROOT)/sub



###############################################################################
##########################  Initialize EzC Framework  #########################
###############################################################################

.PHONY : init

init :
	@rm -rf $(SUB_DIR)/ezc
	@rm -rf $(SUB_DIR)/m.css
	@rm -rf .git/modules/$(SUB_DIR)/ezc
	@rm -rf .git/modules/$(SUB_DIR)/m.css
	@git rm -r --cached --ignore-unmatch $(SUB_DIR)
	git submodule add -f https://github.com/ezaf/ezc.git $(SUB_DIR)/ezc
	git submodule add -f https://github.com/mosra/m.css.git $(SUB_DIR)/m.css
	@rm -f script/ezc.mk
	@mkdir -p script
	@rmdir --ignore-fail-on-non-empty script

-include $(SUB_DIR)/ezc/script/ezc.mk
