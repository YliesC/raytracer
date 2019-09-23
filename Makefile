NAME =	rt
EDITOR = editor

CC =	gcc

RM =	rm -f

PWD =	$(shell pwd)
QTV  =  $(shell sh src/editor/checkqt.sh)

LIBFLD = lib

EDITORFLD = src/editor
CFLAGS += -Wall -Werror -Wextra -Wno-unused-parameter
CFLAGS += -O3 -D_GNU_SOURCE
CFLAGS += -I inc/ -I $(LIBFLD)/

LDFLAGS =  -L $(LIBFLD) -lmy -lmyx -lparson -pthread
LDFLAGS += -L /usr/lib -lmlx -lm
LDFLAGS += -lXext -lX11

LIBS =	$(LIBFLD)/libmy.a \
	$(LIBFLD)/libmyx.a \
	$(LIBFLD)/libparson.a

SRCS =	src/misc/freetab.c \
	src/misc/puterr.c \
	src/misc/getpos.c \
	src/shapes/plane.c \
	src/free.c \
	src/shapes/hyperboloid.c \
	src/shapes/cylinder.c \
	src/shapes/sphere.c \
	src/shapes/cone.c \
	src/lists/o_shapes.c \
	src/lists/o_mods.c \
	src/lists/cams.c \
	src/lists/mods.c \
	src/lists/objects.c \
	src/lists/lights.c \
	src/export/bmp_save.c \
	src/export/bmp_create.c \
	src/export/bmp.c \
	src/mods/chess.c \
	src/mods/light.c \
	src/mods/reflexion.c \
	src/mods/shadow.c \
	src/mods/shining.c \
	src/mods/filter_neg.c \
	src/mods/filter_gray.c \
	src/init.c \
	src/render.c \
	src/parser/parse.c \
	src/parser/config.c \
	src/parser/lights.c \
	src/parser/objects.c \
	src/parser/mods.c \
	src/main.c \
	src/compute.c \
	src/math/translate.c \
	src/math/color.c \
	src/math/rotate.c \
	src/math/solver/solve_diff.c \
	src/math/solver/solve_three.c \
	src/math/solver/solve_init.c \
	src/math/solver/solve_two.c \
	src/math/vector.c \
	src/events.c \
	src/loading.c \
	src/events2.c \
	src/args.c \
	src/thread.c

OBJS = 	$(SRCS:.c=.o)

all:	$(LIBS) $(NAME) $(EDITOR)

$(LIBS):
	make -C $(LIBFLD)/

$(EDITOR):
ifeq ($(QTV),0)
	cd $(EDITORFLD)/ && qmake editor.pro -r -spec linux-g++
	make -C $(EDITORFLD)/
else
	@echo "You need Qt5 to compile the editor."
endif

$(NAME):$(OBJS)
	$(CC) $(OBJS) -o $(NAME) $(LDFLAGS)

clean:
	make -C $(LIBFLD) clean
	$(RM) $(OBJS)
ifeq ($(QTV),0)
	cd $(EDITORFLD)/ && qmake editor.pro -r -spec linux-g++
	make -C $(EDITORFLD) clean
endif

fclean:	clean
	rm -f $(LIBFLD)/my.h
	rm -f $(LIBFLD)/libmy.a
	rm -f $(LIBFLD)/myx.h
	rm -f $(LIBFLD)/libmyx.a
	rm -f $(LIBFLD)/parson.h
	rm -f $(LIBFLD)/libparson.a
	$(RM) $(NAME)
	rm -f $(EDITORFLD)/Makefile
	rm -f $(EDITOR)

re:	fclean all

.PHONY:
	all clean fclean re
