/*
** EPITECH PROJECT, 2026
** check_word_in_list
** File description:
** it checks if a word is in a list, returns position, -1 if not in list
*/

#include "my.h"
#include <string.h>

int check_word_in_list(char **to_check, char *word)
{
    for (int i = 0; i < my_double_array_length(to_check); i++) {
        if (strcmp(to_check[i], word) == 0)
            return (i);
    }
    return (-1);
}
