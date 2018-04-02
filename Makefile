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



# All source FILES within src/ to compile for the project
SOURCE = main.c ezwindow.c ezlog.c

# All submodule source FILES within submod/ to compile for the project
SUBMOD_SOURCE = parson/parson.c

# All submodule include DIRECTORIES within submod/ to compile for the project
SUBMOD_INCLUDE = parson

# Name for the executable FILE created in build/
OUT = debug



###############################################################################
#################  Standard configuration takes place above.  #################
#################   Advanced options can be tweaked below.    #################
###############################################################################



ASSET_DIR = asset
BUILD_DIR = build
DOCS_DIR = docs
INCLUDE_DIR = include
LIB_DIR = lib
SOURCE_DIR = src
SUBMOD_DIR = submod

# CC specifies which compiler we're using
CC = gcc

# Add source directory to source file names
OBJS = $(foreach OBJ,$(SOURCE),$(SOURCE_DIR)/$(OBJ)) \
	   $(foreach OBJ,$(SUBMOD_SOURCE),$(SUBMOD_DIR)/$(OBJ))

# Compiler and linker flags; include and library paths
# Must be C99 or newer because any older and SDL2 will get compile-time errors
CF_UNIV = -std=c99 -pedantic -O3 -w
LF_UNIV = -lSDL2main -lSDL2 -lSDL2_image
INC_UNIV = -I$(INCLUDE_DIR) \
		   $(foreach DIR,$(SUBMOD_INCLUDE),-I$(SUBMOD_DIR)/$(DIR))
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



.PHONY : all $(BUILD_DIR) run dirs deps $(SUBMOD_DIR) $(DOCS_DIR) rtd
.PHONY : compile help clean clean-$(BUILD_DIR) clean-$(SUBMOD_DIR)

all :
	make $(DOCS_DIR) $(NPD)
	make $(BUILD_DIR) $(NPD)
	make run $(NPD)

help :
	@echo
	@echo "TODO: describe make targets"
	@echo

$(DOCS_DIR) :
	make clean-$(DOCS_DIR) $(NPD)
	make $(SUBMOD_DIR) $(NPD)
	python3 $(SUBMOD_DIR)/mcss/doxygen/dox2html5.py .doxyfile-mcss
	cd $(DOCS_DIR) && rm -rf xml/
	$(OPEN) docs/index.html
	cd $(DOCS_DIR)/latex/ && make && mv refman.pdf ../refman.pdf && \
		cd ../ && rm -rf latex/
	#make rtd $(NPD)

rtd :
	$(OPEN) docs/index.html
	#$(OPEN) docs/refman.pdf

$(BUILD_DIR) :
	make dirs $(NPD)
	cp -R $(LIB_DIR)/. $(BUILD_DIR)
	cp -R $(ASSET_DIR)/. $(BUILD_DIR)
	make $(SUBMOD_DIR) $(NPD)
	make compile $(NPD)

dirs :
	mkdir -p $(BUILD_DIR)
	mkdir -p $(LIB_DIR)
	# TODO: remove once stuff gets added to ASSET_DIR
	mkdir -p $(ASSET_DIR)

$(SUBMOD_DIR) :
	git submodule init
	git submodule update

compile : $(OBJS)
	$(CC) $(OBJS) $(INC) $(LIB) $(CF) $(LF) -o $(BUILD_DIR)/$(OUT)

run :
	@echo && ./$(BUILD_DIR)/$(OUT) && echo

clean :
	make clean-$(BUILD_DIR) $(NPD)

clean-all :
	make clean-$(BUILD_DIR) $(NPD)
	make clean-$(DOCS_DIR) $(NPD)
	make clean-$(SUBMOD_DIR) $(NPD)

clean-$(BUILD_DIR) :
	rm -rf $(BUILD_DIR)/*

clean-$(DOCS_DIR) :
	rm -rf $(DOCS_DIR)/*

clean-$(SUBMOD_DIR) :
	rm -rf $(SUBMOD_DIR)/*

