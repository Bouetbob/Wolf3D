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
#include "wolf3d.h"

void write_items(game_t *game, FILE *fd)
{
    char *item_list = NULL;

    fwrite("\n", 1, 1, fd);
    fwrite("ITEMS=", 1, 6, fd);
    for (int i = 0; i < INVENTORY_SIZE; i++) {
        if (game->player->inventory[i]) {
            asprintf(&item_list, "%s,", game->player->inventory[i]->name);
            fwrite(item_list, 1, strlen(item_list), fd);
        }
    }
    fwrite("\n", 1, 1, fd);
}

void write_map(game_t *game, FILE *fd)
{
    game->map[(int) game->player->pos.y][(int) game->player->pos.x] = 'P';
    for (int i = 0; i < game->map_size.y; i++) {
        fwrite(game->map[i], 1, strlen(game->map[i]), fd);
        fwrite("\n", 1, 1, fd);
    }
}

void remove_player_spawn(game_t *game)
{
    int pos = 0;

    for (int i = 0; i < game->map_size.y; i++) {
        pos = find_char('P', game->map[i]);
        if (pos != -1)
            game->map[i][pos] = '0';
    }
}

void write_map_stats(game_t *game, FILE *fd)
{
    char *header = NULL;

    asprintf(&header, "MAP_WIDTH=%i\nMAP_HEIGHT=%i\n\n",
        game->map_size.x, game->map_size.y);
    fwrite(header, 1, strlen(header), fd);
}

int save_map(game_t *game)
{
    FILE *fd = fopen(game->file_name, "w");

    if (!fd)
        return (84);
    remove_player_spawn(game);
    write_map_stats(game, fd);
    write_map(game, fd);
    write_items(game, fd);
    fclose(fd);
    return (0);
}
