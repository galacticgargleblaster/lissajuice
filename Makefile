SIMPLE2D_BASE = /nfs/2018/n/nkirkby/.brew/Cellar/simple2d/1.1.0
SDL2_BASE = /nfs/2018/n/nkirkby/.brew/Cellar/sdl2/2.0.9_1

NAME = lissajuice

INC_DIRS = $(SIMPLE2D_BASE)/include $(SDL2_BASE)/include $(SDL2_BASE)/include/SDL2
INC = $(foreach dir, $(INC_DIRS), -I$(dir))


all: $(NAME)

$(NAME): *.c
	$(CC) $(INC) -L$(SIMPLE2D_BASE)/lib -lsimple2d -L$(SDL2_BASE) -lsdl2 $^ -o $<
