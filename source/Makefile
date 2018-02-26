# OBJS specifies which files to compile for the project
OBJS = main.c ezwindow.c ezlog.c

# OUT specifies the name of the executable
OUT = debug

BUILD_DIR = ../build/
RESRC_DIR = ../resrc/
SOURCE_DIR = ../source/

# CC specifies which compiler we're using
CC = gcc

# CF specifies universal/cross-platform compiler flags
CF = -std=c89 -pedantic-errors -O3 -I

# CF_X specifies platform-specific compiler flags
# "-w" suppresses all warnings; "-Wall" shows all warnings
# "-Wl,-subsystem,windows" gets rid of the console window on windows os
CF = -w
CF_LINUX = $(CF)
CF_WINDOWS = $(CF) #-Wl,-subsystem,windows

# INC_PATHS specifies include paths
INC_PATHS = -ID:\org\libsdl\include -ID:\org\lua-5.3.4\src

# LIB_PATHS specifies library paths
LIB_PATHS = -LD:\org\libsdl\lib -ID:\org\lua-5.3.4\src

# LF_X specifies platform-specific libraries
LF = -lSDL2main -lSDL2 -lSDL2_image
LF_LINUX = $(LF)
LF_WINDOWS = -lmingw32 $(LF)

# TODO: add mac support


all : 
	@echo
	@echo "Try \"make windows\" or \"make linux\""
	@echo

windows:
	make mk-dirs
	make windows-compile
	make cp-resrc
	make run

linux:
	make mk-dirs
	make linux-compile
	make cp-resrc
	make run

windows-compile : $(OBJS)
	$(CC) $(OBJS) $(INC_PATHS) $(LIB_PATHS) $(CF_WINDOWS) $(LF_WINDOWS) -o $(BUILD_DIR)$(OUT)

linux-compile: $(OBJS)
	$(CC) $(OBJS) $(CF_LINUX) $(LF_LINUX) -o $(BUILD_DIR)$(OUT)


# Utilities
mk-dirs :
	mkdir -p $(BUILD_DIR)
	mkdir -p $(RESRC_DIR)

cp-resrc :
	cp -R $(RESRC_DIR). $(BUILD_DIR)

run :
	@cd $(BUILD_DIR) && echo && ./debug && echo && cd $(SOURCE_DIR)
#   At least on windows, this only plays nicely when it's on one line

clean :
	rm -f $(BUILD_DIR)*
