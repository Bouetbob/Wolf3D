/*
** EPITECH PROJECT, 2025
** my
** File description:
** idk what to type here its litteraly just my
*/

#include <stdbool.h>
#include <stdlib.h>

#ifndef MY_H_
    #define MY_H_


int is_char_in_string(char c, char *string);
char **my_str_to_word_array(char *string, char *separators);
bool my_file_exists(const char *file);
int my_double_array_length(char **arr);
void free_array(char **array);
int get_amount_of_words(char *string, char *seps);
int go_until_end(char *string, char *seps, int pos);
int check_word_in_list(char **to_check, char *word);
int check_elm_in_tokened_list(char **to_check, char *word, char *sep);

#endif /* MY_H_ */
