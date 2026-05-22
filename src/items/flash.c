/*
** EPITECH PROJECT, 2026
** bomb
** File description:
** bomb function
*/

#include "engine.h"
#include <SFML/System/Vector2.h>


void flash(game_t *game)
{
    game->player->weapons[game->player->curr_weapon]->max_ammo += 10;
}
