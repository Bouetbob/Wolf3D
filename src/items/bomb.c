/*
** EPITECH PROJECT, 2026
** bomb
** File description:
** bomb function
*/

#include "engine.h"
#include <SFML/System/Vector2.h>

static void remove_wall(game_t *game, int x, int y)
{
    if (x >= game->map_size.x || x < 0 || y >= game->map_size.y || y < 0)
        return;
    if (game->map[y][x] == '7') {
        game->map[y][x] = '0';
    }
}

void bomb(game_t *game)
{
    sfVector2f player_pos = game->player->pos;

    remove_wall(game, player_pos.x, player_pos.y + 1);
    remove_wall(game, player_pos.x, player_pos.y - 1);
    remove_wall(game, player_pos.x - 1, player_pos.y);
    remove_wall(game, player_pos.x + 1, player_pos.y);
}
