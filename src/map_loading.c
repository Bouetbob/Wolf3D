/*
** EPITECH PROJECT, 2026
** wolf3d
** File description:
** map loading file
*/

#include "engine.h"
#include "my.h"
#include <SFML/System/Vector2.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

static int get_number_value(char *string)
{
    int res = 0;
    char **tmp = my_str_to_word_array(string, "=");

    if (my_double_array_length(tmp) != 2) {
        printf("Not even going to try without %s.\n", tmp[0]);
        return (-1);
    }
    res = atoi(tmp[1]);
    free_array(tmp);
    return res;
}

static int check_size_validity(char *content, game_t *game)
{
    char **temp = my_str_to_word_array(content, "\n");
    int width_pos = check_elm_in_tokened_list(temp, "MAP_WIDTH", "=");
    int height_pos = check_elm_in_tokened_list(temp, "MAP_HEIGHT", "=");

    game->map_size = (sfVector2i) {0, 0};
    if (width_pos == -1 || width_pos > 2 ||
        height_pos == -1 || height_pos > 2) {
        printf("Wrong MAP_WIDTH or MAP_HEIGHT position.\n");
        return (84);
    }
    game->map_size.x = get_number_value(temp[width_pos]);
    game->map_size.y = get_number_value(temp[height_pos]);
    if (game->map_size.x <= 1 || game->map_size.y <= 1) {
        printf("Invalid map formatting.\n");
        return (84);
    }
    free_array(temp);
    return (0);
}

static int check_string_validity(char *string)
{
    for (int i = 0; i < (int) strlen(string); i++) {
        if (!is_char_in_string(string[i], AUTHORIZED_CHARS)) {
            printf("Wrong character found.\n");
            return (84);
        }
    }
    return (0);
}

static int map_error_handling(char **temp, game_t *game, int pos)
{
    if ((int) strlen(temp[pos + 2]) != game->map_size.x) {
        printf("Wrong size of line at line %i.\n", pos + 4);
        return (84);
    }
    if (check_string_validity(temp[pos + 2]) == 84)
        return (84);
    return (0);
}

static int check_map_validity(char *cont, game_t *game)
{
    char **temp = my_str_to_word_array(cont, "\n");

    game->map = NULL;
    if (my_double_array_length(temp) < 2 + game->map_size.y) {
        printf("Invalid amount of lines.\n");
        return (84);
    }
    game->map = malloc(sizeof(char *) * (game->map_size.y + 1));
    if (!game->map)
        return (84);
    for (int i = 0; i < game->map_size.y; i++) {
        if (map_error_handling(temp, game, i) == 84)
            return (84);
        game->map[i] = strdup(temp[i + 2]);
    }
    game->map[game->map_size.y] = NULL;
    free_array(temp);
    return (0);
}

int map_filler(game_t *game, char *filename)
{
    FILE *fd = fopen(filename, "r");
    struct stat *s = malloc((sizeof(struct stat)));
    char *temp = NULL;

    if (!fd || !s)
        return (84);
    stat(filename, s);
    temp = malloc(sizeof(char) * s->st_size + 1);
    if (!temp)
        return (84);
    fread(temp, 1, s->st_size, fd);
    temp[s->st_size] = '\0';
    if (check_size_validity(temp, game) == 84)
        return (84);
    free(s);
    if (check_map_validity(temp, game) == 84)
        return (84);
    free(temp);
    fclose(fd);
    return (0);
}
