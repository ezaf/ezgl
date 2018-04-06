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
CF = -std=c99 -pedantic -O3 -w
LF = -lSDL2main -lSDL2 -lSDL2_image
INC = -I$(INC_DIR) \
		   $(foreach DIR,$(EXT_INC_DIR),-I$(EXT_DIR)/$(DIR))
LIB =

# Find what OS we're on so we can better configure all the compiler options
# Linux->"Linux" | MacOS->"Darwin" | Windows->"MSYS_NT-#"
#UNAME = `(uname -s) 2>/dev/null`

# All compiler flags can be customized on a per-platform basis
ifeq ($(OS),Windows_NT)
	# Uncomment "-Wl..." to remove console window on Windows OS
	CF += #-Wl,-subsystem,windows
	# -lmingw32 must come before all else
	LF_TEMP := $(LF)
	LF = -lmingw32 $(LF_TEMP)
	# lua modding support planned
	INC += -ID:/org/libsdl/include #-ID:/org/lua/src
	LIB += -LD:/org/libsdl/lib #-ID:/org/lua/src
	OPEN = cmd //c start "${@//&/^&}"
else
	CF +=
	LF +=
	INC +=
	LIB +=
	OPEN = xdg-open
endif

# Figure out what commands are valid
PY = $(shell echo "quit()">tmp.py && python3 test.py >/dev/null \
	 && rm tmp.py && echo python3 || rm tmp.py && echo python)

# TODO: https://stackoverflow.com/a/34756868/5890633
ifeq ($(shell uname -s | grep -E _NT), 0)
	MSG = "PRECODE"
endif

NPD = --no-print-directory



.PHONY : all $(BLD_DIR) run dirs deps $(EXT_DIR) $(DOC_DIR) rtd
.PHONY : compile help clean clean-$(BLD_DIR) clean-$(EXT_DIR)

all :
	make $(DOC_DIR) $(NPD)
	make $(BLD_DIR) $(NPD)
	make run $(NPD)

help :
	@echo $(shell uname -s)
	@echo $(MSG)
	@if [[ `uname -s | grep -E _NT` ]]; then \
		echo "BASHCODE"; \
	fi
	@echo
	@echo "TODO: describe make targets"
	@echo

$(DOC_DIR) :
	mkdir -p $(DOC_DIR)
	make clean-$(DOC_DIR) $(NPD)
	make $(EXT_DIR) $(NPD)
	@# m.css requires python 3.6+ and doxygen 1.8.14+
	@if [[ `$(PY) --version | grep -E "\b3\.[^0-5]"` && \
		`doxygen --version | grep -E "\b1.[^0-7].((1[^0-3])|(2.*))"` ]]; then \
		$(PY) $(EXT_DIR)/m.css/doxygen/dox2html5.py .doxyfile-mcss; \
		cp $(EXT_DIR)/m.css/css/m-dark+doxygen.compiled.css \
			$(DOC_DIR)/m-dark+doxygen.compiled.css; \
	else \
		doxygen .doxyfile; \
	fi
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

