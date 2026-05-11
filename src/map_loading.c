/*
** EPITECH PROJECT, 2026
** wolf3d
** File description:
** map loading file
*/

#include "engine.h"
#include "my.h"
#include "event.h"
#include <SFML/System/Vector2.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include "wolf3d.h"

void load_items_into_inv(game_t *game, char **item_list)
{
    player_t *player = game->player;

    for (int pos = 0; pos < my_double_array_length(item_list); pos++) {
        if (!strcmp(item_list[pos], "BOMB")) {
            player->inventory[pos] = BOMB;
        }
        if (!strcmp(item_list[pos], "PIE"))
            player->inventory[pos] = PIE;
        if (!strcmp(item_list[pos], "GUM"))
            player->inventory[pos] = GUM;
        if (!strcmp(item_list[pos], "FLASH"))
            player->inventory[pos] = FLASH;
    }
    free_array(item_list);
}

int load_items(game_t *game, char *file)
{
    char *content = get_file_cont(file);
    char **file_content;
    int item_pos;
    char **items;

    if (!content)
        return (84);
    file_content = my_str_to_word_array(content, "\n");
    if (!file_content)
        return (84);
    item_pos = check_elm_in_tokened_list(file_content, "ITEMS", "=");
    if (item_pos != -1) {
        items = my_str_to_word_array(file_content[item_pos], "=,");
        load_items_into_inv(game, items);
    }
    free_array(file_content);
    free(content);
    return (0);
}

int get_number_value(char *string)
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
    if (load_items(game, file) == 84) {
        return (84);
    }
    game->file_name = strdup(file);
    return (0);
}
