/*
** EPITECH PROJECT, 2026
** Wolf3D
** File description:
** map_loading_utils
*/

#include "my.h"
#include "wolf3d.h"
#include <SFML/System/Vector2.h>
#include <stdio.h>
#include <string.h>

int check_size_validity(char *content, game_t *game)
{
    char **temp = my_str_to_word_array(content, "\n");
    int w_pos = check_elm_in_tokened_list(temp, "MAP_WIDTH", "=");
    int h_pos = check_elm_in_tokened_list(temp, "MAP_HEIGHT", "=");

    game->map_size = (sfVector2i){0, 0};
    if (w_pos < 0 || w_pos > 2 || h_pos < 0 || h_pos > 2) {
        printf("Error: Missing or misplaced MAP_WIDTH/HEIGHT.\n");
        free_array(temp);
        return (84);
    }
    game->map_size.x = get_number_value(temp[w_pos]);
    game->map_size.y = get_number_value(temp[h_pos]);
    free_array(temp);
    return (game->map_size.x <= 1 || game->map_size.y <= 1) ? 84 : 0;
}

static int check_string_validity(char *string, int y)
{
    for (int i = 0; string[i]; i++) {
        if (!is_char_in_string(string[i], AUTHORIZED_CHARS)) {
            printf("Invalid char at Y:%i X:%i\n", y + 1, i + 1);
            return (84);
        }
    }
    return (0);
}

static int map_error_handling(char **temp, game_t *game, int pos)
{
    if ((int)strlen(temp[pos + 2]) != game->map_size.x) {
        printf("Wrong size of line at line %i.\n", pos + 4);
        return (84);
    }
    return (check_string_validity(temp[pos + 2], pos));
}

int check_map_validity(char *cont, game_t *game)
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
