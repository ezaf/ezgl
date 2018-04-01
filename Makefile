# All source files to compile for the project
SOURCE = main.c ezwindow.c ezlog.c

# All submodule source files to compile for the project
SUBMOD_SOURCE = parson/parson.c

# All submodule include directories to compile for the project
SUBMOD_INCLUDE = parson

# Name of the executable
OUT = debug



ASSET_DIR = asset
BUILD_DIR = build
DOCS_DIR = docs
INCLUDE_DIR = include
LIB_DIR = lib
SOURCE_DIR = src
SUBMOD_DIR = submod

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



.PHONY : all $(BUILD_DIR) run dirs deps $(SUBMOD_DIR) $(DOCS_DIR) rtd compile
.PHONY : help clean clean-$(BUILD_DIR) clean-$(SUBMOD_DIR)

all :
	make $(DOCS_DIR) $(NPD)
	make $(BUILD_DIR) $(NPD)
	make run $(NPD)

$(BUILD_DIR) :
	make dirs $(NPD)
	make deps $(NPD)
	make $(SUBMOD_DIR) $(NPD)
	make compile $(NPD)

run :
	@echo && ./$(BUILD_DIR)/$(OUT) && echo

dirs :
	mkdir -p $(BUILD_DIR)
	mkdir -p $(LIB_DIR)
	mkdir -p $(ASSET_DIR)

# Copy dependencies for build
deps :
	cp -R $(LIB_DIR)/. $(BUILD_DIR)
	cp -R $(ASSET_DIR)/. $(BUILD_DIR)

$(SUBMOD_DIR) :
	git submodule init
	git submodule update

$(DOCS_DIR) :
	make clean-$(DOCS_DIR) $(NPD)
	python3 $(SUBMOD_DIR)/mcss/doxygen/dox2html5.py .doxyfile-mcss
	cd $(DOCS_DIR)
	rm -rf xml
	cd ..
	make rtd $(NPD)

# Read the docs (not referring to the website)
rtd :
	$(OPEN) docs/index.html

compile : $(OBJS)
	$(CC) $(OBJS) $(INC) $(LIB) $(CF) $(LF) -o $(BUILD_DIR)/$(OUT)

help :
	@echo
	@echo "TODO: describe make targets"
	@echo

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

