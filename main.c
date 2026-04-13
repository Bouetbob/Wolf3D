/*
** EPITECH PROJECT, 2026
** wolf3D
** File description:
** main file
*/

#include "my.h"

int main(int ac, char **av, char **env)
{
    if (ac != 2 || !my_file_exists(av[1]) ||
        check_elm_in_tokened_list(env, "DISPLAY", "=") == -1)
        return (84);
    return (0);
}
