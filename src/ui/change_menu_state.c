/*
** EPITECH PROJECT, 2026
** wolf3d
** File description:
** changes menu state
*/

#include "engine.h"
#include "event.h"
#include "ui.h"
#include <SFML/Graphics/RenderWindow.h>

void leave_game(game_t *game)
{
    sfRenderWindow_close(game->window);
}

void change_menu_state(game_t *game)
{
    game->is_menu_open = !game->is_menu_open;
}
