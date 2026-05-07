/*
** EPITECH PROJECT, 2026
** find_char
** File description:
** it finds a character in a string and returns its position
*/

#include "my.h"

int find_char(char c, char *string)
{
    int pos = 0;

    if (string[pos] == '\0')
        return false;
    while (string[pos] != '\0') {
        if (string[pos] == c)
            return (pos);
        pos++;
    }
    return (-1);
}
