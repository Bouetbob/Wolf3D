##
## EPITECH PROJECT, 2025
## first makefile
## File description:
## idk what it does
##

SRC :=	main.c \
		color.c \
	
OBJ = $(SRC:%.c=%.o)

LIB	=	./lib/my
INCLUDE	=	./include

CC	:=	epiclang
CFLAGS	:=	-Wall -Wextra -I $(INCLUDE) -lm
CSFMLFLAGS	:=	-lcsfml-graphics -lcsfml-window -lcsfml-system

NAME = libmy.a
EXEC_NAME	=	wolf3d

TEMP  = src/*.o
TEMP2 = *~

all	:	$(NAME)	$(EXEC_NAME)

$(NAME)	:
	@$(MAKE) -C $(LIB)
	@$(MAKE) -C $(LIB) comp

$(EXEC_NAME)	:	$(OBJ)
	@$(CC) $(OBJ) -o $(EXEC_NAME) $(CFLAGS) -L. -lmy $(CSFMLFLAGS)

clean	:
	@$(MAKE) -C $(LIB) clean
	@rm -f $(TEMP2)
	@rm -f $(TEMP)

fclean	:
	@$(MAKE) -C $(LIB) fclean
	@rm -f $(EXEC_NAME)
	@rm -f $(OBJ)

re	: fclean all

.PHONY	: $(EXEC_NAME)
