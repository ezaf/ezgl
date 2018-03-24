# FILES specifies which files to compile for the project
FILES = main.c ezwindow.c ezlog.c

# OUT specifies the name of the executable
OUT = debug

BUILD_DIR = bin/
LIB_DIR = lib/
INCLUDE_DIR = include/
SOURCE_DIR = src/
ASSET_DIR = asset/

# Add source directory to source file names
OBJS = $(foreach OBJ,$(FILES),$(SOURCE_DIR)$(OBJ))

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
	INC = $(INC_UNIV) -ID:\org\libsdl\include #-ID:\org\lua-5.3.4\src
	LIB = $(LIB_UNIV) -LD:\org\libsdl\lib #-ID:\org\lua-5.3.4\src
	OPEN = cmd //c start "${@//&/^&}"
else
	CF = $(CF_UNIV)
	LF = $(LF_UNIV)
	INC = $(INC_UNIV)
	LIB = $(LIB_UNIV)
endif



all :
	make build --no-print-directory
	make run --no-print-directory

doxy :
	doxygen .doxyfile

help :
	@echo
	@echo "TODO: describe make targets"
	@echo

clean :
	rm -f $(BUILD_DIR)*

build :
	make mk-dirs --no-print-directory
	make cp-resrc --no-print-directory
	make compile --no-print-directory

mk-dirs :
	mkdir -p $(BUILD_DIR)
	mkdir -p $(LIB_DIR)
	mkdir -p $(ASSET_DIR)

cp-resrc :
	cp -R $(LIB_DIR). $(BUILD_DIR)
	cp -R $(ASSET_DIR). $(BUILD_DIR)

compile : $(OBJS)
	$(CC) $(OBJS) $(INC) $(LIB) $(CF) $(LF) -o $(BUILD_DIR)$(OUT)

run :
	@echo && ./$(BUILD_DIR)$(OUT) && echo
#   At least on windows, this only plays nicely when it's on one line

