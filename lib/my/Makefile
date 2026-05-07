##
## EPITECH PROJECT, 2025
## first makefile
## File description:
## idk what it does
##

# Variables
NAME 	=	libmy.a

SRC_DIR	=	./

SRC	=	my_show_word_array.c \
		my_double_array_length.c \
		free_array.c \
		get_amount_of_words.c \
		check_word_in_list.c \
		check_elm_in_tokened_list.c \
		my_str_to_word_array.c \
		find_char.c \
		get_file_cont.c \
		



OBJS 	= 	$(SRC:%.c=%.o)

PATH_ROOT	=	../..

INC_PATH	=	./../../include

TEMP_FILES	=	$(OBJS)

H_NAME	=	my.h

# Compiler settings
CC = epiclang
CFLAGS = -Wall -Werror -I$(INC_PATH)

# Targets
all: $(NAME)

$(NAME):$(SRC)
	@$(CC) $(CFLAGS) -c $<

comp: 	$(OBJS)
	@ar rc $(NAME) $(OBJS)
	@cp $(NAME) $(PATH_ROOT)
	@mkdir -p $(INC_PATH)
	@cp $(H_NAME) $(INC_PATH)

clean:
	@echo "deleting temp files..."
	@rm -rf $(TEMP_FILES)
	@echo "deleted temp files"

fclean:	clean
	@rm $(INC_PATH)/$(H_NAME)
	@echo "removed includes"
	@cp $(H_NAME) $(INC_PATH)
	@echo "remade includes"

re:	fclean all

