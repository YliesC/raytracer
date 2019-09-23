SRC=	my_atobi.c \
	my_strlowcase.c \
	my_strcpy.c \
	my_strlen.c \
	my_strdup.c \

LIB=	../libmy.a

OBJ=	$(SRC:.c=.o)

CFLAGS += -O3

all:	$(LIB)

$(LIB): $(OBJ)
	ar rc ../libmy.a $(OBJ)
	ranlib ../libmy.a
	cp my.h ../

clean:
	rm -f $(OBJ)

re:	fclean all

fclean:	clean
	rm -f ../my.h
	rm -f ../libmy.a
