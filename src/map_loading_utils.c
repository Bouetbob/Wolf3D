/*
** EPITECH PROJECT, 2026
** Wolf3D
** File description:
** map_loading_utils
*/

#include "my.h"
#include <SFML/System/Vector2.h>
#include <stdio.h>
#include "wolf3d.h"
#include <string.h>

int check_size_validity(char *content, game_t *game)
{
    char **temp = my_str_to_word_array(content, "\n");
    int width_pos = check_elm_in_tokened_list(temp, "MAP_WIDTH", "=");
    int height_pos = check_elm_in_tokened_list(temp, "MAP_HEIGHT", "=");

    game->map_size = (sfVector2i) {0, 0};
    if (width_pos == -1 || width_pos > 2 || height_pos == -1
        || height_pos > 2) {
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

static int check_string_validity(char *string, int y)
{
    for (int i = 0; i < (int) strlen(string); i++) {
        if (!is_char_in_string(string[i], AUTHORIZED_CHARS)) {
            printf("Unsupported character found.\n");
            printf("Invalid character position:\nY=%i\tX=%i\n", y + 1, i + 1);
            printf("Invalid character: %c\n", string[i]);
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
    if (check_string_validity(temp[pos + 2], pos) == 84)
        return (84);
    return (0);
}

int check_map_validity(char *cont, game_t *game)
{
    char **temp = my_str_to_word_array(cont, "\n");

    game->map = NULL;
    if (my_double_array_length(temp) != 3 + game->map_size.y) {
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

bool check_input_validity(char *string, game_t *game)
{
    char **temp = my_str_to_word_array(string, "\t= ");
    int num1 = 0;
    int num2 = 0;

    if (my_double_array_length(temp) != 4) {
        free_array(temp);
        return (false);
    }
    num1 = atoi(temp[1]);
    num2 = atoi(temp[3]);
    free_array(temp);
    if (num1 <= 0 || num1 >= game->map_size.x || num2 <= 0
        || num2 >= game->map_size.y || game->map[num2][num1] != '0') {
        printf("\nInvalid position.\n");
        return (false);
    }
    game->player->pos.x = num1;
    game->player->pos.y = num2;
    return (true);
}
