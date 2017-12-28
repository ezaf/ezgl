#OBJS specifies which files to compile as part of the project
OBJS = main.cpp

BUILD_DIR = ../build
RESRC_DIR = ../resrc

#CC specifies which compiler we're using
CC = g++ -std=c++11 -O3

#INCLUDE_PATHS specifies the additional include paths we'll need
INCLUDE_PATHS = -ID:\org\libsdl\include -ID:\net\glew\include

#LIBRARY_PATHS specifies the additional library paths we'll need
LIBRARY_PATHS = -LD:\org\libsdl\lib -LD:\net\glew\lib\Release\Win32

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
#  # -Wl,-subsystem,windows gets rid of the console window
COMPILER_FLAGS_L = -w
COMPILER_FLAGS_W = -w -Wl,-subsystem,windows

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS_L = -lSDL2main -lSDL2
LINKER_FLAGS_W = -lmingw32 -lSDL2main -lSDL2


all : 
	echo '' && echo "Try \"make windows\" or \"make linux\"" && echo ''

windows:
	make mk_dirs && make windows_compile && make cp_resrc && make run

linux:
	make mk_dirs && make linux_compile && make cp_resrc && make run

windows_compile : $(OBJS)
		$(CC) $(OBJS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS_W) $(LINKER_FLAGS_W) -o $(BUILD_DIR)/debug

linux_compile: $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS_L) $(LINKER_FLAGS_L) -o $(BUILD_DIR)/debug


# Utilities
mk_dirs :
	mkdir $(BUILD_DIR) && mkdir $(RESRC_DIR)

cp_resrc :
	cp -R $(RESRC_DIR)/. $(BUILD_DIR)/

run :
	cd ../build && echo '' && ./debug && cd ../source

clean :
	rm -f $(BUILD_DIR)/*
