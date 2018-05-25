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

# Directory within project/ of the example project that you want to build
MAIN_SUBDIR = pong

# Directory within src/ for which all *.c files will be added to the build
SRC_SUBDIRS = EzUtil EzSDL

# Needed submodule include directories within ext/
SUB_INC_DIRS =

# Needed submodule source directories within ext/
SUB_SRC_DIRS =

# If the submodule has its test source files in the same directory as its
#   actual API source files (facepalm), then you may want to manually specify
#   individual source files here
EXT_SRC_FILES =

# Name for the build subdirectory and executable (file extension not necessary)
OUT = $(MAIN_SUBDIR)



###############################################################################
##############################  Advanced Options  #############################
###############################################################################

# Compiler and linker settings
# In many cases the order in which your `-l`s appear matters!
# The gcc and emcc options can easily be toggled by changing the ifeq check
# WARNING: EzC's emcc mode only supports libc, libc++, and SDL2 right now
ifeq (1,1)
	CC = gcc
	CF = -std=c11 -O3 -Werror
	LF = -lm -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf
else
	CC = emcc
	CF = -O3
	LF = -s USE_SDL=2 -s USE_SDL_IMAGE=2 -s USE_SDL_TTF=2
endif

# The possible source file extensions
SRC_EXTS = c cpp

# May be necessary if building on Windows without MSYS2.
# Outside include and lib directories for `gcc` such as the paths to the SDL2
# Change the path to match where you have installed the stuff on your machine
# Commented out are examples for luac
GCC_I_DIRS_WIN = #D:/org/lua/src
GCC_L_DIRS_WIN = #D:/org/lua/src

# Needed for Linux if you installed your libraries in your home directory
GCC_I_DIRS_LIN = #$$HOME/include
GCC_L_DIRS_LIN = #$$HOME/lib

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
