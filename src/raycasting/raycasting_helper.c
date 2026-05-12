/*
** EPITECH PROJECT, 2026
** Wolf3D
** File description:
** raycasting helper
*/

#include "engine.h"

int is_wall(float x, float y, game_t *game)
{
    int map_x = (int) x;
    int map_y = (int) y;

    if (map_x < 0 || map_y < 0 || map_x >= game->map_size.x
        || map_y >= game->map_size.y)
        return 1;
    return (game->map[map_y][map_x] > '0' && game->map[map_y][map_x] <= '9');
}
