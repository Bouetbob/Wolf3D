/*
** EPITECH PROJECT, 2026
** get_amount_of_words
** File description:
** it gets the amount of words in a string
*/

#include "my.h"

int is_char_in_string(char c, char *string)
{
    int pos = 0;

    while (string[pos] != '\0') {
        if (string[pos] == c)
            return (1);
        pos++;
    }
    return (0);
}

int go_until_end(char *string, char *seps, int pos)
{
    while (is_char_in_string(string[pos], seps) == 0 && string[pos] != '\0')
        pos++;
    return pos;
}

int get_amount_of_words(char *string, char *seps)
{
    int words = 0;
    int pos = 0;

    while (string[pos] != '\0') {
        while (
            is_char_in_string(string[pos], seps) == 1 && string[pos] != '\0')
            pos++;
        if (string[pos] != '\0') {
            words++;
            pos = go_until_end(string, seps, pos);
        }
    }
    if (words == 0)
        return (-1);
    return (words);
}
