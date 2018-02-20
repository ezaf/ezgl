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
CF = -std=c89 -O3 -I

# INC_PATHS specifies include paths
INC_PATHS = -ID:\org\libsdl\include\SDL2 -ID:\org\lua-5.3.4\src

# LIB_PATHS specifies library paths
LIB_PATHS = -LD:\org\libsdl\lib -ID:\org\lua-5.3.4\src

# CF_X specifies platform-specific compiler flags
# "-w" suppresses all warnings
# "-Wl,-subsystem,windows" gets rid of the console window
CF = -w
CF_L = $(CF)
CF_W = $(CF) #-Wl,-subsystem,windows

# LF_X specifies platform-specific libraries
LF = -lSDL2main -lSDL2 -lSDL2_image
LF_L = $(LF)
LF_W = -lmingw32 $(LF)

# TODO: add mac support


all : 
	@echo
	@echo "Try \"make windows\" or \"make linux\""
	@echo

windows:
	make mk_dirs
	make windows_compile
	make cp_resrc
	make run

linux:
	make mk_dirs
	make linux_compile
	make cp_resrc
	make run

windows_compile : $(OBJS)
	$(CC) $(OBJS) $(INC_PATHS) $(LIB_PATHS) $(CF_W) $(LF_W) -o $(BUILD_DIR)$(OUT)

linux_compile: $(OBJS)
	$(CC) $(OBJS) $(CF_L) $(LF_L) -o $(BUILD_DIR)$(OUT)


# Utilities
mk_dirs :
	mkdir -p $(BUILD_DIR)
	mkdir -p $(RESRC_DIR)

cp_resrc :
	cp -R $(RESRC_DIR). $(BUILD_DIR)

run :
	@cd $(BUILD_DIR) && echo && ./debug && echo && cd $(SOURCE_DIR)
	# At least on windows, this only plays nicely when it's on one line

clean :
	rm -f $(BUILD_DIR)*
