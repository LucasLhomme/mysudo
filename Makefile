##
## EPITECH PROJECT, 2024
## Makefile Root
## File description:
## MakeFile dans le fichier root
##

NAME = my_sudo
DEBUG = -g
CFLAGS += -Wall -Wextra -W -Iinclude -Isrc/lib/include

SRC =	./src/my_sudo.c \
		./src/parse_file.c \
		./src/check_group.c \
		./src/check_command.c

OBJ  	=	 $(SRC:.c=.o)


all: 	$(NAME)
		$(MAKE) clean

$(NAME):	$(OBJ)
		$(MAKE) -C src/lib all
		gcc $(CFLAGS) -o $(NAME) $(OBJ) libmy.a -lcrypt
		rm libmy.a

clean || clear:
		$(MAKE) -C src/lib clean
		rm -f $(OBJ)

fclean:
		rm -f $(NAME) debug $(OBJ) libmy.a

re:
		$(MAKE) fclean
		$(MAKE) all
		$(MAKE) clean

debug: 	$(DEBUG)

$(DEBUG):	$(OBJ)
		$(MAKE) -C src/lib all
		gcc -g $(CFLAGS) -o debug $(OBJ) libmy.a

redebug:
		$(MAKE) fclean
		$(MAKE) debug
