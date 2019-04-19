SIMPLE2D_BASE = simple2d
SDL2_BASE = simple2d/deps/macos/include/SDL2

NAME = lissajuice

INC_DIRS = $(SIMPLE2D_BASE)/include $(SDL2_BASE)/include $(SDL2_BASE)/include/SDL2
INC = $(foreach dir, $(INC_DIRS), -I$(dir))

THIS_ONES_SYMLINKED = -I/Volumes/ssd/nkirkby/.brew/include/SDL2
GOOD_GREEF = -I/Volumes/ssd/nkirkby/.brew/Cellar/sdl2/2.0.9_1/include

all: $(NAME)

$(NAME): *.c
	clang -v -I$(SDL2_BASE) -I$(SDL2_BASE)/../ -Isimple2d/include -lsimple2d  -D_THREAD_SAFE -L/Volumes/ssd/nkirkby/.brew/lib -lSDL2 -Wl,-framework,OpenGL -lSDL2_image -lSDL2_mixer -lSDL2_ttf $< -o $@
