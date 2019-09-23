##
## Makefile for libx in /home/aslafy_z/Lib/
##
## Made by Zadkiel Aslafy Aharonian
## Login   <aslafy_z@epitech.net>
##
## Started on  Mon Oct 21 11:21:36 2013 Zadkiel Aslafy Aharonian
## Last update Sat Jun  7 18:40:06 2014 Zadkiel Aslafy-Aharonian
##

SRC=	myx_cd.c \
	myx_draw_line.c \
	myx_flip.c \
	myx_image_blit.c \
	myx_image_create.c \
	myx_image_fill.c \
	myx_init.c \
	myx_init_image.c \
	myx_init_screen.c \
	myx_pixel_put.c \
	myx_pixel_get.c \
	myx_default_events.c \
	myx_open_win.c \
	myx_draw_rect.c \
	math/myx_sqrt.c \
	math/myx_isometry.c

OBJ=	$(SRC:.c=.o)

CFLAGS += -I . -O3

all:	$(OBJ)
	ar rc ../libmyx.a $(OBJ)
	ranlib ../libmyx.a
	cp myx.h ..
clean:
	rm -f $(OBJ)

re:	fclean all

fclean:	clean
	rm -f ../libmyx.a
	rm -f ../myx.h
