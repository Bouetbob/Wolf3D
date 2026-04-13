/*
** EPITECH PROJECT, 2025
** my_str_to_word_array
** File description:
** str but now its array
*/

#include "my.h"
#include <stdio.h>
#include <stdlib.h>

int get_word(char **arr, char *string, int pos, char *seps)
{
    int arr_pos = 0;
    int buff_pos = 0;
    char *buffer =
        malloc(sizeof(char) * (go_until_end(string, seps, pos) - pos + 1));

    if (!buffer)
        return -1;
    while (string[pos] != '\0' && is_char_in_string(string[pos], seps) == 0) {
        buffer[buff_pos] = string[pos];
        buff_pos++;
        pos++;
    }
    while (arr[arr_pos] != NULL)
        arr_pos++;
    buffer[buff_pos] = '\0';
    arr[arr_pos] = my_strdup(buffer);
    free(buffer);
    return (0);
}

int place_words_into_array(char **arr, char *string, char *seps)
{
    int pos = 0;

    while (string[pos] != '\0') {
        while (
            is_char_in_string(string[pos], seps) == 1 && string[pos] != '\0')
            pos++;
        if (is_char_in_string(string[pos], seps) == 0) {
            get_word(arr, string, pos, seps);
            pos = go_until_end(string, seps, pos);
        }
    }
    return (0);
}

int init_arr(char **arr, int amt)
{
    for (int i = 0; i < amt; i++)
        arr[i] = NULL;
    return (0);
}

char **my_str_to_word_array(char *string, char *separators)
{
    int word_amount = get_amount_of_words(string, separators);
    char **array = malloc(sizeof(char *) * (word_amount + 1));

    if (!array)
        return NULL;
    init_arr(array, word_amount);
    place_words_into_array(array, string, separators);
    array[word_amount] = NULL;
    return (array);
}
