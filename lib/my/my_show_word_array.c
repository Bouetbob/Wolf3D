/*
** EPITECH PROJECT, 2025
** my_show_word_array
** File description:
** my show word but its now an array
*/

#include "my.h"
#include <stdio.h>

int my_show_word_array(char *const *tab)
{
    for (int i = 0; tab[i] != 0; i++) {
        printf("%s\n", tab[i]);
    }
    return (0);
}
