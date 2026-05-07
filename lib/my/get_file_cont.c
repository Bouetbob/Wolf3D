/*
** EPITECH PROJECT, 2026
** get_file_cont
** File description:
** returns the content of a file
*/

#include "my.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>

char *get_file_cont(char *file)
{
    FILE *fd = fopen(file, "r");
    struct stat *s = malloc((sizeof(struct stat)));
    char *temp = NULL;

    if (!fd || !s)
        return (NULL);
    stat(file, s);
    temp = malloc(sizeof(char) * s->st_size + 1);
    if (!temp)
        return (NULL);
    fread(temp, 1, s->st_size, fd);
    temp[s->st_size] = '\0';
    return (temp);
}
