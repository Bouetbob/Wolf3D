/*
** EPITECH PROJECT, 2026
** wolf3d
** File description:
** map loading file
*/

#include "enemy.h"
#include "engine.h"
#include "my.h"
#include "wolf3d.h"
#include <SFML/System/Vector2.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

static void handle_tile_entities(game_t *game, char tile, int x, int y)
{
    sfVector2f pos = {(float)x + 0.5f, (float)y + 0.5f};

    if ((tile == 'T' || tile == 'M') && game->enemy_count < MAX_ENEMIES) {
        game->enemies[game->enemy_count] = init_enemy((tile == 'M' ? 1 : 2),
            &pos);
        if (game->enemies[game->enemy_count])
            game->enemy_count++;
    }
}

static void init_map_entities(game_t *game)
{
    if (!game->map)
        return;
    for (int y = 0; game->map[y]; y++) {
        for (int x = 0; game->map[y][x]; x++)
            handle_tile_entities(game, game->map[y][x], x, y);
    }
}

static int map_filler(game_t *game, char *filename)
{
    FILE *fd = fopen(filename, "r");
    struct stat s;
    char *temp = NULL;

    if (!fd || stat(filename, &s) == -1)
        return (84);
    temp = malloc(sizeof(char) * s.st_size + 1);
    if (!temp)
        return (84);
    fread(temp, 1, s.st_size, fd);
    temp[s.st_size] = '\0';
    if (check_size_validity(temp, game) == 84 ||
        check_map_validity(temp, game) == 84) {
        free(temp);
        return (84);
    }
    init_map_entities(game);
    free(temp);
    fclose(fd);
    return (0);
}

void load_items_into_inv(game_t *game, char **item_list)
{
    player_t *p = game->player;

    for (int i = 0; i < my_double_array_length(item_list) &&
        i < INVENTORY_SIZE; i++) {
        if (!strcmp(item_list[i], "BOMB"))
            p->inventory[i] = BOMB;
        if (!strcmp(item_list[i], "PIE"))
            p->inventory[i] = PIE;
        if (!strcmp(item_list[i], "GUM"))
            p->inventory[i] = GUM;
        if (!strcmp(item_list[i], "FLASH"))
            p->inventory[i] = FLASH;
    }
    free_array(item_list);
}

int load_items(game_t *game, char *file)
{
    char *content = get_file_cont(file);
    char **file_cont;
    int pos;

    if (!content)
        return (84);
    file_cont = my_str_to_word_array(content, "\n");
    if (!file_cont)
        return (84);
    pos = check_elm_in_tokened_list(file_cont, "ITEMS", "=");
    for (int i = 0; i < INVENTORY_SIZE; i++) {
        game->player->inventory[i] = NULL;
    }
    if (pos != -1)
        load_items_into_inv(game, my_str_to_word_array(file_cont[pos], "=,"));
    free_array(file_cont);
    free(content);
    return (0);
}

int get_number_value(char *string)
{
    int res = 0;
    char **tmp = my_str_to_word_array(string, "=");

    if (my_double_array_length(tmp) != 2) {
        free_array(tmp);
        return (-1);
    }
    res = atoi(tmp[1]);
    free_array(tmp);
    return (res);
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

static int get_user_player_pos_input(game_t *game)
{
    bool valid_pos = false;
    char *temp = NULL;
    size_t size = 0;

    while (!valid_pos) {
        printf("Map size: x=%i\ty=%i\n", game->map_size.x, game->map_size.y);
        printf("Format: x=?\ty=?\nReplace ? by a value of your");
        printf(" choice.\nInput \"exit\" if you want to exit.\n");
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
    game->player->pos.x = find_char('P', map[(int) game->player->pos.y]);
    return (0);
}

int load_map_from_file(game_t *game, char *file)
{
    if (map_filler(game, file) == 84)
        return (84);
    if (check_player_in_map(game->map, game) == 84)
        return (84);
    game->map[(int)game->player->pos.y][(int)game->player->pos.x] = '0';
    if (load_items(game, file) == 84)
        return (84);
    game->file_name = strdup(file);
    return (0);
}
