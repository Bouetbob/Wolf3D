/*
** EPITECH PROJECT, 2025
** free_array
** File description:
** it frees double arrays
*/

#include <stdio.h>
#include <stdlib.h>

void free_array(char **array)
{
    for (int i = 0; array[i] != NULL; i++)
        free(array[i]);
    free(array);
}
