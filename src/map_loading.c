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
#include <time.h>

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

static int check_map_validity(char *cont, game_t *game)
{
    char **temp = my_str_to_word_array(cont, "\n");

    game->map = NULL;
    if (my_double_array_length(temp) != 2 + game->map_size.y) {
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

static int map_filler(game_t *game, char *filename)
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

static bool check_input_validity(char *string, game_t *game)
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
    printf("%i %i\n", num1, num2);
    return (true);
}

static int get_user_player_pos_input(game_t *game)
{
    bool valid_pos = false;
    char *temp = NULL;
    size_t size = 0;

    while (!valid_pos) {
        printf("Map size: x=%i\ty=%i\n", game->map_size.x, game->map_size.y);
        printf("Format: x=?\ty=?\nReplace ? by a value of your");
        printf(" choice.\nInput \"EXIT\" if you want to exit.\n");
        getline(&temp, &size, stdin);
        if (strcmp(temp, "exit\n") == 0)
            exit(0);
        valid_pos = check_input_validity(temp, game);
        if (valid_pos)
            break;
        printf("Invalid format or values.\nRetry.\n\n");
    }
    printf("Valid values entered.\nPlease proceed to the game.\n");
    return (0);
}

static int get_char_pos(char *string, char c)
{
    for (int i = 0; string[i]; i++) {
        if (string[i] == c)
            return (i);
    }
    return (-1);
}

static int check_player_in_map(char **map, game_t *game)
{
    int player_count = 0;

    for (int i = 0; i < my_double_array_length(map); i++) {
        if (is_char_in_string('P', map[i])) {
            game->player->pos.y = i;
            player_count++;
        }
    }
    if (player_count == 0) {
        printf("Missing player.\n");
        return (get_user_player_pos_input(game));
    }
    if (player_count > 1) {
        printf("Too many player starting points.\n");
        return (84);
    }
    game->player->pos.x = get_char_pos(map[(int) game->player->pos.y], 'P');
    return (0);
}

int load_map_from_file(game_t *game, char *file)
{
    if (map_filler(game, file) == 84)
        return (84);
    if (check_player_in_map(game->map, game) == 84)
        return (84);
    game->map[(int)game->player->pos.y][(int)game->player->pos.x] = '0';
    return (0);
}
