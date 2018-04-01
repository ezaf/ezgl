# All source files to compile for the project
SOURCE = main.c ezwindow.c ezlog.c

# All submodule source files to compile for the project
SUBMOD_SOURCE = parson/parson.c

# All submodule include directories to compile for the project
SUBMOD_INCLUDE = parson

# Name of the executable
OUT = debug



BUILD_DIR = build
DOCS_DIR = docs
LIB_DIR = lib
INCLUDE_DIR = include
SUBMOD_DIR = submodule
SOURCE_DIR = src
ASSET_DIR = asset

# Add source directory to source file names
OBJS = $(foreach OBJ,$(SOURCE),$(SOURCE_DIR)/$(OBJ)) $(foreach OBJ,$(SUBMOD_SOURCE),$(SUBMOD_DIR)/$(OBJ))

# Find what OS we're on so we can better configure all the compiler options
# Linux->"Linux" | MacOS->"Darwin" | Windows->"MSYS_NT-#"
#UNAME = `(uname -s) 2>/dev/null`

# CC specifies which compiler we're using
CC = gcc

# Compiler and linker flags; include and library paths
# Must be C99 or newer because and older and SDL2 has compile errors
CF_UNIV = -std=c99 -pedantic -O3 -w
LF_UNIV = -lSDL2main -lSDL2 -lSDL2_image
INC_UNIV = -I$(INCLUDE_DIR) $(foreach DIR,$(SUBMOD_INCLUDE),-I$(SUBMOD_DIR)/$(DIR))
LIB_UNIV =

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
NULL = >/dev/null



.PHONY : all $(DOCS_DIR) rtd help clean clean-build clean-submod build dirs
.PHONY : deps submod compile run

all :
	make build $(NPD)
	make run $(NPD)

$(DOCS_DIR) :
	#doxygen .doxyfile
	rm -rf docs/*
	python $(SUBMOD_DIR)/mcss/doxygen/dox2html5.py .doxyfile-mcss
	cd docs
	rm -rf xml
	cd ..
	make rtd $(NPD)

# Read the docs (not referring to the website)
rtd :
	$(OPEN) docs/index.html

help :
	@echo
	@echo "TODO: describe make targets"
	@echo

clean :
	#make clean-submod $(NPD)
	make clean-build $(NPD)

clean-build :
	rm -rf $(BUILD_DIR)/*

clean-submod :
	rm -rf $(SUBMOD_DIR)/*

build :
	make dirs $(NPD)
	make deps $(NPD)
	make submods $(NPD)
	make compile $(NPD)

dirs :
	mkdir -p $(BUILD_DIR)
	mkdir -p $(LIB_DIR)
	mkdir -p $(ASSET_DIR)

# Copy dependencies for build
deps :
	cp -R $(LIB_DIR)/. $(BUILD_DIR)
	cp -R $(ASSET_DIR)/. $(BUILD_DIR)

submod :
	git submodule init
	git submodule update

compile : $(OBJS)
	$(CC) $(OBJS) $(INC) $(LIB) $(CF) $(LF) -o $(BUILD_DIR)/$(OUT)

run :
	@echo && ./$(BUILD_DIR)/$(OUT) && echo
