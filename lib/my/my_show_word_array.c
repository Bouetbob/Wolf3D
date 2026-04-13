/*
** EPITECH PROJECT, 2025
** my_show_word_array
** File description:
** my show word but its now an array
*/

#include "my.h"

int my_show_word_array(char *const *tab)
{
    for (int i = 0; tab[i] != 0; i++) {
        my_putstr(tab[i]);
        my_putchar('\n');
    }
    return (0);
}
