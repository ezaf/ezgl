# OBJS specifies which files to compile for the project
OBJS = main.c ezwindow.c ezlog.c

# OUT specifies the name of the executable
OUT = debug

BUILD_DIR = ../build/
RESRC_DIR = ../resrc/
SOURCE_DIR = ../source/

# Find what OS we're on so we can better configure all the compiler options
# Linux->"Linux" | MacOS->"Darwin" | Windows->"MSYS_NT-#"
#UNAME = `(uname -s) 2>/dev/null`

# CC specifies which compiler we're using
CC = gcc

# Compiler and linker flags; include and library paths
# Must be C99 or newer because and older and SDL2 has compile errors
CF_UNIV = -std=c99 -pedantic -O3 -w
LF_UNIV = -lSDL2main -lSDL2 -lSDL2_image
INC_UNIV =
LIB_UNIV =

# All compiler flags can be customized on a per-platform basis
ifeq ($(OS),Windows_NT)
	# Uncomment "-Wl..." to remove console window on Windows OS
	CF = $(CF_UNIV) #-Wl,-subsystem,windows
	LF = -lmingw32 $(LF_UNIV)
	# lua modding support planned
	INC = $(INC_UNIV) -ID:\org\libsdl\include #-ID:\org\lua-5.3.4\src
	LIB = $(LIB_UNIV) -LD:\org\libsdl\lib #-ID:\org\lua-5.3.4\src
else
	CF = $(CF_UNIV)
	LF = $(LF_UNIV)
	INC = $(INC_UNIV)
	LIB = $(LIB_UNIV)
endif



all :
	make build
	make run

help :
	@echo
	@echo "TODO: describe make targets"
	@echo

clean :
	rm -f $(BUILD_DIR)*

build :
	make mk-dirs
	make cp-resrc
	make compile

mk-dirs :
	mkdir -p $(BUILD_DIR)
	mkdir -p $(RESRC_DIR)

cp-resrc :
	cp -R $(RESRC_DIR). $(BUILD_DIR)

compile : $(OBJS)
	$(CC) $(OBJS) $(INC) $(LIB) $(CF) $(LF) -o $(BUILD_DIR)$(OUT)

run :
	@cd $(BUILD_DIR) && echo && ./$(OUT) && echo && cd $(SOURCE_DIR)
#   At least on windows, this only plays nicely when it's on one line

