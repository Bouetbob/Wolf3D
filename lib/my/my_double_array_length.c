/*
** EPITECH PROJECT, 2025
** my_double_array_length
** File description:
** length of a double array instead of a string
*/

#include "my.h"
#include <stdlib.h>

int my_double_array_length(char **arr)
{
    int size = 0;

    if (arr == NULL)
        return (0);
    while (arr[size] != NULL)
        size++;
    return (size);
}
