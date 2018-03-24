# All source files to compile for the project
MY_SRC = main.c ezsdl/ezwindow.c ezsdl/ezlog.c

# All submodule source files to compile for the project
SUBMOD_SRC = parson/parson.c

# Name of the executable
OUT = debug



BUILD_DIR = bin
LIB_DIR = lib
INCLUDE_DIR = include
SUBMOD_DIR = submodules
SOURCE_DIR = src
ASSET_DIR = asset

# Add source directory to source file names
OBJS = $(foreach OBJ,$(MY_SRC),$(SOURCE_DIR)/$(OBJ)) $(foreach OBJ,$(SUBMOD_SRC),$(SUBMOD_DIR)/$(OBJ))

# Find what OS we're on so we can better configure all the compiler options
# Linux->"Linux" | MacOS->"Darwin" | Windows->"MSYS_NT-#"
#UNAME = `(uname -s) 2>/dev/null`

# CC specifies which compiler we're using
CC = gcc

# Compiler and linker flags; include and library paths
# Must be C99 or newer because and older and SDL2 has compile errors
CF_UNIV = -std=c99 -pedantic -O3 -w
LF_UNIV = -lSDL2main -lSDL2 -lSDL2_image
INC_UNIV = -I$(INCLUDE_DIR)
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



.PHONY : all
all :
	make build $(NPD)
	make run $(NPD)

.PHONY : docs
docs :
	doxygen .doxyfile
	$(OPEN) docs/index.html

.PHONY : help
help :
	@echo
	@echo "TODO: describe make targets"
	@echo

.PHONY : clean
clean :
	rm -f $(BUILD_DIR)*


.PHONY : build
build :
	make mk-dirs $(NPD)
	make submods $(NPD)
	make cp-deps $(NPD)
	make compile $(NPD)

.PHONY : mk-dirs
mk-dirs :
	mkdir -p $(BUILD_DIR)
	mkdir -p $(LIB_DIR)
	mkdir -p $(ASSET_DIR)

.PHONY : submods
submods :
	pushd $(SUBMOD_DIR) $(NULL) && ./import.sh 2$(NULL) && popd $(NULL)

.PHONY : cp-deps
cp-deps :
	cp -R $(LIB_DIR)/. $(BUILD_DIR)
	cp -R $(ASSET_DIR)/. $(BUILD_DIR)

.PHONY : compile
compile : $(OBJS)
	$(CC) $(OBJS) $(INC) $(LIB) $(CF) $(LF) -o $(BUILD_DIR)/$(OUT)

.PHONY : run
run :
	@echo && ./$(BUILD_DIR)/$(OUT) && echo



# Target aliases
.PHONY : bin/
bin / :
	make build $(NPD)

.PHONY : submodules/
submodules/ :
	make submods $(NPD)

.PHONY : docs/
docs/ :
	make docs $(NPD)
