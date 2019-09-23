##
## Makefile for libx in /home/aslafy_z/Lib/
##
## Made by Zadkiel Aslafy Aharonian
## Login   <aslafy_z@epitech.net>
##
## Started on  Mon Oct 21 11:21:36 2013 Zadkiel Aslafy Aharonian
## Last update Wed Jun  4 16:41:37 2014 Zadkiel Aslafy-Aharonian
##

SRC=	parson.c

OBJ=	$(SRC:.c=.o)

CFLAGS += -I . -O3

all:	$(OBJ)
	ar rc ../libparson.a $(OBJ)
	ranlib ../libparson.a
	cp parson.h ..

clean:
	rm -f $(OBJ)

re:	fclean all

fclean:	clean
	rm -f ../libparson.a
	rm -f ../parson.h
