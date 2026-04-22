/*
** EPITECH PROJECT, 2026
** wolf3d
** File description:
** changes menu state
*/

#include "engine.h"
#include "event.h"
#include "ui.h"

void change_menu_state(game_t *game)
{
    game->is_menu_open = !game->is_menu_open;
}
