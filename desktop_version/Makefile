PRGNAME     = vvvvvv
CC			= $(CROSS_COMPILE)gcc
CXX			= $(CROSS_COMPILE)g++

SRCDIR		= ./src/ ./lodepng ./physfs ./tinyxml
VPATH		= $(SRCDIR)
SRC_C		= $(foreach dir, $(SRCDIR), $(wildcard $(dir)/*.c))
SRC_CP		= $(foreach dir, $(SRCDIR), $(wildcard $(dir)/*.cpp))
OBJ_C		= $(notdir $(patsubst %.c, %.o, $(SRC_C)))
OBJ_CP		= $(notdir $(patsubst %.cpp, %.o, $(SRC_CP)))
OBJS		= $(OBJ_C) $(OBJ_CP)

CFLAGS          = -O2 -DPHYSFS_SUPPORTS_DEFAULT=0 -DPHYSFS_SUPPORTS_ZIP=1 -DGAME_BITDEPTH=16 -DVVV_COMPILEMUSIC -DRETROFW
CFLAGS		+= -I./src/ -I./lodepng -I./physfs -I./tinyxml -I$(SYSROOT)/usr/include/SDL

LTO		= -flto=auto

CFLAGS		+= -I./src/ -I./lodepng -I./physfs -I./tinyxml $(SDL_CFLAGS) $(LTO)
CFLAGS		+= -fdata-sections -ffunction-sections -fno-PIC -fomit-frame-pointer
CXXFLAGS	= $(CFLAGS) -std=gnu++11
LDFLAGS     	= -nodefaultlibs -lc -lstdc++ -lgcc_eh -lgcc -lgcc_s -lm -lSDL -lSDL_image $(LTO)
LDFLAGS		+= -lSDL_ttf -ldl
LDFLAGS		+= -lz -lmad
LDFLAGS		+= -lts -lasound -lSDL_mixer -lvorbisidec -lvorbisfile -lvorbis -logg
LDFLAGS		+= -no-pie -Wl,--as-needed -Wl,--gc-sections

# Rules to make executable
$(PRGNAME): $(OBJS)  
	$(CC) $(CFLAGS) -o $(PRGNAME) $^ $(LDFLAGS)

$(OBJ_C) : %.o : %.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJ_CP) : %.o : %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f $(PRGNAME) *.o
