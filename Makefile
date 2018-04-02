# ezSDL Makefile
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



# All source files within src/ to compile for the project
SRC_FILES = main.c ezwindow.c ezlog.c

# All submodule source files within ext/ to compile for the project
EXT_SRC_FILES = parson/parson.c

# All submodule include directories within ext/ to compile for the project
EXT_INC_DIR = parson

# Name for the executable FILE created in build/
OUT = debug



###############################################################################
#################  Standard configuration takes place above.  #################
#################   Advanced options can be tweaked below.    #################
###############################################################################



# Binaries
BIN_DIR = bin
# Build
BLD_DIR = build
# Documentation
DOC_DIR = docs
# External (git submodule)
EXT_DIR = ext
# Include
INC_DIR = include
# Libraries
LIB_DIR = lib
# Resources (config, textures, etc)
RES_DIR = res
# Source
SRC_DIR = src

# CC specifies which compiler we're using
CC = gcc

# Add source directory to source file names
OBJS = $(foreach OBJ,$(SRC_FILES),$(SRC_DIR)/$(OBJ)) \
	   $(foreach OBJ,$(EXT_SRC_FILES),$(EXT_DIR)/$(OBJ))

# Compiler and linker flags; include and library paths
# Must be C99 or newer because any older and SDL2 will get compile-time errors
CF_UNIV = -std=c99 -pedantic -O3 -w
LF_UNIV = -lSDL2main -lSDL2 -lSDL2_image
INC_UNIV = -I$(INC_DIR) \
		   $(foreach DIR,$(EXT_INC_DIR),-I$(EXT_DIR)/$(DIR))
LIB_UNIV =

# Find what OS we're on so we can better configure all the compiler options
# Linux->"Linux" | MacOS->"Darwin" | Windows->"MSYS_NT-#"
#UNAME = `(uname -s) 2>/dev/null`

# All compiler flags can be customized on a per-platform basis
ifeq ($(OS),Windows_NT)
	# Uncomment "-Wl..." to remove console window on Windows OS
	CF = $(CF_UNIV) #-Wl,-subsystem,windows
	LF = -lmingw32 $(LF_UNIV)
	# lua modding support planned
	INC = $(INC_UNIV) -ID:/org/libsdl/include #-ID:/org/lua-5.3.4/src
	LIB = $(LIB_UNIV) -LD:/org/libsdl/lib #-ID:/org/lua-5.3.4/src
	OPEN = cmd //c start "${@//&/^&}"
else
	CF = $(CF_UNIV)
	LF = $(LF_UNIV)
	INC = $(INC_UNIV)
	LIB = $(LIB_UNIV)
	OPEN = xdg-open
endif

NPD = --no-print-directory



.PHONY : all $(BLD_DIR) run dirs deps $(EXT_DIR) $(DOC_DIR) rtd
.PHONY : compile help clean clean-$(BLD_DIR) clean-$(EXT_DIR)

all :
	make $(DOC_DIR) $(NPD)
	make $(BLD_DIR) $(NPD)
	make run $(NPD)

help :
	@echo
	@echo "TODO: describe make targets"
	@echo

$(DOC_DIR) :
	mkdir -p $(DOC_DIR)
	make clean-$(DOC_DIR) $(NPD)
	make $(EXT_DIR) $(NPD)
	python3 $(EXT_DIR)/mcss/doxygen/dox2html5.py .doxyfile-mcss
	cd $(DOC_DIR) && rm -rf xml/
	make rtd $(NPD)
	cd $(DOC_DIR)/latex/ && make && mv refman.pdf ../refman.pdf && \
		cd ../ && rm -rf latex/

rtd :
	$(OPEN) docs/index.html
	#$(OPEN) docs/refman.pdf

$(BLD_DIR) :
	mkdir -p $(BIN_DIR)
	mkdir -p $(BLD_DIR)
	mkdir -p $(RES_DIR)
	cp -R $(BIN_DIR)/. $(BLD_DIR)
	cp -R $(RES_DIR)/. $(BLD_DIR)
	make $(EXT_DIR) $(NPD)
	make compile $(NPD)

$(EXT_DIR) :
	git submodule init
	git submodule update

compile : $(OBJS)
	$(CC) $(OBJS) $(INC) $(LIB) $(CF) $(LF) -o $(BLD_DIR)/$(OUT)

run :
	@echo && ./$(BLD_DIR)/$(OUT) && echo

clean :
	make clean-$(BLD_DIR) $(NPD)

clean-all :
	make clean-$(BLD_DIR) $(NPD)
	make clean-$(DOC_DIR) $(NPD)
	make clean-$(EXT_DIR) $(NPD)

clean-$(BLD_DIR) :
	rm -rf $(BLD_DIR)/*

clean-$(DOC_DIR) :
	rm -rf $(DOC_DIR)/*

clean-$(EXT_DIR) :
	rm -rf $(EXT_DIR)/*

