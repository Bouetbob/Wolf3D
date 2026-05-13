##
## EPITECH PROJECT, 2025
## first makefile
## File description:
## idk what it does
##

SRC :=	src/main.c \
		src/color.c \
		src/init_game.c \
		src/movement.c \
		src/utils.c \
		src/events.c \
		src/cleanup.c \
		src/raycasting/raycasting.c \
		src/raycasting/raycasting_helper.c \
		src/buttons/draw_buttons.c \
		src/buttons/init_buttons.c \
		src/buttons/event_buttons.c \
		src/map/map_loading.c \
		src/map/map_saving.c \
		src/map/map_loading_utils.c \
		src/ui/change_menu_state.c \
		src/enemies/ai.c \
		src/enemies/init_enemy.c \
		src/enemies/weapons/magnum.c \
		src/enemies/weapons/thompson.c \
		src/enemies/render_enemies.c \
		src/items/draw_items.c \
		src/items/init_items.c \
		src/items/item_utils.c \
		src/map_saving.c \
		src/items/bomb.c \


	


OBJ = $(SRC:%.c=%.o)

LIB	=	./lib/my
INCLUDE	=	./include

CC	:=	epiclang
CFLAGS	:=	-Wall -Wextra -I $(INCLUDE) -g
CSFMLFLAGS	:=	-lcsfml-graphics -lcsfml-window -lcsfml-system
LIBS_TO_LINK	:=	$(CSFMLFLAGS) -lm -L. -lmy

LIB_NAME = libmy.a
EXEC_NAME	=	wolf3d

TEMP  = src/*.o
TEMP2 = *~

all : build_lib $(EXEC_NAME)

build_lib :
	@$(MAKE) -C $(LIB)
	@$(MAKE) -C $(LIB) comp

$(EXEC_NAME) : $(OBJ)
	@$(CC) $(OBJ) -o $(EXEC_NAME) $(LIBS_TO_LINK)

clean	:
	@$(MAKE) -C $(LIB) clean
	@rm -f $(TEMP2)
	@rm -f $(TEMP)

fclean	:
	@$(MAKE) -C $(LIB) fclean
	@rm -f $(EXEC_NAME)
	@rm -f $(OBJ)
	@rm -f $(LIB_NAME)

re	: fclean all

.PHONY	: all build_lib clean fclean re
