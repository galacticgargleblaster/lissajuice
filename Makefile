SIMPLE2D_BASE = simple2d
SDL2_BASE = simple2d/deps/macos/include/SDL2

NAME = lissajuice

INC_DIRS = $(SDL2_BASE) $(SDL2_BASE)/../ $(SIMPLE2D_BASE)/include liblist
INC = $(foreach dir, $(INC_DIRS), -I$(dir))

LIB_DIRS = /Volumes/ssd/nkirkby/.brew/lib liblist
LIB = $(foreach dir, $(LIB_DIRS), -L$(dir))

all: $(NAME) deps

deps:
	make -C liblist

$(NAME): *.c 
	clang $(INC) $(LIB) -llist -lsimple2d -D_THREAD_SAFE -lSDL2 -Wl,-framework,OpenGL -lSDL2_image -lSDL2_mixer -lSDL2_ttf $< -o $@

run: $(NAME)
	./$(NAME)