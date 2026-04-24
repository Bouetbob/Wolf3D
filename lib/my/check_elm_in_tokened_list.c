/*
** EPITECH PROJECT, 2026
** check_elm_in_tokened_list
** File description:
** checks of a specific token is in a list, returns the line upon finding it
*/

#include "my.h"
#include <unistd.h>
#include <string.h>
#include <stdio.h>

int check_elm(char *to_check, char *word, char *sep)
{
    char **temp = NULL;

    temp = my_str_to_word_array(to_check, sep);
    for (int i = 0; i < my_double_array_length(temp); i++)
        if (strcmp(temp[0], word) == 0) {
            free_array(temp);
            return (i);
        }
    if (temp)
        free_array(temp);
    return (-1);
}

int check_elm_in_tokened_list(char **to_check, char *word, char *sep)
{
    int check = 0;

    for (int i = 0; i < my_double_array_length(to_check); i++) {
        check = check_elm(to_check[i], word, sep);
        if (check != -1)
            return i;
    }
    return (-1);
}
